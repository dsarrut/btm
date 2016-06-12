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
public:
    QPlayersTable2(QTableView * view);

    void SetTournament(btm::Tournament::pointer t);

    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool insertRows(int row, int count,
                    const QModelIndex &parent = QModelIndex());
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index,
                 const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

protected:
    btm::Tournament::pointer tournament;
    //btm::QPlayerTableRow::vector rows;


};
// ----------------------------------------------------------------------------

} // end namespace

#endif // QPLAYERSTABLE2_H
