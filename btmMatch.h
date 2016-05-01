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


};
} // end namespace

#endif // BTMMATCH_H
