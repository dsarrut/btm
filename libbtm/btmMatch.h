#ifndef BTMMATCH_H
#define BTMMATCH_H

#include "btmPlayer.h"
#include "btmSet.h"
#include <array>

namespace btm {

class Match
{
public:
    Match(int n);

    typedef std::shared_ptr<Match> pointer;
    typedef std::vector<pointer> vector;
    static pointer New(int n) { return std::make_shared<Match>(n); }
    enum Status { Init, Playing, Terminated };

    std::string ToString();
    void UpdatePlayersStatus();
    void GenerateRandomScore(std::mt19937 &rng);

    void SetScore(int team, int set, int points);
    int GetWinner();

    std::array<btm::Player::pointer, 4> players;

    std::vector<btm::Set::pointer> sets;
    Status status;
    int match_nb;
    int score; // 0=in progress 1=team1 or 2=team2

};
} // end namespace

#endif // BTMMATCH_H
