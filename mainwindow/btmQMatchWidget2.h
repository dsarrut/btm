#ifndef BTMQMATCHWIDGET2_H
#define BTMQMATCHWIDGET2_H

#include <QFrame>
#include "btmMatch.h"
#include "btmQRoundWidget2.h"

namespace Ui {
class QMatchWidget2;
}

class QRoundWidget2;

class QMatchWidget2 : public QFrame
{
    Q_OBJECT

public:
    explicit QMatchWidget2(QWidget *parent = 0);
    ~QMatchWidget2();

    void SetMatch(btm::Match::pointer m);
    void SetScore(int team, int set, const QString & v);
    void SetSwitchPlayerMode(bool b);
    void ConnectPlayerSelection(QRoundWidget2 *o);

public slots:
    void on_players_changed();
    void on_scores_changed();
    void on_status_changed();
    void on_test();

protected:
    btm::Match::pointer match;
    QString style_winner;
    QString style_looser;
    QString style_in_progress;
    QString style_switch;
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
