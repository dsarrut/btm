#ifndef QMATCHWIDGET_H
#define QMATCHWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include "btmTournament.h"
#include "btmQPlayerWidget.h"

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
    void SetPlayer(int player, btm::Player::pointer p);
    void enableModeSwitchPlayer(bool b);
    void ResetSelection();
    void ChangePlayer(btm::Player::pointer p1,
                      btm::Player::pointer p2);
    btm::Match::pointer GetMatch() { return match; }
    void SetEditableScore(bool b);

public slots:
    void on_match_changed();

protected:
    btm::Match::pointer match;
    QString style_winner;
    QString style_looser;
    QString style_in_progress;
    QString style_switch;
    std::vector<QLabel*> labels;
    bool switchPlayerMode;
    std::vector<QPlayerWidget*> playerWidgets;
    QPixmap pixWin;
    QPixmap pixLoose;
    bool scoresAreEditable;

signals:
    void matchScoreChanged(btm::Match::pointer m);

private slots:
    void on_lineTeam1Set1_textEdited(const QString &arg1);
    void on_lineTeam1Set2_textEdited(const QString &arg1);
    void on_lineTeam1Set3_textEdited(const QString &arg1);
    void on_lineTeam2Set1_textEdited(const QString &arg1);
    void on_lineTeam2Set2_textEdited(const QString &arg1);
    void on_lineTeam2Set3_textEdited(const QString &arg1);

private:
    Ui::QMatchWidget *ui;
};

#endif // QMatchWidget_H
