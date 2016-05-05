#ifndef BTMROUND_H
#define BTMROUND_H

#include <iostream>
#include "btmMatch.h"

namespace btm {

class Round
{
public:
    Round();

    typedef std::shared_ptr<Round> pointer;
    typedef std::vector<pointer> vector;
    static pointer New() { return std::make_shared<Round>(); }
    enum Status { Init, Playing, Terminated };

    std::string ToString();
    void UpdatePlayersStatus();
    Status GetStatus() { return status; }

    Status status;
    btm::Match::vector matches;
    btm::Player::vector waiting_players;
};

} // end namespace
#endif // BTMROUND_H
