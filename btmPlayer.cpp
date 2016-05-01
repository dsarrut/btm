#include "btmPlayer.h"

btm::Player::Player()
{

}

std::string btm::Player::ToString() const
{
    std::stringstream ss;
    ss << name;
    return ss.str();
}

void btm::GenerateRandomPlayers(btm::Player::vector & players, int n)
{
    for(auto i=0; i<n; i++) {
     auto p = btm::Player::New();
     p->name = btm::RandomString(10);
     players.push_back(p);
    }
}

