#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include "btmRound.h"
#include "btmPlayer.h"
#include <memory>
#include <QObject>

namespace btm {

class Tournament : public QObject
{
    Q_OBJECT

public:
    Tournament();

    typedef std::shared_ptr<Tournament> pointer;
    typedef std::vector<pointer> vector;
    static pointer New() { return std::make_shared<Tournament>(); }

    btm::Round::pointer StartNewRound();
    void ComputeWaitingPlayers(btm::Round::pointer r,
                               btm::Player::vector & players);
    void PairRandom(btm::Round::pointer r,
                    btm::Player::vector & players);
    void PairSwissSystem(btm::Round::pointer r,
                         btm::Player::vector & players);
    void GenerateRandomScores(btm::Round::pointer r);
    void ComputePlayersStatus();
    std::string GetPlayersStatus();
    void SavePlayersToFile(std::string filename);
    void LoadPlayersFromFile(std::string filename);

    btm::Player::vector players;
    btm::Round::vector rounds;

public slots:
    void on_round_score_changed();

signals:
    void currentRoundHasChanged(btm::Round::pointer);
    void scoreHasChanged();

};
} // end namespace
#endif // TOURNAMENT_H
