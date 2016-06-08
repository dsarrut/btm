#ifndef QPLAYERTableRow_H
#define QPLAYERTableRow_H

#include <btmPlayer.h>
#include <QTableWidgetItem>
#include "btmQPlayersTableItem.h"

namespace btm {

class QPlayersTable2;

// ----------------------------------------------------------------------------
class QPlayerTableRow
{

public:
    // Constructor
    QPlayerTableRow(btm::QPlayersTable2 * t,
                    btm::Player::pointer p,
                    int row);

    // Types and pointer
    typedef std::shared_ptr<QPlayerTableRow> pointer;
    typedef std::vector<pointer> vector;
    static pointer New(btm::QPlayersTable2 * t,
                       btm::Player::pointer p,
                       int row);

public slots:
    void on_player_score_changed();

protected:
    btm::Player::pointer player;
    btm::QPlayersTable2* table;
    int row;
    std::vector<QPlayersTableItem::pointer> items;
    void InsertItem(int col, std::string type);

};
// ----------------------------------------------------------------------------

} // end namespace
#endif // QPLAYERTableRow_H
