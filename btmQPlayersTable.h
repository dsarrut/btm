#ifndef BTMQPLAYERSTABLE_H
#define BTMQPLAYERSTABLE_H

#include <QTableWidget>
#include <btmPlayer.h>
#include <btmQTableWidgetItemWithPlayer.h>

namespace btm {

class QPlayersTable
{
public:
    QPlayersTable();

    void UpdatePlayers(btm::Player::vector * p);
    void UpdatePlayers();

    void SetRow(btm::Player::pointer p, int row);
    void SetItemText(int row, int col, QString s);
    QTableWidgetItem * NewItemColumn(int col, Player::pointer p);
    void itemChanged(QTableWidgetItem * item);

    QTableWidget * table;
    btm::Player::vector * players;

};

} // end namespace

#endif // BTMQPLAYERSTABLE_H
