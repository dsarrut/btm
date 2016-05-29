#include "btmTournament.h"
#include <algorithm>
#include <random>
#include <ctime>
#include <fstream>

btm::Tournament::Tournament()
{
    std::srand(std::time(0));
}

btm::Round::pointer btm::Tournament::StartNewRound()
{
    btm::Tournament::pointer t(this);
    auto r = btm::Round::New(t);
    r->round_nb = rounds.size()+1;// to start at one
    btm::Player::vector temp;//= players; //copy
    for(auto p:players)
        if (p->participate) temp.push_back(p);
    std::random_shuffle(temp.begin(), temp.end());
    ComputeWaitingPlayers(r, temp);
    PairSwissSystem(r, temp);
    //PairRandom(r, players);
    rounds.push_back(r);
    QObject::connect(r.get(), SIGNAL(roundScoreHasChanged()),
                     this, SLOT(on_round_score_changed()));
    emit currentRoundHasChanged(r);
    return r;
}

void btm::Tournament::ComputeWaitingPlayers(btm::Round::pointer r,
                                            btm::Player::vector & players)
{
    btm::Player::vector temp = players; //copy
    std::sort(temp.begin(), temp.end(),
              [](const btm::Player::pointer & a,
              const btm::Player::pointer & b) -> bool
    {
        return a->nb_of_wait_rounds > b->nb_of_wait_rounds;
    });
    int n = temp.size() % 4;
    r->waiting_players.clear();
    for(auto i=0; i<n; i++) {
        r->waiting_players.push_back(temp.back());
        temp.pop_back();
    }
    players = temp;
}

void btm::Tournament::PairRandom(btm::Round::pointer r,
                                 btm::Player::vector & players)
{
    auto temp = players;
    for(unsigned int i=0; i<temp.size(); i+=4) {
        auto m = btm::Match::New(r, i);
        m->SetPlayer(1, temp[i]);
        m->SetPlayer(2, temp[i+1]);
        m->SetPlayer(3, temp[i+2]);
        m->SetPlayer(4, temp[i+3]);
        r->matches.push_back(m);
        QObject::connect(m.get(), SIGNAL(matchStatusHasChanged()),
                         r.get(), SLOT(on_match_status_changed()));
        QObject::connect(m.get(), SIGNAL(matchScoreHasChanged()),
                         r.get(), SLOT(on_match_score_changed()));
    }
}

void btm::Tournament::PairSwissSystem(btm::Round::pointer r,
                                      btm::Player::vector & players)
{
    btm::Player::vector temp = players;
    std::sort(temp.begin(), temp.end(),
              [](const btm::Player::pointer & a,
              const btm::Player::pointer & b) -> bool
    {
        return a->nb_of_win_matches > b->nb_of_win_matches;
    });
    int nb=1;
    for(unsigned int i=0; i<temp.size(); i+=4) {
        auto m = btm::Match::New(r, nb);
        m->SetPlayer(1, temp[i]);
        m->SetPlayer(2, temp[i+2]); // first with third
        m->SetPlayer(3, temp[i+1]);
        m->SetPlayer(4, temp[i+3]);
        r->matches.push_back(m); //
        QObject::connect(m.get(), SIGNAL(matchStatusHasChanged()),
                         r.get(), SLOT(on_match_status_changed()));
        QObject::connect(m.get(), SIGNAL(matchScoreHasChanged()),
                         r.get(), SLOT(on_match_score_changed()));
        ++nb;
    }
}

void btm::Tournament::GenerateRandomScores(btm::Round::pointer r)
{
    std::mt19937 rng(std::time(0));
    std::uniform_int_distribution<int> gen(1, 2);
    for(auto & m:r->matches) m->GenerateRandomScore(rng);
}

void btm::Tournament::ComputePlayersStatus()
{
    for(auto p:players) p->ResetStatus();
    for(auto r:rounds) r->ComputePlayersStatus();
    emit scoreHasChanged();
}

std::string btm::Tournament::GetPlayersStatus()
{
    std::stringstream ss;
    for(auto p:players) {
        ss << p->ToString() << " " << p->StatusToString() << std::endl;
    }
    return ss.str();
}

void btm::Tournament::SavePlayersToFile(std::string filename)
{
    std::ofstream os(filename);
    SavePlayers(os);
    os.close();
}

void btm::Tournament::LoadPlayersFromFile(std::string filename)
{
    std::ifstream is(filename);
    LoadPlayers(is);
    is.close();
}

void btm::Tournament::SavePlayers(std::ostream &os)
{
    os << players.size() << std::endl;
    for(auto p:players) {
        p->Save(os);
        os << std::endl;
    }
}

void btm::Tournament::LoadPlayers(std::istream & is)
{
    players.clear();
    int n;
    is >> n;
    for(int i=0; i<n; i++) {
        btm::Player::pointer p = btm::Player::New();
        p->Load(is);
        players.push_back(p);
    }
}

void btm::Tournament::SaveToFile(std::string filename)
{
    std::ofstream os(filename);
    SavePlayers(os);
    os << rounds.size() << std::endl;
    for(auto r:rounds) r->Save(os);
}

void btm::Tournament::LoadFromFile(std::string filename)
{
    std::ifstream is(filename);
    LoadPlayers(is);
     int nb;
    is >> nb; // nb of rounds
    rounds.clear();
    for(int i=0; i<nb; i++) {
       auto r = btm::Round::New(shared_from_this());
       r->Load(is);
       rounds.push_back(r);
       QObject::connect(r.get(), SIGNAL(btm::Round::roundScoreHasChanged()),
                        this, SLOT(on_round_score_changed()));
    }
    is.close();

}

btm::Player::pointer btm::Tournament::FindPlayerById(int id)
{
    for(auto p:players) {
        if (p->id == id) return p;
    }
    DD("error player id ")
    exit(0);
}

void btm::Tournament::on_round_score_changed()
{
    ComputePlayersStatus();
}
