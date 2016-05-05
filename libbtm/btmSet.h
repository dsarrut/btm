#ifndef SET_H
#define SET_H

#include <random>
#include <memory>
#include <ctime>
#include "btmDD.h"

namespace btm {

class Set
{
public:
    Set();

    typedef std::shared_ptr<Set> pointer;
    typedef std::vector<pointer> vector;
    static pointer New() { return std::make_shared<Set>(); }

    int GetWinner(); // 0=in progress, 1=team1 2=team2
    void GenerateRandomScore(std::mt19937 &rng);

    int team1_points;
    int team2_points;

    int nb_points_to_win;
};

} // end namespace

#endif // SET_H
