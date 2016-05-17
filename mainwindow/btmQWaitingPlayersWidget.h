#ifndef QWAITINGPLAYERSWIDGET_H
#define QWAITINGPLAYERSWIDGET_H

#include <QFrame>
#include <QLabel>
#include <QRadioButton>
#include "btmPlayer.h"
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
    void ConnectPlayerSelection(QObject *o);

    void SetSwapPlayerMode(bool b);
   // void ChangePlayer(btm::Player::pointer p1,
    //                  btm::Player::pointer p2);

//signals:
  //  void playerSwaped(QWaitingPlayersWidget *, int player);

protected:
    btm::Player::vector players;
    std::vector<QPlayerWidget*> playerWidgets;

private:
    Ui::QWaitingPlayersWidget *ui;
};

#endif // QWAITINGPLAYERSWIDGET_H
