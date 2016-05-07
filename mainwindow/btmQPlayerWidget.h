#ifndef BTMQPLAYERWIDGET_H
#define BTMQPLAYERWIDGET_H

#include <QFrame>
#include "btmPlayer.h"

namespace Ui {
class QPlayerWidget;
}

class QPlayerWidget : public QFrame
{
    Q_OBJECT

public:
    explicit QPlayerWidget(QWidget *parent = 0);
    ~QPlayerWidget();

    void SetPlayer(btm::Player::pointer p);
    void EnableSelectMode(bool b);
    void ResetSelection();
    void Update();
    btm::Player::pointer GetPlayer() { return player; }
    void ChangePlayer(btm::Player::pointer p1, btm::Player::pointer p2);

signals:
    void selectedToggled(QPlayerWidget*, bool checked);

protected:
    btm::Player::pointer player;
    bool selectMode;

private slots:
    void on_radioButton_toggled(bool checked);

private:
    Ui::QPlayerWidget *ui;
};

#endif // BTMQPLAYERWIDGET_H
