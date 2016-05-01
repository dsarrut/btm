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

    void Bidon();
    std::string ToString();

    std::vector<btm::Match::pointer> matches;

};

} // end namespace
#endif // BTMROUND_H
