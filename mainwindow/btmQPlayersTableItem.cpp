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
    setText("toto");
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
