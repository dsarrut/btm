#include "btmRound.h"

btm::Round::Round()
{
    currentStatus = Init;
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

void btm::Round::UpdatePlayersStatus()
{
    for(auto m:matches) {
        m->UpdatePlayersStatus();
    }
    for(auto p:waiting_players) {
        p->nb_of_wait_rounds++;
    }
}

btm::Status btm::Round::GetStatus()
{
    return currentStatus;
}

void btm::Round::SwitchPlayers(btm::Player::pointer p1,
                               btm::Player::pointer p2)
{
    btm::Match::pointer m1;
    btm::Match::pointer m2;
    int ip1, ip2;
    FindPlayer(p1, m1, ip1);
    FindPlayer(p2, m2, ip2);
    if (ip1 and ip2) {
        m1->SwapPlayer(ip1, m2, ip2);
        return;
    }
    DD(" in waiting TODO");
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
        emit RoundStatusHasChanged();
    }
}
