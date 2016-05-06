#ifndef QMATCHWIDGET_H
#define QMATCHWIDGET_H

#include <QWidget>
#include <QLabel>
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

public slots:
    void Update();

protected:
    btm::Match::pointer match;
    QString style_winner;
    QString style_looser;
    QString style_in_progress;
    std::vector<QLabel*> labels;

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
