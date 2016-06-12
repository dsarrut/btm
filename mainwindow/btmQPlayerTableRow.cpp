#include "btmQPlayerTableRow.h"
#include "btmQPlayersTable2.h"
#include "btmQPlayersTableItem.h"

// ----------------------------------------------------------------------------
btm::QPlayerTableRow::QPlayerTableRow(btm::QPlayersTable2 * t,
                                      btm::Player::pointer p,
                                      int r)
{
    player = p;
    table = t;
    row = r;
    //table->setColumnCount(7);
    InsertItem(0, "name");
    InsertItem(1, "matches");
    InsertItem(2, "win");
    InsertItem(3, "sets");
    InsertItem(4, "points");
    InsertItem(5, "loose");
    InsertItem(6, "wait");
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
void btm::QPlayerTableRow::InsertItem(int col, std::string type)
{
    auto item = QPlayersTableItem::New(player, row, col, type);
    //table->setItem(row, col, item.get());
    items.push_back(item);
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
btm::QPlayerTableRow::pointer btm::QPlayerTableRow::New(QPlayersTable2 *table,
                                                        btm::Player::pointer player,
                                                        int row)
{
    return std::make_shared<QPlayerTableRow>(table, player, row);
}
// ----------------------------------------------------------------------------

