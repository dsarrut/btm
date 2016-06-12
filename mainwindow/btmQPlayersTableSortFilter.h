#ifndef QPLAYERSTABLESORTFILTER_H
#define QPLAYERSTABLESORTFILTER_H

#include "btmDD.h"
#include <QSortFilterProxyModel>

class QPlayersTableSortFilter : public QSortFilterProxyModel
{
public:
    QPlayersTableSortFilter(QObject *parent = Q_NULLPTR);

protected:
    bool lessThan(const QModelIndex &source_left,
                  const QModelIndex &source_right) const;

};

#endif // QPLAYERSTABLESORTFILTER_H
