#ifndef QPLAYERTableRow_H
#define QPLAYERTableRow_H

#include <btmPlayer.h>
#include <QTableWidgetItem>
#include "btmQTableWidgetItemWithPlayer.h"

namespace btm {

class QPlayersTable2;

// ----------------------------------------------------------------------------
class QPlayerTableRow
{

public:
    QPlayerTableRow(btm::QPlayersTable2 * t,
                    btm::Player::pointer p,
                    int row);

    typedef std::shared_ptr<QPlayerTableRow> pointer;
    typedef std::vector<pointer> vector;
    static pointer New(btm::QPlayersTable2 * t,
                       btm::Player::pointer p,
                       int row);

    void InsertItem(int row, int col, bool editable);
    void Update();

protected:
    btm::Player::pointer player;
    btm::QPlayersTable2* table;
    std::vector<QTableWidgetItemWithPlayer*> items;

};
// ----------------------------------------------------------------------------

} // end namespace
#endif // QPLAYERTableRow_H
