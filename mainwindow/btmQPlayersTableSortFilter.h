#ifndef QPLAYERSTABLESORTFILTER_H
#define QPLAYERSTABLESORTFILTER_H

#include "btmDD.h"
#include <QSortFilterProxyModel>

class QPlayersTableSortFilter : public QSortFilterProxyModel
{
public:
    QPlayersTableSortFilter(QObject *parent = Q_NULLPTR);
    void SetFilter(const QString &arg);

protected:
    bool lessThan(const QModelIndex &source_left,
                  const QModelIndex &source_right) const;
    bool filterAcceptsRow(int sourceRow,
                          const QModelIndex &sourceParent) const;
    QString filter;

};

#endif // QPLAYERSTABLESORTFILTER_H
