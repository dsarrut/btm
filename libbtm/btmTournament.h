#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include "btmRound.h"
#include "btmPlayer.h"
#include <memory>
#include <QObject>

namespace btm {

class Tournament : public QObject,
        public std::enable_shared_from_this<Tournament>
{
    Q_OBJECT

public:
    Tournament();

    typedef std::shared_ptr<Tournament> pointer;
    typedef std::vector<pointer> vector;
    static pointer New() { return std::make_shared<Tournament>(); }

    btm::Round::pointer StartNewRound(int set_score_max);
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
    void SavePlayers(std::ostream & os);
    void LoadPlayersFromFile(std::string filename);
    void LoadPlayers(std::istream &is);
    void SaveToFile(std::string filename);
    void LoadFromFile(std::string filename);
    btm::Player::pointer FindPlayerById(int id);

    const btm::Player::vector & GetPlayers() const { return players; }
    void SetPlayers(btm::Player::vector p);

    btm::Round::vector rounds;

public slots:
    void on_round_score_changed();

protected:
    btm::Player::vector players;

signals:
    void currentRoundHasChanged(btm::Round::pointer);
    void scoreHasChanged();

};
} // end namespace
#endif // TOURNAMENT_H
