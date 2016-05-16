#include "btmQMatchWidget2.h"
#include "ui_btmQMatchWidget2.h"

QMatchWidget2::QMatchWidget2(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::QMatchWidget2)
{
    ui->setupUi(this);
    match = NULL;
    style_winner = "QLabel { color : green; }";
    style_looser = "QLabel { color : red; }";
    style_in_progress = "QLabel { color : black; }";
    style_switch = "QLabel { color : blue; }";
    pixWin = QPixmap(":/icons/icons/face-smile-big-2.png");
    pixLoose = QPixmap(":/icons/icons/face-crying-2.png");
}

QMatchWidget2::~QMatchWidget2()
{
    delete ui;
}

void QMatchWidget2::SetMatch(btm::Match::pointer m)
{
    DD("here set match");
    // Disconnet previous signals
    if (match != NULL) {
        QObject::disconnect(match.get(), 0, this, 0);
    }
    match = m;
    QObject::connect(match.get(), SIGNAL(matchPlayersHaveChanged()),
                     this, SLOT(on_players_changed()));
    QObject::connect(match.get(), SIGNAL(matchScoreHasChanged()),
                     this, SLOT(on_scores_changed()));
    QObject::connect(match.get(), SIGNAL(matchStatusHasChanged()),
                     this, SLOT(on_status_changed()));
    on_players_changed();
    on_scores_changed();
    on_status_changed();
}

void QMatchWidget2::SetScore(int team, int set, const QString &v)
{
    bool ok;
    int value = v.toInt(&ok);
    if (ok) match->SetScore(team, set, value);
}

void QMatchWidget2::on_players_changed()
{
    DD("widget player changed");
    QString p1 = QString::fromStdString(match->GetPlayer(0)->name);
    QString p2 = QString::fromStdString(match->GetPlayer(1)->name);
    QString p3 = QString::fromStdString(match->GetPlayer(2)->name);
    QString p4 = QString::fromStdString(match->GetPlayer(3)->name);
    ui->labelTeam1->setText(QString("%1 / %2").arg(p1).arg(p2));
    ui->labelTeam2->setText(QString("%1 / %2").arg(p3).arg(p4));

    ui->widgetPlayer1->SetPlayer(match->GetPlayer(0));
    ui->widgetPlayer2->SetPlayer(match->GetPlayer(1));
    ui->widgetPlayer3->SetPlayer(match->GetPlayer(2));
    ui->widgetPlayer4->SetPlayer(match->GetPlayer(3));

}

void QMatchWidget2::on_scores_changed()
{
    DD(" widget score changed");
    ui->lineTeam1Set1->setText(QString("%1").arg(match->GetSet(0)->GetTeam1Points()));
    ui->lineTeam2Set1->setText(QString("%1").arg(match->GetSet(0)->GetTeam2Points()));
    ui->lineTeam1Set2->setText(QString("%1").arg(match->GetSet(1)->GetTeam1Points()));
    ui->lineTeam2Set2->setText(QString("%1").arg(match->GetSet(1)->GetTeam2Points()));
    ui->lineTeam1Set3->setText(QString("%1").arg(match->GetSet(2)->GetTeam1Points()));
    ui->lineTeam2Set3->setText(QString("%1").arg(match->GetSet(2)->GetTeam2Points()));

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
}

void QMatchWidget2::on_status_changed()
{
    DD("status changed");
    if (match->GetWinner() == 1) {
        ui->labelTeam1Status->setStyleSheet(style_winner);
        ui->labelTeam2Status->setStyleSheet(style_looser);
        ui->iconTeam1->setPixmap(pixWin);
        ui->iconTeam2->setPixmap(pixLoose);
        ui->labelTeam1Status->setText("Victoire");
        ui->labelTeam2Status->setText("Défaite");
    }
    if (match->GetWinner() == 2) {
        ui->labelTeam1Status->setStyleSheet(style_looser);
        ui->labelTeam2Status->setStyleSheet(style_winner);
        ui->iconTeam1->setPixmap(pixLoose);
        ui->iconTeam2->setPixmap(pixWin);
        ui->labelTeam1Status->setText("Défaite");
        ui->labelTeam2Status->setText("Victoire");
    }
    if (match->GetWinner() == 0) {
        ui->labelTeam1Status->setStyleSheet(style_in_progress);
        ui->labelTeam2Status->setStyleSheet(style_in_progress);
        ui->iconTeam1->setPixmap(QPixmap());
        ui->iconTeam2->setPixmap(QPixmap());
        ui->labelTeam1Status->setText("");
        ui->labelTeam2Status->setText("");
    }
    QString status;
    if (match->GetStatus() == btm::Init) status = "";
    if (match->GetStatus() == btm::Terminated) status = "terminé";
    if (match->GetStatus() == btm::Playing) status = "en cours";
    ui->groupBox->setTitle(QString("Match n°%1 \t\t %2")
                           .arg(match->GetMatchNb()).arg(status));
}

void QMatchWidget2::on_lineTeam1Set1_textChanged(const QString &arg1)
{
    SetScore(1,1,arg1);
}

void QMatchWidget2::on_lineTeam1Set2_textChanged(const QString &arg1)
{
    SetScore(1,2,arg1);
}

void QMatchWidget2::on_lineTeam1Set3_textChanged(const QString &arg1)
{
    SetScore(1,3,arg1);
}

void QMatchWidget2::on_lineTeam2Set1_textChanged(const QString &arg1)
{
    SetScore(2,1,arg1);
}

void QMatchWidget2::on_lineTeam2Set2_textChanged(const QString &arg1)
{
    SetScore(2,2,arg1);
}

void QMatchWidget2::on_lineTeam2Set3_textChanged(const QString &arg1)
{
    SetScore(2,3,arg1);
}
