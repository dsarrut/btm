#include "btmQPlayerTableRow.h"
#include "btmQPlayersTable2.h"
#include "btmQTableWidgetItemWithPlayer.h"

// ----------------------------------------------------------------------------
btm::QPlayerTableRow::QPlayerTableRow(btm::QPlayersTable2 * t,
                                      btm::Player::pointer p,
                                      int row)
{
    player = p;
    table = t;
    /*
    items.resize(7);
    InsertItem(row, 0, true);  // name
    items[0]->checkable = true;
    InsertItem(row, 1, false); // matches
    InsertItem(row, 2, false); // victory
    InsertItem(row, 3, false); // sets
    InsertItem(row, 4, false); // points
    InsertItem(row, 5, false); // loose
    InsertItem(row, 6, false); // wait
    */
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
void btm::QPlayerTableRow::InsertItem(int row, int col, bool editable)
{
    /*
    QTableWidgetItemWithPlayer * item = new QTableWidgetItemWithPlayer(player);
    if (!editable)
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    table->setItem(row, col, item);
    items[col] = item;
    */
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
void btm::QPlayerTableRow::Update()
{
    /*
    items[0]->setText(QString::fromStdString(player->name));
    if (player->participate)
        items[0]->setCheckState(Qt::CheckState::Checked);
    else
        items[0]->setCheckState(Qt::CheckState::Unchecked);
    items[1]->setData(Qt::DisplayRole, player->nb_of_matches);
    items[2]->setData(Qt::DisplayRole, player->nb_of_win_matches);
    items[3]->setData(Qt::DisplayRole, player->nb_of_win_sets);
    items[4]->setData(Qt::DisplayRole, player->nb_of_points);
    items[5]->setData(Qt::DisplayRole, player->nb_of_lost_matches);
    items[6]->setData(Qt::DisplayRole, player->nb_of_wait_rounds);
*/
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
