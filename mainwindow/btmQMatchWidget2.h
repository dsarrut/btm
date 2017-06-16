#ifndef BTMQMATCHWIDGET2_H
#define BTMQMATCHWIDGET2_H

#include <QFrame>
#include "btmMatch.h"

namespace Ui {
class QMatchWidget2;
}

class QMatchWidget2 : public QFrame
{
    Q_OBJECT

public:
    explicit QMatchWidget2(QWidget *parent = 0);
    ~QMatchWidget2();

    void SetMatch(btm::Match::pointer m);
    void SetScore(int team, int set, const QString & v);
    void SetSwapPlayerMode(bool b);
    void ConnectPlayerSelection(QObject *o);
    void ResetSelection();


public slots:
    void onPlayersChanged();
    void onStatusChanged();
    void onScoresChanged();

protected:
    btm::Match::pointer match;
    QString style_winner;
    QString style_looser;
    QString style_in_progress;
    QString style_Swap;
    QPixmap pixWin;
    QPixmap pixLoose;

private slots:
    void on_lineTeam1Set1_textChanged(const QString &arg1);
    void on_lineTeam1Set2_textChanged(const QString &arg1);
    void on_lineTeam1Set3_textChanged(const QString &arg1);
    void on_lineTeam2Set1_textChanged(const QString &arg1);
    void on_lineTeam2Set2_textChanged(const QString &arg1);
    void on_lineTeam2Set3_textChanged(const QString &arg1);

private:
    Ui::QMatchWidget2 *ui;
};

#endif // BTMQMATCHWIDGET2_H
