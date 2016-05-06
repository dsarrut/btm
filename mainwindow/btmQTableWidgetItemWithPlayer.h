#ifndef QTABLEWIDGETITEMWITHPLAYER_H
#define QTABLEWIDGETITEMWITHPLAYER_H

#include <QObject>
#include <QTableWidgetItem>
#include "btmPlayer.h"

namespace btm {

class QTableWidgetItemWithPlayer : public QTableWidgetItem
{

public:
    QTableWidgetItemWithPlayer(btm::Player::pointer p);
    void Update();
    void itemClicked();

    bool checkable;
    btm::Player::pointer player;

};

} // end namespace

#endif // QTABLEWIDGETITEMWITHPLAYER_H
