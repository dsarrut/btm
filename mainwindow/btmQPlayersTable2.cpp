#include "btmQPlayersTable2.h"
#include <QLabel>

// ----------------------------------------------------------------------------
btm::QPlayersTable2::QPlayersTable2(QWidget * parent)
    :QTableWidget(parent)
{

}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
void btm::QPlayersTable2::SetTournament(btm::Tournament::pointer t)
{
    tournament = t;
    // remove previous rows
    DD("TODO: remove previous rows");
    // Add new list of players
    auto players = tournament->GetPlayers();
    setRowCount(players.size());
    for(auto p:players)
        InsertPlayer(p);
    QStringList horzHeaders;
    horzHeaders << tr("Joueurs")
                << tr("Matchs")
                << tr("Victoires")
                << tr("Sets")
                << tr("Points")
                << tr("Défaites")
                << tr("Attentes");
    setHorizontalHeaderLabels(horzHeaders);
    resizeColumnsToContents();
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
void btm::QPlayersTable2::InsertPlayer(btm::Player::pointer p)
{
    int row = rows.size();
    DD(row);
    auto r = btm::QPlayerTableRow::New(this, p, row);
    rows.push_back(r);
}
// ----------------------------------------------------------------------------


