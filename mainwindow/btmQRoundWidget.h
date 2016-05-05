#ifndef BTMQROUNDWIDGET_H
#define BTMQROUNDWIDGET_H

#include <QFrame>
#include "btmTournament.h"
#include "btmQMatchWidget.h"

namespace Ui {
class QRoundWidget;
}

class QRoundWidget : public QFrame
{
    Q_OBJECT

public:
    explicit QRoundWidget(QWidget *parent = 0);
    ~QRoundWidget();

    void SetTournament(btm::Tournament::pointer tournament);
    void Update();
    void AddWidget();

protected:
    btm::Tournament::pointer tournament;
    btm::Round::pointer round;
    std::vector<QMatchWidget*> widgetMatches;

signals:
    void newRound();

private slots:
    void on_buttonRandomScores_clicked();
    void on_buttonNewRound_clicked();

private:
    Ui::QRoundWidget *ui;
};

#endif // BTMQROUNDWIDGET_H
