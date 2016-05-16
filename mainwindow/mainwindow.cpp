#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QMenuBar>
#include <QBoxLayout>
#include <QDialog>

#include "btmQTableWidgetItemWithPlayer.h"

//----------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    players_table = new btm::QPlayersTable(ui->tablePlayers);
    tournament = btm::Tournament::New();
    /*QObject::connect(ui->widgetRound,
                     SIGNAL(newCurrentRound(btm::Round::pointer)),
                     this,
                     SLOT(UpdateDisplayPlayersStatus()));*/
    ui->menuBar->addAction(ui->actionRemoteDisplay);
    QObject::connect(ui->actionRemoteDisplay, SIGNAL(triggered(bool)),
                     this, SLOT(on_menuRemoteDisplayTriggered()));
    mRemoteDisplayDialog = NULL;
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
    //ui->widgetRound->Update();
}


void MainWindow::on_tablePlayers_itemClicked(QTableWidgetItem *item)
{
    auto a = static_cast<btm::QTableWidgetItemWithPlayer*>(item);
    a->itemClicked();
   // ui->widgetRound->Update();
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
    //ui->widgetRound->SetTournament(tournament);
    UpdateDisplayPlayersStatus();
//    QObject::connect(
}

void MainWindow::InitRemoteDisplayDialog()
{
    DD("creation");
    mRemoteDisplayDialog = new QRemoteDisplayDialog(this);
    DD(mRemoteDisplayDialog->isModal());

    /*
    QObject::connect(ui->widgetRound,
                     SIGNAL(newCurrentRound(btm::Round::pointer)),
                     mRemoteDisplayDialog->GetWidget(),
                     SLOT(on_RoundChanged(btm::Round::pointer)));
    if (tournament->rounds.size() > 0)
        mRemoteDisplayDialog->GetWidget()->on_RoundChanged(tournament->rounds.back());
        */
}

void MainWindow::on_buttonAddPlayer_clicked()
{
    auto p = btm::Player::New();
    p->name = "pas de nom encore";
    tournament->players.push_back(p);
    players_table->AddPlayer(p);
    UpdateDisplayPlayersStatus();
}

void MainWindow::on_menuRemoteDisplayTriggered()
{
    DD("here");
    if (mRemoteDisplayDialog == NULL) InitRemoteDisplayDialog();
    if (!mRemoteDisplayDialog->isVisible()) mRemoteDisplayDialog->show();
    else mRemoteDisplayDialog->hide();
    if (!tournament) return;
    if (tournament->rounds.size() == 0) return;
    mRemoteDisplayDialog->SetRound(tournament->rounds.back());
}

void MainWindow::on_newRound_clicked()
{
    DD("new tour");
    if (!tournament) return;
    if (tournament->rounds.size() == 0)
        currentRound = tournament->StartNewRound();
    else {
        auto r = tournament->rounds.back();
        if (r->GetStatus() == btm::Terminated) {
            currentRound = tournament->StartNewRound();
        }
        else return;
    }
    DD("ici");
    if (mRemoteDisplayDialog) mRemoteDisplayDialog->SetRound(currentRound);
    QObject::connect(currentRound.get(), SIGNAL(RoundStatusHasChanged()),
                     this, SLOT(UpdateDisplayPlayersStatus()));
    on_currentRound_changed();
}


void MainWindow::on_buttonRndScore_clicked()
{
    DD("rand");
    std::mt19937 rng(std::time(0));
    if (!tournament) return;
    if (tournament->rounds.size() == 0) return;
    btm::Round::pointer round = tournament->rounds.back();
    DD("here");
    for(auto & m:round->matches)
        m->GenerateRandomScore(rng);
}

void MainWindow::on_buttonRoundBack_clicked()
{
    if (!currentRound) return;
    auto i = currentRound->round_nb;
    if (i==1) return;
    currentRound = tournament->rounds[i-2];
    on_currentRound_changed();
}

void MainWindow::on_buttonRoundForward_clicked()
{
    if (!currentRound) return;
    auto i = currentRound->round_nb;
    if (i==tournament->rounds.size()) return;
    currentRound = tournament->rounds[i];
    on_currentRound_changed();
}

void MainWindow::on_currentRound_changed()
{
    ui->roundWidget2->SetRound(currentRound);
    if (currentRound->round_nb == 1)
        ui->buttonRoundBack->setEnabled(false);
    else ui->buttonRoundBack->setEnabled(true);
    if (currentRound->round_nb == tournament->rounds.size())
        ui->buttonRoundForward->setEnabled(false);
    else ui->buttonRoundForward->setEnabled(true);
}

void MainWindow::on_buttonModifyPlayers_clicked()
{
    DD("switch");
    if (ui->roundWidget2->GetSwitchPlayerMode()) {
        ui->roundWidget2->SetSwitchPlayerMode(false);
        ui->buttonModifyPlayers->setText("Modifier les matchs");
    }
    else {
        ui->roundWidget2->SetSwitchPlayerMode(true);
        ui->buttonModifyPlayers->setText("Reprendre");
    }
}
