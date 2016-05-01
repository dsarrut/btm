#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <btmRound.h>
#include <btmPlayer.h>
#include <memory>

namespace btm {

class Tournament
{
public:
    Tournament();

    typedef std::shared_ptr<Tournament> pointer;

    btm::Round::pointer StartNewRound();
    void GenerateRandomScores(btm::Round::pointer r);

    std::vector<btm::Player::pointer> players;
    std::vector<btm::Round::pointer> rounds;
    //std::vector<btm::PlayerStatus> players_stats;

};
} // end namespace
#endif // TOURNAMENT_H
