#ifndef QPLAYERSTABLE2_H
#define QPLAYERSTABLE2_H

#include <QTableWidget>
#include "btmTournament.h"

namespace btm {

// ----------------------------------------------------------------------------
class QPlayersTable2 : public QTableWidget
{
public:
    QPlayersTable2(QWidget * parent);

    void SetTournament(btm::Tournament::pointer t);

protected:
    btm::Tournament::pointer tournament;
    void InsertPlayer(btm::Player::pointer p);

};
// ----------------------------------------------------------------------------

} // end namespace

#endif // QPLAYERSTABLE2_H
