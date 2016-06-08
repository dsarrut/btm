#ifndef BTMPLAYER_H
#define BTMPLAYER_H

#include <vector>
#include <sstream>
#include <memory>

#include <QObject>

#include "btmDD.h"
#include "btmUtils.h"

namespace btm {

class Match;

class Player: public QObject
{
    Q_OBJECT

public:
    Player();

    typedef std::shared_ptr<Player> pointer;
    typedef std::vector<pointer> vector;
    static pointer New() { return std::make_shared<Player>(); }

    std::string GetName() const { return name; }
    void SetName(std::string s);

    void UpdateWinPoints(int diff);
    void UpdateWinSets(int diff);
    void UpdateWinMatches(int diff);

    void UpdateScores(std::shared_ptr<btm::Match> m);
    void ResetStatus();

    int id;
    std::string name;
    int nb_of_wait_rounds;
    int nb_of_matches;
    int nb_of_win_matches;
    int nb_of_lost_matches;
    int nb_of_win_sets;
    int nb_of_points;
    bool participate;

    std::string ToString() const;
    std::string StatusToString() const;
    void Save(std::ostream & os);
    void Load(std::istream & is);

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

signals:
    void playerNameChanged();
    void playerScoreChanged();

};

void GenerateRandomPlayers(btm::Player::vector & players, int n);

} // end namespace
#endif // BTMPLAYER_H
