#include "btmQTableWidgetItemWithPlayer.h"

btm::QTableWidgetItemWithPlayer::QTableWidgetItemWithPlayer(Player::pointer p):QTableWidgetItem()
{
    player = p;
}

void btm::QTableWidgetItemWithPlayer::itemChanged()
{
    DD(p);
}
