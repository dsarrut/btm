#include "btmQPlayersTable.h"

btm::QPlayersTable::QPlayersTable()
{

}

void btm::QPlayersTable::UpdatePlayers(btm::Player::vector *p)
{
    players = p;
    UpdatePlayers();
}

void btm::QPlayersTable::UpdatePlayers()
{
    table->setRowCount(players->size());
    int n=0;
    for(auto p:*players) {
        SetRow(p, n);
        ++n;
    }
}

void btm::QPlayersTable::SetRow(btm::Player::pointer p,
                                int row)
{
    SetItemText(row, 0, QString::fromStdString(p->name));
    SetItemText(row, 1, QString("%1").arg(p->nb_of_matches));
    SetItemText(row, 2, QString("%1").arg(p->nb_of_win_matches));
    SetItemText(row, 3, QString("%1").arg(p->nb_of_lost_matches));
    SetItemText(row, 4, QString("%1").arg(p->nb_of_wait_rounds));
}

void btm::QPlayersTable::SetItemText(int row,
                                     int col,
                                     QString s)
{
    auto item = table->item(row,col);
    if (item == 0) {
        item = NewItemColumn(col, player);
        table->setItem(row,col, item);
    }
    item->setText(s);
}

QTableWidgetItem * btm::QPlayersTable::NewItemColumn(int col, btm::Player::pointer p)
{
    auto item = new QTableWidgetItemWithPlayer();
    if (col !=0 )
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    return item;
}
