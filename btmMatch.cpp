#include "btmMatch.h"

btm::Match::Match()
{
    score = 0;
}

std::string btm::Match::ToString()
{
    std::stringstream ss;
    ss << players[0]->ToString() << "+" << players[1]->ToString()
       << "    vs    "
       << players[2]->ToString() << "+" << players[3]->ToString();
    return ss.str();
}
