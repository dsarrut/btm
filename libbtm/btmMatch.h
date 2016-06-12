#ifndef BTMMATCH_H
#define BTMMATCH_H

#include "btmPlayer.h"
#include "btmSet.h"
#include <array>
#include <QObject>

namespace btm {

class Round;

class Match : public QObject
{
    Q_OBJECT

public:

    // Constructor
    Match(std::shared_ptr<btm::Round> r, int n,
          btm::Player::pointer p1,
          btm::Player::pointer p2,
          btm::Player::pointer p3,
          btm::Player::pointer p4);

    // Types
    typedef std::shared_ptr<Match> pointer;
    typedef std::vector<pointer> vector;
    static pointer New(std::shared_ptr<Round> r, int n,
                       Player::pointer p1,
                       Player::pointer p2,
                       Player::pointer p3,
                       Player::pointer p4);

    int GetNumberOfPoints(int team);

    void ComputePlayersStatus();
    void GenerateRandomScore(std::mt19937 &rng);

    int GetWinner();
    btm::Status GetStatus();

    // Player in [1-4]
    btm::Player::pointer GetPlayer(int i);
    int GetPlayerTeam(btm::Player::pointer p);

    // Set in [1-3]
    btm::Set::pointer GetSet(int i);

    unsigned int GetMatchNb() const { return match_nb; }

    std::string ToString();
    void SetScore(int team, int theSet, unsigned int points);
    //void SetPlayer(unsigned int i, btm::Player::pointer p);
    void SwapPlayer(int player1,
                    btm::Match::pointer m2,
                    int player2);
    void FindPlayer(btm::Player::pointer p, int & ip);
    void Save(std::ostream & os);
    void Load(std::istream & is);
    std::string ToString() const;

    /// Default function to print an element (must be inline here).
    friend std::ostream& operator<<(std::ostream& os,
                                    const Match::pointer  m) {
        os << m->ToString();
        return os;
    }

signals:
    void matchPlayersHaveChanged();
    void matchScoreHasChanged();
    void matchStatusHasChanged();

protected:
    std::array<btm::Player::pointer, 4> players;
    std::vector<btm::Set::pointer> sets;
    unsigned int match_nb;
    std::shared_ptr<btm::Round> round;
    //unsigned int score; // 0=in progress 1=team1 or 2=team2

};
} // end namespace

#endif // BTMMATCH_H
