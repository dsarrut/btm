#include "btmQMatchWidget.h"
#include "ui_btmQMatchWidget.h"

QMatchWidget::QMatchWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QMatchWidget)
{
    ui->setupUi(this);
}

QMatchWidget::~QMatchWidget()
{
    delete ui;
}

void QMatchWidget::SetMatch(btm::Match::pointer m)
{
    match = m;
    Update();
}

void QMatchWidget::Update()
{
    // Player names
    ui->labelPlayer1->setText(QString::fromStdString(match->players[0]->name));
    ui->labelPlayer2->setText(QString::fromStdString(match->players[1]->name));
    ui->labelPlayer3->setText(QString::fromStdString(match->players[2]->name));
    ui->labelPlayer4->setText(QString::fromStdString(match->players[3]->name));

    // Scores
    ui->lineTeam1Set1->setText(QString("%1").arg(match->sets[0]->team1_points));
    ui->lineTeam2Set1->setText(QString("%1").arg(match->sets[0]->team2_points));
    ui->lineTeam1Set2->setText(QString("%1").arg(match->sets[1]->team1_points));
    ui->lineTeam2Set2->setText(QString("%1").arg(match->sets[1]->team2_points));
    ui->lineTeam1Set3->setText(QString("%1").arg(match->sets[2]->team1_points));
    ui->lineTeam2Set3->setText(QString("%1").arg(match->sets[2]->team2_points));

    // Match nb
    ui->groupBox->setTitle(QString("Match n°%1").arg(match->match_nb));

    // Status win/loose
    if (match->GetWinner() == 1) {
        ui->labelTeam1Status->setText("Victoire");
        ui->labelTeam2Status->setText("Défaite");
    }
    if (match->GetWinner() == 2) {
        ui->labelTeam2Status->setText("Victoire");
        ui->labelTeam1Status->setText("Défaite");
    }
    if (match->GetWinner() == 0) {
        ui->labelTeam1Status->setText("");
        ui->labelTeam2Status->setText("");
    }
}

void QMatchWidget::SetScore(int set, int team, const QString & v)
{
    bool ok;
    int value = v.toInt(&ok);
    if (ok) {
        if (team == 1) match->sets[set]->team1_points = value;
        else match->sets[set]->team2_points = value;
    }
    Update();
}

void QMatchWidget::on_lineTeam1Set1_textEdited(const QString &arg1)
{
    SetScore(0,1,arg1);
}

void QMatchWidget::on_lineTeam1Set2_textEdited(const QString &arg1)
{
    SetScore(1,1,arg1);
}

void QMatchWidget::on_lineTeam1Set3_textEdited(const QString &arg1)
{
    SetScore(2,1,arg1);
}

void QMatchWidget::on_lineTeam2Set1_textEdited(const QString &arg1)
{
    SetScore(0,2,arg1);
}

void QMatchWidget::on_lineTeam2Set2_textEdited(const QString &arg1)
{
    SetScore(1,2,arg1);
}

void QMatchWidget::on_lineTeam2Set3_textEdited(const QString &arg1)
{
    SetScore(2,2,arg1);
}
