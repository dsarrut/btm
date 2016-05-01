#include "btmQTableWidgetItemWithPlayer.h"
#include <QString>

btm::QTableWidgetItemWithPlayer::QTableWidgetItemWithPlayer(btm::Player::pointer p):QTableWidgetItem()
{
    player = p;
}

void btm::QTableWidgetItemWithPlayer::Update()
{
   std::string t = text().toStdString();
    if (t != player->name)
        player->name = t;
}
