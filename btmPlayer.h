#ifndef BTMPLAYER_H
#define BTMPLAYER_H

#include <vector>
#include <sstream>
#include <memory>

#include "btmDD.h"
#include "btmUtils.h"

namespace btm {

class Player
{
public:
    Player();

    typedef std::shared_ptr<Player> pointer;
    typedef std::vector<pointer> vector;
    static pointer New() { return std::make_shared<Player>(); }

    std::string name;
    std::string ToString() const;

    /// Default function to print an element (must be inline here).
    friend std::ostream& operator<<(std::ostream& os, const Player & p) {
        os << p.ToString();
        return os;
    }
    /// Default function to print an element (must be inline here).
    friend std::ostream& operator<<(std::ostream& os, const Player::pointer  p) {
        os << p->ToString();
        return os;
    }

};

void GenerateRandomPlayers(btm::Player::vector & players, int n);

} // end namespace
#endif // BTMPLAYER_H
