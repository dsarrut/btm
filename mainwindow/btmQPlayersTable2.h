#ifndef QPLAYERSTABLE2_H
#define QPLAYERSTABLE2_H

#include <QAbstractTableModel>
#include <QTableView>

#include "btmTournament.h"
#include "btmQPlayersTableSortFilter.h"

namespace btm {

// ----------------------------------------------------------------------------
class QPlayersTable2 : public QAbstractTableModel
{
    Q_OBJECT

public:
    QPlayersTable2(QTableView * view);

    void SetTournament(btm::Tournament::pointer t);
    void SetFilter(const QString & arg);

    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool insertRows(int row, int count,
                    const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count,
                    const QModelIndex &parent = QModelIndex());
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index,
                 const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

public slots:
    void on_playerParticipateFlag_changed(btm::Player::pointer p);

protected:
    btm::Tournament::pointer tournament;
    QPlayersTableSortFilter * proxyModel;

};
// ----------------------------------------------------------------------------

} // end namespace

#endif // QPLAYERSTABLE2_H
