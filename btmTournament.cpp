#include "btmTournament.h"
#include <algorithm>

btm::Tournament::Tournament()
{

}

btm::Round::pointer btm::Tournament::StartNewRound()
{
 auto r = btm::Round::New();

 btm::Player::vector temp = players;
 std::random_shuffle ( temp.begin(), temp.end() );

 int n = temp.size() % 4;
 for(unsigned int i=0; i<temp.size()-n; i+=4) {
     auto m = btm::Match::New();
     m->players.push_back(temp[i]);
     m->players.push_back(temp[i+1]);
     m->players.push_back(temp[i+2]);
     m->players.push_back(temp[i+3]);
     r->matches.push_back(m);
 }

 return r;
}
