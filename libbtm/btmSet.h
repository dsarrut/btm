#ifndef SET_H
#define SET_H

#include <random>
#include <memory>
#include <ctime>
#include "btmPlayer.h"

namespace btm {

enum Status { Init, Playing, Terminated };

class Set
{
public:
    // Const
    Set(int s);

    // Types
    typedef std::shared_ptr<Set> pointer;
    typedef std::vector<pointer> vector;
    static pointer New(int s) { return std::make_shared<Set>(s); }

    int GetWinner(); // 0=in progress, 1=team1 2=team2
    void GenerateRandomScore(std::mt19937 &rng);
    btm::Status GetStatus();
    void SetScore(int team, int points);
    unsigned int GetTeam1Points() const { return team1_points; }
    unsigned int GetTeam2Points() const { return team2_points; }
    unsigned int GetTeamPoints(unsigned int team) const;
    void UpdatePlayerStats(int team, btm::Player::pointer m);
    void Save(std::ostream & os);
    void Load(std::istream & is);
    std::string ToString() const;

    /// Default function to print an element (must be inline here).
    friend std::ostream& operator<<(std::ostream& os,
                                    const Set::pointer  m) {
        os << m->ToString();
        return os;
    }

protected:
    unsigned int team1_points;
    unsigned int team2_points;
    unsigned int nb_points_to_win;
};

} // end namespace

#endif // SET_H
