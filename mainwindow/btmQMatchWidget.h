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
    void SetScore(int set, int team, const QString & v);

protected:
    btm::Match::pointer match;

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
