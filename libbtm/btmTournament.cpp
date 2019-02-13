#include "btmTournament.h"
#include <algorithm>
#include <random>
#include <ctime>
#include <fstream>
#include <sstream>


//----------------------------------------------------------------------------
btm::Tournament::Tournament()
{
    std::srand(std::time(0));
    mPairMode = 0;
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
btm::Round::pointer btm::Tournament::StartNewRound(int set_score_max)
{
    btm::Tournament::pointer t(this);
    auto r = btm::Round::New(t, set_score_max);
    r->round_nb = rounds.size()+1;// to start at one
    btm::Player::vector temp;//= players; //copy
    for(auto p:players)
        if (p->participate) temp.push_back(p);
    std::random_shuffle(temp.begin(), temp.end());
    ComputeWaitingPlayers(r, temp);
    if (mPairMode == 0)
        PairSwissSystem(r, temp);
    else
        PairRandom(r, temp);
    rounds.push_back(r);
    QObject::connect(r.get(), SIGNAL(roundScoreHasChanged()),
                     this, SLOT(on_round_score_changed()));
    emit currentRoundHasChanged(r);
    return r;
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
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
        temp.back()->nb_of_wait_rounds++;
        temp.pop_back();
    }
    players = temp;
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void btm::Tournament::PairRandom(btm::Round::pointer r,
                                 btm::Player::vector & players)
{
    DD("PairRandom");
    btm::Player::vector temp = players;
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(temp.begin(), temp.end(), g);
    int nb=1;
    for(unsigned int i=0; i<temp.size(); i+=4) {
        auto m = btm::Match::New(r, nb, temp[i], temp[i+2],
                temp[i+1], temp[i+3]);
        r->matches.push_back(m);
        ++nb;
    }
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void btm::Tournament::PairSwissSystem(btm::Round::pointer r,
                                      btm::Player::vector & players)
{
    DD("PairSwiss");
    btm::Player::vector temp = players;
    std::sort(temp.begin(), temp.end(),
              [](const btm::Player::pointer & a,
              const btm::Player::pointer & b) -> bool
    {
        auto ia = a->nb_of_win_matches;
        auto ib = b->nb_of_win_matches;
        if (ia>ib) return true;
        if (ia<ib) return false;
        auto sa = a->nb_of_win_sets;
        auto sb = b->nb_of_win_sets;
        if (sa>sb) return true;
        if (sa<sb) return false;
        auto na = a->nb_of_points;
        auto nb = b->nb_of_points;
        return (na>nb);
        // If equality ?
    });
    int nb=1;
    for(unsigned int i=0; i<temp.size(); i+=4) {
        auto m = btm::Match::New(r, nb, temp[i], temp[i+2],
                temp[i+1], temp[i+3]);
        r->matches.push_back(m);
        ++nb;
    }
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void btm::Tournament::GenerateRandomScores(btm::Round::pointer r)
{
    std::mt19937 rng(std::time(0));
    std::uniform_int_distribution<int> gen(1, 2);
    for(auto & m:r->matches) m->GenerateRandomScore(rng);
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void btm::Tournament::ComputePlayersStatus()
{
    for(auto p:players) p->ResetStatus();
    for(auto r:rounds) r->ComputePlayersStatus();
    emit scoreHasChanged();
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
std::string btm::Tournament::GetPlayersStatus()
{
    std::stringstream ss;
    for(auto p:players) {
        ss << p->ToString() << " " << p->StatusToString() << std::endl;
    }
    return ss.str();
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void btm::Tournament::SavePlayersToFile(std::string filename)
{
    std::ofstream os(filename);
    SavePlayers(os);
    os.close();
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void btm::Tournament::LoadPlayersFromFile(std::string filename)
{
    std::ifstream is(filename);
    LoadPlayers(is);
    is.close();
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void btm::Tournament::SavePlayers(std::ostream &os)
{
    os << players.size() << std::endl;
    for(auto p:players) p->Save(os);
    os << std::endl;
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void btm::Tournament::LoadPlayers(std::istream & is)
{
    players.clear();
    std::string line;
    std::getline(is, line);
    std::istringstream iss(line);
    int n;
    iss >> n; // nb of players
    DD("nb of players");
    DD(n);
    for(int i=0; i<n; i++) {
        btm::Player::pointer p = btm::Player::New();
        p->Load(is);
        players.push_back(p);
    }
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void btm::Tournament::SaveToFile(std::string filename)
{
    std::ofstream os(filename);
    SavePlayers(os);
    os << "Rounds " << rounds.size() << std::endl;
    for(auto r:rounds) r->Save(os);
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void btm::Tournament::LoadFromFile(std::string filename)
{
    // Players
    std::ifstream is(filename);
    LoadPlayers(is);

    // Nb of round
    std::string line;
    std::string s;
    bool found = false;
    int nb;
    while (!found) {
        std::getline(is, line);
        std::istringstream iss(line);
        if (line == "") continue;
        iss >> s;
        if (s == "Rounds") {
            iss >> nb; // nb of rounds
            DD(nb);
            found = true;
        }
        DD(line);
        if (!iss) exit(0);
    }

    // Round
    rounds.clear();
    for(int i=0; i<nb; i++) {
        auto r = btm::Round::New(shared_from_this());
        r->Load(is);
        rounds.push_back(r);
        QObject::connect(r.get(), SIGNAL(roundScoreHasChanged()),
                         this, SLOT(on_round_score_changed()));
    }
    if (rounds.size() > 0)
        emit currentRoundHasChanged(rounds[0]);
    is.close();
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
btm::Player::pointer btm::Tournament::FindPlayerById(int id)
{
    for(auto & p:players) {
        if (p->id == id) return p;
    }
    DD("FindPlayerById error player id ");
    DD(id);
    exit(0);
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void btm::Tournament::AddPlayer(btm::Player::pointer p)
{
    players.push_back(p);
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void btm::Tournament::SetPlayers(btm::Player::vector p)
{
    players = p;
    DD("TODO: emit signal players changed");
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void btm::Tournament::on_round_score_changed()
{
    ComputePlayersStatus();
}
//----------------------------------------------------------------------------
