#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

#include "btmQTableWidgetItemWithPlayer.h"

//----------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    players_table = new btm::QPlayersTable(ui->tablePlayers);
    tournament = btm::Tournament::New();
    QObject::connect(ui->widgetRound, SIGNAL(newRound()),
                     this, SLOT(UpdateDisplayPlayersStatus()));
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void MainWindow::on_pushButton_rnd_players_clicked()
{
    if (tournament->players.size() != 0) {
        auto reply = QMessageBox::question(this, "Question",
                                           "Cela va effacer tout le tournoi actuel. Souhaitez vous continuer ?",
                                           QMessageBox::Yes|QMessageBox::No);
        if (reply != QMessageBox::Yes) return;
    }
    btm::Player::vector players;
    btm::GenerateRandomPlayers(players, 31);
    tournament = btm::Tournament::New();
    tournament->players = players;
    StartNewTournament();
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void MainWindow::UpdateDisplayPlayersStatus()
{
    tournament->ComputePlayersStatus();
    auto x = tournament->GetPlayersStatus();
    QString s = QString::fromStdString(x);
    players_table->Update();
}
//----------------------------------------------------------------------------


void MainWindow::on_tablePlayers_cellChanged(int row, int column)
{
    players_table->cellChanged(row, column);
    ui->widgetRound->Update();
}


void MainWindow::on_tablePlayers_itemClicked(QTableWidgetItem *item)
{
    auto a = static_cast<btm::QTableWidgetItemWithPlayer*>(item);
    a->itemClicked();
    ui->widgetRound->Update();
}

void MainWindow::on_buttonSave_clicked()
{
    auto fileName = QFileDialog::getSaveFileName(this,
                                                 tr("Sauvegarde joueurs"));
    tournament->SavePlayersToFile(fileName.toStdString());
}

void MainWindow::on_buttonLoad_clicked()
{
    if (tournament->players.size() != 0) {
        auto reply = QMessageBox::question(this, "Question",
                                           "Cela va effacer tout le tournoi actuel. Souhaitez vous continuer ?",
                                           QMessageBox::Yes|QMessageBox::No);
        if (reply != QMessageBox::Yes) return;
    }
    auto fileName = QFileDialog::getOpenFileName(this,
                                                 tr("Charger des joueurs"));
    if(!fileName.isEmpty()&& !fileName.isNull()){
        tournament = btm::Tournament::New();
        tournament->LoadPlayersFromFile(fileName.toStdString());
        StartNewTournament();
    }
}

void MainWindow::StartNewTournament()
{
    players_table->SetPlayers(tournament->players);
    ui->widgetRound->SetTournament(tournament);
    UpdateDisplayPlayersStatus();
}
