#ifndef QPLAYERSTABLEITEM__H
#define QPLAYERSTABLEITEM__H

#include <QObject>
#include <QTableWidgetItem>
#include "btmPlayer.h"

namespace btm {

class QPlayersTable2;

// ----------------------------------------------------------------------------
class QPlayersTableItem : public QObject, public QTableWidgetItem
{
    Q_OBJECT

public:
    QPlayersTableItem(btm::Player::pointer player,
                      int row, int col, std::string type);

    // Types and pointer
    typedef std::shared_ptr<QPlayersTableItem> pointer;
    typedef std::vector<pointer> vector;
    static pointer New(btm::Player::pointer p,
                       int r, int c, std::string t);


    //void Update();
    void itemClicked();

    bool operator <(const QPlayersTableItem &other) const;

public slots:
    void on_player_name_changed();
    void on_player_score_changed();

protected:
    //bool checkable;
    btm::QPlayersTable2 * table;
    btm::Player::pointer player;
    std::string type;

};
// ----------------------------------------------------------------------------

} // end namespace

#endif // QPLAYERSTABLEITEM__H
