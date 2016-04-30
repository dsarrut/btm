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

void btm::GenerateRandomPlayers(std::vector<btm::Player> &players, int n)
{
    for(auto i=0; i<n; i++) {
     btm::Player p;
     p.name = btm::RandomString(10);
     players.push_back(p);
    }
}

