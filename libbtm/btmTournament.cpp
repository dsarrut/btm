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
    auto r = btm::Round::New();
    r->round_nb = rounds.size()+1;// to start at one
    btm::Player::vector temp;//= players; //copy
    for(auto p:players)
        if (p->participate) temp.push_back(p);
    std::random_shuffle(temp.begin(), temp.end());
    ComputeWaitingPlayers(r, temp);
    PairSwissSystem(r, temp);
    //PairRandom(r, players);
    rounds.push_back(r);
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
        auto m = btm::Match::New(i);
        m->SetPlayer(0, temp[i]);
        m->SetPlayer(1, temp[i+1]);
        m->SetPlayer(2, temp[i+2]);
        m->SetPlayer(3, temp[i+3]);
        r->matches.push_back(m);
        QObject::connect(m.get(), SIGNAL(matchStatusHasChanged()),
                         r.get(), SLOT(on_match_status_changed()));
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
        auto m = btm::Match::New(nb);
        m->SetPlayer(0, temp[i]);
        m->SetPlayer(1, temp[i+2]); // first with third
        m->SetPlayer(2, temp[i+1]);
        m->SetPlayer(3, temp[i+3]);
        r->matches.push_back(m); //
        QObject::connect(m.get(), SIGNAL(matchStatusHasChanged()),
                         r.get(), SLOT(on_match_status_changed()));
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
    for(auto r:rounds) {
        r->UpdatePlayersStatus();
    }
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
    for(auto p:players) os << p->name << std::endl;
    os.close();
}

void btm::Tournament::LoadPlayersFromFile(std::string filename)
{
    std::ifstream is(filename);
    players.clear();
    for (std::string line; std::getline(is, line); )
    {
        btm::Player::pointer p = btm::Player::New();
        p->name = line;
        p->ResetStatus();
        players.push_back(p);
    }
    is.close();
}
