#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <btmRound.h>
#include <btmPlayer.h>

namespace btm {

class Tournament
{
public:
    Tournament();

    void StartNewRound() {}

    std::vector<btm::Player> players;
    std::vector<btm::Round> rounds;
    //std::vector<btm::PlayerStatus> players_stats;

};
} // end namespace
#endif // TOURNAMENT_H
