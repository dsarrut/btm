#include "btmQPlayersTable2.h"

// ----------------------------------------------------------------------------
btm::QPlayersTable2::QPlayersTable2(QTableView *view):
    QAbstractTableModel(view)
{
    QSortFilterProxyModel * proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel( this );
    view->setModel(proxyModel);
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
void btm::QPlayersTable2::SetTournament(btm::Tournament::pointer t)
{
    tournament = t;
    // remove previous rows
    DD("TODO: QPlayersTable2::SetTournament remove previous rows");

    // Add new list of players
    auto & players = tournament->GetPlayers();
    insertRows(0,players.size());
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
int btm::QPlayersTable2::rowCount(const QModelIndex &parent) const
{
    if (!tournament) return 0;
    auto players = tournament->GetPlayers();
    return players.size();
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
int btm::QPlayersTable2::columnCount(const QModelIndex &parent) const
{
    return 7;
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
QVariant btm::QPlayersTable2::data(const QModelIndex &index, int role) const
{
    if (!tournament) return QVariant();
    int row = index.row();
    int col = index.column();
    auto & players = tournament->GetPlayers();
    auto & player = players[row];
    if (role == Qt::DisplayRole) {
        if (col == 0) return QString::fromStdString(player->GetName());
        if (col == 1) return player->nb_of_matches;
        if (col == 2) return player->nb_of_win_matches;
        if (col == 3) return player->nb_of_points;
        if (col == 4) return player->nb_of_win_sets;
        if (col == 5) return player->nb_of_lost_matches;
        if (col == 6) return player->nb_of_wait_rounds;
        return QString("Row%1, Column%2")
                .arg(index.row() + 1)
                .arg(index.column() +1);
    }
    return QVariant();
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
bool btm::QPlayersTable2::insertRows(int row, int count,
                                     const QModelIndex &parent)
{
    DDF();
    beginInsertRows(QModelIndex(), row, row+count-1);
    endInsertRows();
    return true;
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
Qt::ItemFlags btm::QPlayersTable2::flags(const QModelIndex &index) const
{
    // only name first column is editable
    int col = index.column();
    if (col == 0)
        return (QAbstractTableModel::flags(index) | Qt::ItemIsEditable);
    return  QAbstractTableModel::flags(index);
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
bool btm::QPlayersTable2::setData(const QModelIndex &index,
                                  const QVariant &value,
                                  int role)
{
    DDF();
    if (index.isValid() && role == Qt::EditRole) {
        int row = index.row();
        DD(row);
        auto & players = tournament->GetPlayers();
        auto player = players[row];
        player->SetName(value.toString().toStdString());
        emit dataChanged(index, index);
    }
    return false;
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
/*void btm::QPlayersTable2::sort(int column, Qt::SortOrder order)
{
    DDF();
    QAbstractTableModel::sort(column, order);
}*/
// ----------------------------------------------------------------------------


