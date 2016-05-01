#ifndef BTMMATCH_H
#define BTMMATCH_H

#include "btmPlayer.h"

namespace btm {

class Match
{
public:
    Match();

    typedef std::shared_ptr<Match> pointer;
    typedef std::vector<pointer> vector;
    static pointer New() { return std::make_shared<Match>(); }

    std::string ToString();

    std::vector<btm::Player::pointer> players;

    int score; // 0=in progress 1=team1 or 2=team2

};
} // end namespace

#endif // BTMMATCH_H
