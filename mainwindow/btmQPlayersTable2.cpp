#include "btmQPlayersTable2.h"
#include <QHeaderView>

// ----------------------------------------------------------------------------
btm::QPlayersTable2::QPlayersTable2(QTableView *view):
    QAbstractTableModel(view)
{
    proxyModel = new QPlayersTableSortFilter(this);
    proxyModel->setSourceModel(this);
    view->setModel(proxyModel);
    view->setSortingEnabled(true);
    view->setAlternatingRowColors(true);
    view->horizontalHeader()->setStretchLastSection(true);
    view->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
void btm::QPlayersTable2::SetTournament(btm::Tournament::pointer t)
{
    int n=0;
    if (tournament)
        n = tournament->GetPlayers().size();
    tournament = t;
    // remove previous rows
    removeRows(0, n);

    // Add new list of players
    auto & players = tournament->GetPlayers();
    insertRows(0,players.size());

    for(auto p:players) {
        connect(p.get(),
                SIGNAL(playerParticipateFlagChanged(btm::Player::pointer)),
                this,
                SLOT(on_playerParticipateFlag_changed(btm::Player::pointer)));
    }
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
void btm::QPlayersTable2::SetFilter(const QString &arg)
{
    proxyModel->SetFilter(arg);
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
int btm::QPlayersTable2::rowCount(const QModelIndex &) const
{
    if (!tournament) return 0;
    auto players = tournament->GetPlayers();
    return players.size();
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
int btm::QPlayersTable2::columnCount(const QModelIndex &) const
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
        if (col == 3) return player->nb_of_win_sets;
        if (col == 4) return player->nb_of_points;
        if (col == 5) return player->nb_of_lost_matches;
        if (col == 6) return player->nb_of_wait_rounds;
        //if (col == 7) return true;
        return QString("Row%1, Column%2")
                .arg(index.row() + 1)
                .arg(index.column() +1);
    }
    if (role == Qt::EditRole) {
        return QString::fromStdString(player->GetName());
    }
    if (role == Qt::CheckStateRole) {
        if (col == 0) {
            if (player->GetParticipateFlag()) return 2;
            else return 0;
        }
        else return QVariant();
    }
    return QVariant();
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
bool btm::QPlayersTable2::insertRows(int row, int count,
                                     const QModelIndex & index)
{
    beginInsertRows(QModelIndex(), row, row+count-1);
    endInsertRows();
    return true;
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
bool btm::QPlayersTable2::removeRows(int row, int count,
                                     const QModelIndex &)
{
    beginRemoveRows(QModelIndex(), row, row+count-1);
    endRemoveRows();
    return true;
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
Qt::ItemFlags btm::QPlayersTable2::flags(const QModelIndex &index) const
{
    // only name first column is editable
    int col = index.column();
    if (col == 0) {
        return (QAbstractTableModel::flags(index)
                | Qt::ItemIsEditable | Qt::ItemIsUserCheckable);
    }
    return  QAbstractTableModel::flags(index);
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
bool btm::QPlayersTable2::setData(const QModelIndex &index,
                                  const QVariant &value,
                                  int role)
{
    int row = index.row();
    auto player = tournament->GetPlayer(row);
    // only column "name" could be edited
    if (index.isValid() and role == Qt::EditRole) {
        player->SetName(value.toString().toStdString());
        SetFilter("");
        emit dataChanged(index, index);
    }
    // Toggle check (player participate or not)
    if (index.isValid() and role == Qt::CheckStateRole) {
        auto b = !player->GetParticipateFlag();
        player->SetParticipateFlag(b);
        emit dataChanged(index, index);
    }
    return false;
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
QVariant btm::QPlayersTable2::headerData(int section,
                                         Qt::Orientation orientation,
                                         int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0: return tr("Nom");
        case 1: return tr("Matchs");
        case 2: return tr("Victoires");
        case 3: return tr("Sets");
        case 4: return tr("Points");
        case 5: return tr("Défaites");
        case 6: return tr("Attentes");
        default: return "Unknown!";
        }
    }
    else {
        auto & player = tournament->GetPlayers()[section];
        return player->GetId();
    }
    return QVariant();
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
void btm::QPlayersTable2::on_playerParticipateFlag_changed(btm::Player::pointer p)
{
    QModelIndex index = createIndex(p->GetId(), 0);
    emit dataChanged(index, index);
}
// ----------------------------------------------------------------------------

