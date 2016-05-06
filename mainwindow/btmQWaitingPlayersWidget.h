#ifndef QWAITINGPLAYERSWIDGET_H
#define QWAITINGPLAYERSWIDGET_H

#include <QFrame>
#include "btmPlayer.h"

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

protected:
    btm::Player::vector players;

private:
    Ui::QWaitingPlayersWidget *ui;
};

#endif // QWAITINGPLAYERSWIDGET_H
