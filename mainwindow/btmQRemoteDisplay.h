#ifndef BTMQREMOTEDISPLAY_H
#define BTMQREMOTEDISPLAY_H

#include <QFrame>
#include "btmRound.h"
#include "btmQMatchWidget.h"

namespace Ui {
class QRemoteDisplay;
}

class QRemoteDisplay : public QFrame
{
    Q_OBJECT

public:
    explicit QRemoteDisplay(QWidget *parent = 0);
    ~QRemoteDisplay();

    btm::Round::pointer round;
    std::vector<QMatchWidget*> matchWidgets;

public slots:
    void on_QRemoteDisplay_destroyed();
    void on_RoundChanged(btm::Round::pointer r);
    void playerSelectionToggled(QPlayerWidget*,bool);

private:
    Ui::QRemoteDisplay *ui;
};

#endif // BTMQREMOTEDISPLAY_H
