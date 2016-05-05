#ifndef QMATCHWIDGET_H
#define QMATCHWIDGET_H

#include <QWidget>
#include "btmTournament.h"

namespace Ui {
class QMatchWidget;
}

class QMatchWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QMatchWidget(QWidget *parent = 0);
    ~QMatchWidget();

    void SetMatch(btm::Match::pointer m);
    void Update();

protected:
    btm::Match::pointer match;

private:
    Ui::QMatchWidget *ui;
};

#endif // QMatchWidget_H
