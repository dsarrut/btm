#ifndef BTMQROUNDWIDGET2_H
#define BTMQROUNDWIDGET2_H

#include <QFrame>
#include <QGridLayout>
#include "btmRound.h"
#include "btmQMatchWidget2.h"

namespace Ui {
class QRoundWidget2;
}

class QRoundWidget2 : public QFrame
{
    Q_OBJECT

public:
    explicit QRoundWidget2(QWidget *parent = 0);
    ~QRoundWidget2();

    void SetRound(btm::Round::pointer r);
    void SetNumberOfColumns(int i);
    void SetSwitchPlayerMode(bool b);
    bool GetSwitchPlayerMode() const;

protected:
    btm::Round::pointer round;
    std::vector<QMatchWidget2*> matchWidgets;
    QGridLayout * gridLayout;
    int nbOfColumns;
    bool switchPlayerMode;

private:
    Ui::QRoundWidget2 *ui;
};

#endif // BTMQROUNDWIDGET2_H
