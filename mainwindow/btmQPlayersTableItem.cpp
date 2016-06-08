#include "btmQPlayersTableItem.h"
#include "btmQPlayersTable2.h"

// ----------------------------------------------------------------------------
btm::QPlayersTableItem::
QPlayersTableItem(btm::Player::pointer p,
                  int row, int col,
                  std::string t):QTableWidgetItem()
{
    player = p;
    type = t;
    if (type == "matches") setData(Qt::DisplayRole, player->nb_of_matches);
    if (type == "sets") setData(Qt::DisplayRole, player->nb_of_win_sets);
    if (type == "points") setData(Qt::DisplayRole, player->nb_of_points);
    if (type == "loose") setData(Qt::DisplayRole, player->nb_of_lost_matches);
    if (type == "wait") setData(Qt::DisplayRole, player->nb_of_wait_rounds);

    // Connection
    // name -> playerNamedChanged()
    // match etc -> linked to a tournament ?
    // player scoreHasChanged --> on_score_changed
    //

    if (type == "name") {
        QObject::connect(p.get(), SIGNAL(playerNameChanged()),
                         this, SLOT(on_player_name_changed()));
        on_player_name_changed();
    }
    else {
        QObject::connect(p.get(), SIGNAL(playerScoreChanged()),
                         this, SLOT(on_player_score_changed()));
        on_player_score_changed();
    }

}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
btm::QPlayersTableItem::pointer
btm::QPlayersTableItem::New(btm::Player::pointer p,
                            int r, int c,
                            std::string t)
{
    return std::make_shared<QPlayersTableItem>(p, r, c, t);
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
void btm::QPlayersTableItem::itemClicked()
{
    //if (!checkable) return;
    //if (checkState() == Qt::Checked) player->participate = true;
    //else player->participate = false;
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
bool btm::QPlayersTableItem::
operator <(const QPlayersTableItem &other) const
{
    DD("sort < here");
    return (text() < other.text());
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
void btm::QPlayersTableItem::on_player_name_changed()
{
    setText(QString::fromStdString(player->GetName()));
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
void btm::QPlayersTableItem::on_player_score_changed()
{
    if (type == "matches") setData(Qt::DisplayRole, player->nb_of_matches);
    if (type == "points") setData(Qt::DisplayRole, player->nb_of_points);

}
// ----------------------------------------------------------------------------
