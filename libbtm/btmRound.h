#ifndef BTMROUND_H
#define BTMROUND_H

#include <iostream>
#include <QObject>
#include "btmMatch.h"

namespace btm {

class Round : public QObject
{
    Q_OBJECT

public:
    Round();

    typedef std::shared_ptr<Round> pointer;
    typedef std::vector<pointer> vector;
    static pointer New() { return std::make_shared<Round>(); }

    std::string ToString();
    btm::Status GetStatus();
    void SwapPlayers(btm::Player::pointer p1, btm::Player::pointer p2);
    void FindPlayer(btm::Player::pointer p,
                    btm::Match::pointer & m,
                    int & ip);

    unsigned int round_nb;
    btm::Match::vector matches;
    btm::Player::vector waiting_players;
    void ComputePlayersStatus();

public slots:
    void on_match_status_changed();
    void on_match_score_changed();

protected:
    btm::Status currentStatus;

signals:
    void roundStatusHasChanged();
    void waitingPlayersHaveChanged();
    void roundScoreHasChanged();

};

} // end namespace
#endif // BTMROUND_H
