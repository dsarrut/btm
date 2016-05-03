#ifndef BTMQPLAYERSTABLE_H
#define BTMQPLAYERSTABLE_H

#include <QTableWidget>
#include <btmPlayer.h>
#include <btmQPlayerTableRow.h>

namespace btm {

class QPlayersTable
{
public:
    QPlayersTable(QTableWidget * t);

    void SetPlayers(btm::Player::vector pv);
    void AddPlayer(btm::Player::pointer p);
    void Update();

    void cellChanged(int row, int column);

    QTableWidget * table;
    btm::Player::vector players;
    btm::QPlayerTableRow::vector row_items;

};

} // end namespace

#endif // BTMQPLAYERSTABLE_H
