#ifndef QPLAYERTableRow_H
#define QPLAYERTableRow_H

#include <btmPlayer.h>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "btmQTableWidgetItemWithPlayer.h"

namespace btm {
class QPlayerTableRow
{

public:
    QPlayerTableRow(btm::Player::pointer p, QTableWidget * t, int r);

    typedef std::shared_ptr<QPlayerTableRow> pointer;
    typedef std::vector<pointer> vector;
    static pointer New(btm::Player::pointer p, QTableWidget * t, int r);

    void InsertItem(int row, int col, bool editable);
    void Update();

    btm::Player::pointer player;
    QTableWidget * table;
    std::vector<QTableWidgetItemWithPlayer*> items;

};

} // end namespace
#endif // QPLAYERTableRow_H
