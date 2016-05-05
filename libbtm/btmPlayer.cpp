#include "btmPlayer.h"

btm::Player::Player()
{
    ResetStatus();
}

std::string btm::Player::ToString() const
{
    std::stringstream ss;
    ss << name;
    return ss.str();
}

std::string btm::Player::StatusToString() const
{
    std::stringstream ss;
    ss << "M " << nb_of_matches
       << "  W " << nb_of_win_matches
       << "  L " << nb_of_lost_matches
       << "  t " << nb_of_wait_rounds;
    return ss.str();
}

void btm::Player::ResetStatus()
{
    nb_of_wait_rounds = 0;
    nb_of_lost_matches = 0;
    nb_of_matches = 0;
    nb_of_win_matches = 0;
}

void btm::GenerateRandomPlayers(btm::Player::vector & players, int n)
{
    for(auto i=0; i<n; i++) {
     auto p = btm::Player::New();
     p->name = btm::RandomString(10)+" "+btm::RandomString(10);
     players.push_back(p);
    }
}

