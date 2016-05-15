#ifndef BTMQROUNDWIDGET_H
#define BTMQROUNDWIDGET_H

#include <QFrame>
#include "btmTournament.h"
#include "btmQMatchWidget.h"
#include "btmQWaitingPlayersWidget.h"

namespace Ui {
class QRoundWidget;
}

class QRoundWidget : public QFrame
{
    Q_OBJECT

public:
    explicit QRoundWidget(QWidget *parent = 0);
    ~QRoundWidget();

    void SetTournament(btm::Tournament::pointer tournament);
    void AddWidget();
    void SetRound(btm::Round::pointer r);
    void SwapPlayers(btm::Player::pointer p1, btm::Player::pointer p2);

public slots:
    void Update();
    void playerSwitched(QMatchWidget *w, int player);
    void playerSelectionToggled(QPlayerWidget * w, bool checked);

protected:
    btm::Tournament::pointer tournament;
    btm::Round::pointer round;
    std::vector<QMatchWidget*> widgetMatches;
    QWaitingPlayersWidget * waitingPlayersWidget;
    bool switchPlayerMode;

signals:
    void newCurrentRound(btm::Round::pointer);

private slots:
    void on_buttonRandomScores_clicked();
    void on_buttonNewRound_clicked();
    void on_buttonBack_clicked();
    void on_buttonForward_clicked();
    void on_buttonSwitch_clicked();

private:
    Ui::QRoundWidget *ui;
};

#endif // BTMQROUNDWIDGET_H
