#include "btmQPlayersTableSortFilter.h"

// ----------------------------------------------------------------------------
QPlayersTableSortFilter::QPlayersTableSortFilter(QObject *parent):
    QSortFilterProxyModel(parent)
{
    setFilterCaseSensitivity(Qt::CaseInsensitive);
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
bool QPlayersTableSortFilter::lessThan(const QModelIndex & left,
                                       const QModelIndex & right) const
{
    // Special case for column "wins" (col 2)
    QVariant leftData = sourceModel()->data(left);
    QVariant rightData = sourceModel()->data(right);
    if (left.column() == 2) {
        if (leftData < rightData) return true;
        if (leftData > rightData) return false;
        QModelIndex nb_set_left = createIndex(left.row(), 3);
        QModelIndex nb_set_right = createIndex(right.row(), 3);
        return lessThan(nb_set_left, nb_set_right);
    }
    // Special case for column "sets" (col 3)
    if (left.column() == 3) {
        if (leftData < rightData) return true;
        if (leftData > rightData) return false;
        QModelIndex nb_pts_left = createIndex(left.row(), 4);
        QModelIndex nb_pts_right = createIndex(right.row(), 4);
        return lessThan(nb_pts_left, nb_pts_right);
    }
    // All other cases
    if (leftData < rightData) return true;
    else return false;
}
// ----------------------------------------------------------------------------
