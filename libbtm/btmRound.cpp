#include "btmRound.h"
#include "btmTournament.h"
#include <algorithm>

btm::Round::Round(std::shared_ptr<Tournament> t)
{
    currentStatus = Init;
    tournament = t;
}

btm::Round::pointer btm::Round::New(btm::Tournament::pointer t)
{
    return std::make_shared<Round>(t);
}

std::string btm::Round::ToString()
{
    std::stringstream ss;
    int n=1;
    for(auto m:matches) {
        ss << "Match " << n << " " << m->ToString() << std::endl;
        ++n;
    }
    for(auto p:waiting_players)
        ss << "Waiting players : " << p << std::endl;
    return ss.str();
}


void btm::Round::ComputePlayersStatus()
{
    for(auto m:matches) {
        m->ComputePlayersStatus();
    }
    for(auto p:waiting_players) {
        p->nb_of_wait_rounds++;
    }
}

void btm::Round::Save(std::ostream & os)
{
    os << round_nb << " "
       << waiting_players.size() << " "
       << matches.size() << std::endl;
    for(auto p:waiting_players) os << p->id << " ";
    os << std::endl << std::endl;
    for(auto m:matches) m->Save(os);
    os << std::endl;
}

void btm::Round::Load(std::istream & is)
{
    int nb_w;
    int nb_m;
    is >> round_nb;
    is >> nb_w;
    is >> nb_m;
    // Waiting players
    waiting_players.clear();
    for(int i=0; i<nb_w; i++) {
        int id;
        is >> id;
        auto player = tournament->FindPlayerById(id);
        waiting_players.push_back(player);
    }
    // matchs
    matches.clear();
    for(int i=0; i<nb_m; i++) {
        btm::Match::pointer match = btm::Match::New(shared_from_this(), i);
        match->Load(is);
        matches.push_back(match);
    }
    DD(nb_m);
    DD(matches.size());
    for(auto m:matches) {
        DD(m);
    }
    DD("end roundload");
}

void btm::Round::on_match_score_changed()
{
    DD("round:on match score recompute");
    emit roundScoreHasChanged();
}

btm::Status btm::Round::GetStatus()
{
    return currentStatus;
}

void btm::Round::SwapPlayers(btm::Player::pointer p1,
                             btm::Player::pointer p2)
{
    btm::Match::pointer m1;
    btm::Match::pointer m2;
    int ip1, ip2;
    FindPlayer(p1, m1, ip1);
    FindPlayer(p2, m2, ip2);
    if (ip1 and ip2) {
        m1->SwapPlayer(ip1, m2, ip2);
        emit roundScoreHasChanged();
        return;
    }
    if (ip1) {
        auto i = std::find(waiting_players.begin(), waiting_players.end(), p2);
        m1->SetPlayer(ip1, *i);
        *i = p1;
    }
    else {
        auto i = std::find(waiting_players.begin(), waiting_players.end(), p1);
        m2->SetPlayer(ip2, *i);
        *i = p2;
    }
    emit waitingPlayersHaveChanged();
    emit roundScoreHasChanged();
}

void btm::Round::FindPlayer(btm::Player::pointer p,
                            btm::Match::pointer &m,
                            int &ip)
{
    ip = 0;
    for(auto match:matches) {
        match->FindPlayer(p, ip);
        if (ip) {
            m = match;
            return;
        }
    }
}

void btm::Round::on_match_status_changed()
{
    DD("slot round::on_match_status_changed");
    btm::Status status = Init;
    unsigned int playing=0;
    unsigned int term=0;
    for(auto m:matches) {
        if (m->GetStatus() == Init) status = Init;
        if (m->GetStatus() == Playing) ++playing;
        if (m->GetStatus() == Terminated) ++term;
    }
    if (playing == matches.size()) status = Playing;
    if (term == matches.size()) status = Terminated;
    if (currentStatus != status) {
        currentStatus = status;
        emit roundStatusHasChanged();
    }
}
