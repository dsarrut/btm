#ifndef QWAITINGPLAYERSWIDGET_H
#define QWAITINGPLAYERSWIDGET_H

#include <QFrame>
#include <QLabel>
#include <QRadioButton>
#include "btmPlayer.h"
#include "btmRound.h"
#include "btmQPlayerWidget.h"

namespace Ui {
class QWaitingPlayersWidget;
}

class QWaitingPlayersWidget : public QFrame
{
    Q_OBJECT

public:
    explicit QWaitingPlayersWidget(QWidget *parent = 0);
    ~QWaitingPlayersWidget();

    void SetPlayers(btm::Player::vector p);
    void SetRound(btm::Round::pointer r);
    void ConnectPlayerSelection(QObject *o);
    void ResetSelection();
    void SetSwapPlayerMode(bool b);

public slots:
    void on_waiting_players_changed();

protected:
    btm::Player::vector players;
    std::vector<QPlayerWidget*> playerWidgets;
    btm::Round::pointer round;

private:
    Ui::QWaitingPlayersWidget *ui;
};

#endif // QWAITINGPLAYERSWIDGET_H
