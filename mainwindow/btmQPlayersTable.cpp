#include "btmQPlayersTable.h"

btm::QPlayersTable::QPlayersTable(QTableWidget * t)
{
    table = t;
}

void btm::QPlayersTable::SetPlayers(btm::Player::vector pv)
{
    players.clear();
    table->setRowCount(pv.size());
    table->blockSignals(true);
    for(auto p:pv) AddPlayer(p);
    Update();
    table->blockSignals(false);
}

void btm::QPlayersTable::AddPlayer(btm::Player::pointer p)
{
    players.push_back(p);
    table->setRowCount(players.size());
    int r = players.size()-1;
    btm::QPlayerTableRow::pointer row = btm::QPlayerTableRow::New(p, table, r);
    row_items.push_back(row);
}

void btm::QPlayersTable::Update()
{
    table->blockSignals(true);
    for(auto r:row_items) r->Update();
    table->blockSignals(false);
}

void btm::QPlayersTable::cellChanged(int row, int column)
{
    if (column == 0) {
        auto item = table->item(row, column);
        auto a = static_cast<btm::QTableWidgetItemWithPlayer*>(item);
        a->Update();
    }
}



