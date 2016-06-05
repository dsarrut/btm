#include "btmQTableWidgetItemWithPlayer.h"
#include <QString>

// ----------------------------------------------------------------------------
btm::QTableWidgetItemWithPlayer::
QTableWidgetItemWithPlayer(btm::Player::pointer p):QTableWidgetItem()
{
    player = p;
    checkable = false;
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
void btm::QTableWidgetItemWithPlayer::Update()
{
    std::string t = text().toStdString();
    if (t != player->name) player->name = t;
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
void btm::QTableWidgetItemWithPlayer::itemClicked()
{
    if (!checkable) return;
    if (checkState() == Qt::Checked) player->participate = true;
    else player->participate = false;
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
bool btm::QTableWidgetItemWithPlayer::
operator <(const QTableWidgetItemWithPlayer &other) const
{
    DD("sort < here");
    return text() < other.text());
}
// ----------------------------------------------------------------------------
