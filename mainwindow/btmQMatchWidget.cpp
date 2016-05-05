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
    ui->labelPlayer1->setText(QString::fromStdString(match->players[0]->name));
    ui->labelPlayer2->setText(QString::fromStdString(match->players[1]->name));
    ui->labelPlayer3->setText(QString::fromStdString(match->players[2]->name));
    ui->labelPlayer4->setText(QString::fromStdString(match->players[3]->name));
    ui->lineTeam1Set1->setText(QString("%1").arg(match->sets[0]->team1_points));
    ui->lineTeam2Set1->setText(QString("%1").arg(match->sets[0]->team2_points));
    ui->lineTeam1Set2->setText(QString("%1").arg(match->sets[1]->team1_points));
    ui->lineTeam2Set2->setText(QString("%1").arg(match->sets[1]->team2_points));
    ui->lineTeam1Set3->setText(QString("%1").arg(match->sets[2]->team1_points));
    ui->lineTeam2Set3->setText(QString("%1").arg(match->sets[2]->team2_points));
}

