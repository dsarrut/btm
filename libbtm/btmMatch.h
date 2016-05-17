#ifndef BTMMATCH_H
#define BTMMATCH_H

#include "btmPlayer.h"
#include "btmSet.h"
#include <array>
#include <QObject>

namespace btm {

class Match : public QObject
{
    Q_OBJECT

public:
    // Constructor
    Match(int n);

    // Types
    typedef std::shared_ptr<Match> pointer;
    typedef std::vector<pointer> vector;
    static pointer New(int n) { return std::make_shared<Match>(n); }

    void UpdatePlayersStatus();
    void GenerateRandomScore(std::mt19937 &rng);

    int GetWinner();
    btm::Status GetStatus();
    btm::Player::pointer GetPlayer(int i);
    btm::Set::pointer GetSet(int i) { return sets[i]; }
    unsigned int GetMatchNb() const { return match_nb; }

    std::string ToString();
    void SetScore(int team, int set, int points);
    void SetPlayer(unsigned int i, btm::Player::pointer p);
    void SwapPlayer(int player1,
                    btm::Match::pointer m2,
                    int player2);
    void FindPlayer(btm::Player::pointer p, int & ip);

signals:
    void matchPlayersHaveChanged();
    void matchScoreHasChanged();
    void matchStatusHasChanged();

protected:
    std::array<btm::Player::pointer, 4> players;
    std::vector<btm::Set::pointer> sets;
    unsigned int match_nb;
    //unsigned int score; // 0=in progress 1=team1 or 2=team2

};
} // end namespace

#endif // BTMMATCH_H
