#include "btmQPlayersTableItem.h"
#include "btmQPlayersTable2.h"

// ----------------------------------------------------------------------------
btm::QPlayersTableItem::
QPlayersTableItem(btm::Player::pointer p,
                  int row, int col,
                  std::string t):QTableWidgetItem()
{
    player = p;
    type = t;
    if (type == "name") setText(QString::fromStdString(player->GetName()));
    if (type == "matches") setData(Qt::DisplayRole, player->nb_of_matches);
    if (type == "sets") setData(Qt::DisplayRole, player->nb_of_win_sets);
    if (type == "points") setData(Qt::DisplayRole, player->nb_of_points);
    if (type == "loose") setData(Qt::DisplayRole, player->nb_of_lost_matches);
    if (type == "wait") setData(Qt::DisplayRole, player->nb_of_wait_rounds);
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
btm::QPlayersTableItem::pointer btm::QPlayersTableItem::New(btm::Player::pointer p,
                                                            int r, int c,
                                                            std::string t)
{
    return std::make_shared<QPlayersTableItem>(p, r, c, t);
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
void btm::QPlayersTableItem::itemClicked()
{
    //if (!checkable) return;
    //if (checkState() == Qt::Checked) player->participate = true;
    //else player->participate = false;
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
bool btm::QPlayersTableItem::
operator <(const QPlayersTableItem &other) const
{
    DD("sort < here");
    return (text() < other.text());
}
// ----------------------------------------------------------------------------
