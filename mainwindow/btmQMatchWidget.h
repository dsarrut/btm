#ifndef QMATCHWIDGET_H
#define QMATCHWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
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
    void SetScore(int team, int set, const QString & v);
    void enableModeSwitchPlayer(bool b);
    btm::Match::pointer GetMatch() { return match; }
    void UncheckSwitch();

public slots:
    void Update();

protected:
    btm::Match::pointer match;
    QString style_winner;
    QString style_looser;
    QString style_in_progress;
    QString style_switch;
    std::vector<QLabel*> labels;
    bool switchPlayerMode;

signals:
    void matchScoreChanged(btm::Match::pointer m);
    void playerSwitched(QMatchWidget *, int player);

private slots:
    void on_lineTeam1Set1_textEdited(const QString &arg1);
    void on_lineTeam1Set2_textEdited(const QString &arg1);
    void on_lineTeam1Set3_textEdited(const QString &arg1);
    void on_lineTeam2Set1_textEdited(const QString &arg1);
    void on_lineTeam2Set2_textEdited(const QString &arg1);
    void on_lineTeam2Set3_textEdited(const QString &arg1);
    void on_radioButtonTeam1Player1_toggled(bool checked);
    void on_radioButtonTeam1Player2_toggled(bool checked);
    void on_radioButtonTeam2Player1_toggled(bool checked);
    void on_radioButtonTeam2Player2_toggled(bool checked);

private:
    Ui::QMatchWidget *ui;
};

#endif // QMatchWidget_H
