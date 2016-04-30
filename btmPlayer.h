#ifndef BTMPLAYER_H
#define BTMPLAYER_H

#include <vector>
#include <sstream>

#include "btmDD.h"
#include "btmUtils.h"

namespace btm {

class Player
{
public:
    Player();

    std::string name;

    std::string ToString() const;

    /// Default function to print an element (must be inline here).
    friend std::ostream& operator<<(std::ostream& os, const Player & p) {
        os << p.ToString();
        return os;
    }

};

void GenerateRandomPlayers(std::vector<btm::Player> & players, int n);

} // end namespace
#endif // BTMPLAYER_H
