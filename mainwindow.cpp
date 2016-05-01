#include "mainwindow.h"
#include "ui_mainwindow.h"

//----------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    players_table.table = ui->tablePlayers;
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void MainWindow::SetStatus(std::string & s)
{
    ui->textCurrentyRoundStatus->setPlainText(QString::fromStdString(s));
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void MainWindow::AddToStatus(std::string & s)
{
    QString ss = ui->textCurrentyRoundStatus->toPlainText()
            +QString::fromStdString(s);
    ui->textCurrentyRoundStatus->setPlainText(ss);
}
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
void MainWindow::on_pushButton_clicked()
{
    auto round = tournament.StartNewRound();
    UpdateDisplayCurrentRound();
    UpdateDisplayPlayersStatus();
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void MainWindow::on_pushButton_rnd_players_clicked()
{
    btm::Player::vector players;
    btm::GenerateRandomPlayers(players, 31);
    for(auto p:players) DD(p);
    std::cout << std::endl;
    tournament.players = players;
    players_table.UpdatePlayers(&tournament.players);
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void MainWindow::on_pushButton_rnd_scores_clicked()
{
    tournament.GenerateRandomScores(tournament.rounds.back());
    UpdateDisplayCurrentRound();
    UpdateDisplayPlayersStatus();
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void MainWindow::UpdateDisplayCurrentRound()
{
    auto round = tournament.rounds.back();
    QString s = QString::fromStdString(round->ToString());
    ui->textCurrentyRoundStatus->setPlainText(s);
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void MainWindow::UpdateDisplayPlayersStatus()
{
    tournament.ComputePlayersStatus();
    auto x = tournament.GetPlayersStatus();
    QString s = QString::fromStdString(x);
    ui->textPlayersStatus->setPlainText(s);
    players_table.UpdatePlayers();
}
//----------------------------------------------------------------------------




void MainWindow::on_tablePlayers_itemChanged(QTableWidgetItem *item)
{
    btm::QTableWidgetItemWithPlayer * a =
            static_cast<btm::QTableWidgetItemWithPlayer*>(item);
    a->itemChanged();
}

