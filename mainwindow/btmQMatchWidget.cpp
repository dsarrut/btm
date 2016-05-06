#include "btmQMatchWidget.h"
#include "ui_btmQMatchWidget.h"

QMatchWidget::QMatchWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QMatchWidget)
{
    ui->setupUi(this);
    style_winner = "QLabel { color : green; }";
    style_looser = "QLabel { color : red; }";
    style_in_progress = "QLabel { color : black; }";
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

    // Color
    if (match->GetWinner() == 1) {
        ui->labelTeam1Status->setStyleSheet(style_winner);
        ui->labelTeam2Status->setStyleSheet(style_looser);
    }
    if (match->GetWinner() == 2) {
        ui->labelTeam1Status->setStyleSheet(style_looser);
        ui->labelTeam2Status->setStyleSheet(style_winner);
    }
    if (match->GetWinner() == 0) {
        ui->labelTeam1Status->setStyleSheet(style_in_progress);
        ui->labelTeam2Status->setStyleSheet(style_in_progress);
    }


    // Player names
    ui->labelPlayer1->setText(QString::fromStdString(match->GetPlayer(0)->name));
    ui->labelPlayer2->setText(QString::fromStdString(match->GetPlayer(1)->name));
    ui->labelPlayer3->setText(QString::fromStdString(match->GetPlayer(2)->name));
    ui->labelPlayer4->setText(QString::fromStdString(match->GetPlayer(3)->name));

    // Scores
    ui->lineTeam1Set1->setText(QString("%1").arg(match->GetSet(0)->GetTeam1Points()));
    ui->lineTeam2Set1->setText(QString("%1").arg(match->GetSet(0)->GetTeam2Points()));
    ui->lineTeam1Set2->setText(QString("%1").arg(match->GetSet(1)->GetTeam1Points()));
    ui->lineTeam2Set2->setText(QString("%1").arg(match->GetSet(1)->GetTeam2Points()));
    ui->lineTeam1Set3->setText(QString("%1").arg(match->GetSet(2)->GetTeam1Points()));
    ui->lineTeam2Set3->setText(QString("%1").arg(match->GetSet(2)->GetTeam2Points()));

    // First set
    ui->lineTeam1Set1->setEnabled(true);
    ui->lineTeam1Set1->setEnabled(true);

    // Second set
    if (match->GetSet(0)->GetWinner() == 0) {
        ui->lineTeam1Set2->setEnabled(false);
        ui->lineTeam2Set2->setEnabled(false);
    }
    else {
        ui->lineTeam1Set2->setEnabled(true);
        ui->lineTeam2Set2->setEnabled(true);
    }

    // Third set
    if (match->GetSet(0)->GetWinner() != 0 and
        match->GetSet(1)->GetWinner() != 0 and
        match->GetSet(0)->GetWinner() != match->GetSet(1)->GetWinner()) {
        ui->lineTeam1Set3->setEnabled(true);
        ui->lineTeam2Set3->setEnabled(true);
    }
    else {
        ui->lineTeam1Set3->setEnabled(false);
        ui->lineTeam2Set3->setEnabled(false);
    }

    // Match nb
    QString status;
    if (match->GetStatus() == btm::Init) status = "";
    if (match->GetStatus() == btm::Terminated) status = "terminé";
    if (match->GetStatus() == btm::Playing) status = "en cours";
    ui->groupBox->setTitle(QString("Match n°%1 \t\t %2")
                           .arg(match->GetMatchNb()).arg(status));

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

void QMatchWidget::SetScore(int team, int set, const QString & v)
{
    bool ok;
    int value = v.toInt(&ok);
    if (ok) {
        match->SetScore(team,set, value);
        //if (team == 1) match->GetSet(set)->team1_points = value;
        //else match->GetSet(set)->team2_points = value;
    }
    Update();
}

void QMatchWidget::on_lineTeam1Set1_textEdited(const QString &arg1)
{
    SetScore(1,1,arg1);
}

void QMatchWidget::on_lineTeam1Set2_textEdited(const QString &arg1)
{
    SetScore(1,2,arg1);
}

void QMatchWidget::on_lineTeam1Set3_textEdited(const QString &arg1)
{
    SetScore(1,3,arg1);
}

void QMatchWidget::on_lineTeam2Set1_textEdited(const QString &arg1)
{
    SetScore(2,1,arg1);
}

void QMatchWidget::on_lineTeam2Set2_textEdited(const QString &arg1)
{
    SetScore(2,2,arg1);
}

void QMatchWidget::on_lineTeam2Set3_textEdited(const QString &arg1)
{
    SetScore(2,3,arg1);
}
