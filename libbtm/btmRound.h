#ifndef BTMROUND_H
#define BTMROUND_H

#include <iostream>
#include <QObject>
#include "btmMatch.h"


namespace btm {

class Tournament;

class Round : public QObject,
        public std::enable_shared_from_this<Round>
{
    Q_OBJECT

public:
    Round(std::shared_ptr<btm::Tournament> t, int s=11);

    typedef std::shared_ptr<Round> pointer;
    typedef std::vector<pointer> vector;
    static pointer New(std::shared_ptr<btm::Tournament> t, int s=11);

    std::string ToString();
    btm::Status GetStatus();
    std::shared_ptr<btm::Tournament> tournament;

    void SwapPlayers(btm::Player::pointer p1, btm::Player::pointer p2);
    void FindPlayer(btm::Player::pointer p,
                    btm::Match::pointer & m,
                    int & ip);

    unsigned int round_nb;
    btm::Match::vector matches;
    btm::Player::vector waiting_players;
    void ComputePlayersStatus();
    void Save(std::ostream &os);
    void Load(std::istream &is);
    int GetNumberOfPointsToWin() { return nb_points_to_win; }

public slots:
    void on_match_status_changed();
    void on_match_score_changed();

protected:
    btm::Status currentStatus;
    int nb_points_to_win;

signals:
    void roundStatusHasChanged();
    void waitingPlayersHaveChanged();
    void roundScoreHasChanged();

};

} // end namespace
#endif // BTMROUND_H
