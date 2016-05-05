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
    typedef std::vector<pointer> vector;
    static pointer New() { return std::make_shared<Tournament>(); }

    btm::Round::pointer StartNewRound();
    void ComputeWaitingPlayers(btm::Round::pointer r,
                               btm::Player::vector & players);
    void PairRandom(btm::Round::pointer r,
                    btm::Player::vector & players);
    void PairSwissSystem(btm::Round::pointer r,
                         btm::Player::vector & players);
    void GenerateRandomScores(btm::Round::pointer r);
    void ComputePlayersStatus();
    std::string GetPlayersStatus();

    btm::Player::vector players;
    btm::Round::vector rounds;

};
} // end namespace
#endif // TOURNAMENT_H
