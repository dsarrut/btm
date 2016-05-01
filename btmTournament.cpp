#include "btmTournament.h"
#include <algorithm>
#include <random>
#include <ctime>


btm::Tournament::Tournament()
{
    std::srand(std::time(0));
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
 rounds.push_back(r);
 return r;
}

void btm::Tournament::GenerateRandomScores(btm::Round::pointer r)
{
    std::mt19937 rng(std::time(0));
    std::uniform_int_distribution<int> gen(1, 2); // uniform, unbiased
    for(auto & m:r->matches) {
        m->score = gen(rng);
        DD(m->score);
    }
}
