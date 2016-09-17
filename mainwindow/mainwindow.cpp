#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QMenuBar>
#include <QBoxLayout>
#include <QDialog>
#include <QInputDialog>

#include "btmQPlayersTable2.h"

//----------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tournament = btm::Tournament::New();

    // Table with the list of players
    tablePlayersModel = new btm::QPlayersTable2(ui->tablePlayersView);

    //ui->menuBar->addAction(ui->actionRemoteDisplay);
    QObject::connect(ui->actionRemoteDisplay, SIGNAL(triggered(bool)),
                     this, SLOT(on_menuRemoteDisplayTriggered()));
    mRemoteDisplayDialog = NULL;
    current_nb_of_points_to_win = 11;
    QString s = QString("Score à atteindre: %1")
            .arg(current_nb_of_points_to_win);
    ui->actionScore->setText(s);
    rnd_allowed = true; // FIXME to change when release
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
    if (tournament->GetPlayers().size() != 0) {
        auto reply = QMessageBox::question(this, "Question",
                                           "Cela va effacer tout le tournoi actuel. Souhaitez vous continuer ?",
                                           QMessageBox::Yes|QMessageBox::No);
        if (reply != QMessageBox::Yes) return;
    }
    btm::Player::vector players;
    btm::GenerateRandomPlayers(players, 31);
    tournament = btm::Tournament::New();
    tournament->SetPlayers(players);
    StartNewTournament();
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void MainWindow::UpdateDisplayPlayersStatus()
{
    tournament->ComputePlayersStatus();
    UpdateButtons();
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void MainWindow::on_tablePlayers_itemClicked(QTableWidgetItem *item)
{
    //auto a = static_cast<btm::QTableWidgetItemWithPlayer*>(item);
    //a->itemClicked();
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void MainWindow::on_buttonSave_clicked()
{
    auto fileName = QFileDialog::getSaveFileName(this,
                                                 tr("Sauvegarde joueurs"));
    tournament->SavePlayersToFile(fileName.toStdString());
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void MainWindow::on_buttonLoad_clicked()
{
    if (tournament->GetPlayers().size() != 0) {
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
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void MainWindow::StartNewTournament()
{
    tablePlayersModel->SetTournament(tournament);
    if (tournament->rounds.size() != 0) {
        currentRound = tournament->rounds.back();
        if (mRemoteDisplayDialog) mRemoteDisplayDialog->SetRound(currentRound);
        QObject::connect(currentRound.get(), SIGNAL(roundStatusHasChanged()),
                         this, SLOT(UpdateDisplayPlayersStatus()));
        on_currentRound_changed();
    }
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void MainWindow::InitRemoteDisplayDialog()
{
    mRemoteDisplayDialog = new QRemoteDisplayDialog(this);
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void MainWindow::on_buttonAddPlayer_clicked()
{
    DD("TODO add player");
    //auto p = btm::Player::New();
    //p->name = "pas de nom encore";
    //tournament->players.push_back(p);
    //players_table->AddPlayer(p);
    //UpdateDisplayPlayersStatus();
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void MainWindow::on_menuRemoteDisplayTriggered()
{
    if (mRemoteDisplayDialog == NULL) InitRemoteDisplayDialog();
    if (!mRemoteDisplayDialog->isVisible()) mRemoteDisplayDialog->show();
    else mRemoteDisplayDialog->hide();
    if (!tournament) return;
    if (tournament->rounds.size() == 0) return;
    mRemoteDisplayDialog->SetRound(tournament->rounds.back());
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void MainWindow::on_buttonNewRound_clicked()
{
    if (!tournament) return;
    if (tournament->GetPlayers().size() < 4) return;
    int n=0;
    for(auto p:tournament->GetPlayers())
        if (p->GetParticipateFlag()) ++n;
    if (n<4) return;

    if (tournament->rounds.size() == 0)
        currentRound = tournament->StartNewRound(current_nb_of_points_to_win);
    else {
        auto r = tournament->rounds.back();
        if (r->GetStatus() == btm::Terminated) {
            currentRound = tournament->StartNewRound(current_nb_of_points_to_win);
        }
        else return;
    }
    if (mRemoteDisplayDialog) mRemoteDisplayDialog->SetRound(currentRound);
    QObject::connect(currentRound.get(), SIGNAL(roundStatusHasChanged()),
                     this, SLOT(UpdateDisplayPlayersStatus()));
    on_currentRound_changed();
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void MainWindow::on_buttonRndScore_clicked()
{
    std::mt19937 rng(std::time(0));
    if (!tournament) return;
    if (tournament->rounds.size() == 0) return;
    btm::Round::pointer round = tournament->rounds.back();
    for(auto & m:round->matches)
        m->GenerateRandomScore(rng);
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void MainWindow::on_buttonRoundBack_clicked()
{
    if (!currentRound) return;
    auto i = currentRound->round_nb;
    if (i==1) return;
    currentRound = tournament->rounds[i-2];
    on_currentRound_changed();
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void MainWindow::on_buttonRoundForward_clicked()
{
    if (!currentRound) return;
    auto i = currentRound->round_nb;
    if (i==tournament->rounds.size()) return;
    currentRound = tournament->rounds[i];
    on_currentRound_changed();
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void MainWindow::on_currentRound_changed()
{
    ui->roundWidget2->SetRound(currentRound);
    ui->roundWidget2->SetSwapPlayerMode(false);
    ui->labelRound->setText(QString("Tour n°%1").arg(currentRound->round_nb));
    UpdateButtons();
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void MainWindow::UpdateButtons()
{
    if (!currentRound) {
        ui->buttonModifyPlayers->setEnabled(false);
        ui->buttonRoundBack->setEnabled(false);
        ui->buttonRoundForward->setEnabled(false);
        ui->buttonRndScore->setEnabled(false);
        return;
    }
    ui->buttonModifyPlayers->setEnabled(true);

    // Back forward
    if (currentRound->round_nb == 1)
        ui->buttonRoundBack->setEnabled(false);
    else ui->buttonRoundBack->setEnabled(true);
    if (currentRound->round_nb == tournament->rounds.size())
        ui->buttonRoundForward->setEnabled(false);
    else ui->buttonRoundForward->setEnabled(true);

    // Rnd button
    if (rnd_allowed) {
        if (currentRound->GetStatus() == btm::Terminated)
            ui->buttonRndScore->setEnabled(false);
        else ui->buttonRndScore->setEnabled(true);
    }

    // Swap player
    if (ui->roundWidget2->GetSwapPlayerMode()) {
        ui->buttonRoundBack->setEnabled(false);
        ui->buttonRoundForward->setEnabled(false);
        ui->buttonRndScore->setEnabled(false);
    }

    // Swap mode
    if (ui->roundWidget2->GetSwapPlayerMode())
        ui->buttonModifyPlayers->setText("Reprendre");
    else ui->buttonModifyPlayers->setText("Modifier les matchs");

    // New round
    if (currentRound == tournament->rounds.back() and
            currentRound->GetStatus() == btm::Terminated) {
        ui->buttonNewRound->setEnabled(true);
    }
    else ui->buttonNewRound->setEnabled(false);

    if (tournament->rounds.size() > 0)
        ui->buttonCancelRound->setEnabled(true);
    else ui->buttonCancelRound->setEnabled(false);
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void MainWindow::on_buttonModifyPlayers_clicked()
{
    auto b = ui->roundWidget2->GetSwapPlayerMode();
    ui->roundWidget2->SetSwapPlayerMode(!b);
    UpdateButtons();
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void MainWindow::on_buttonSaveTournament_clicked()
{
    auto fileName = QFileDialog::getSaveFileName(this,
                                                 tr("Sauvegarder le tournoi actuel"));
    if(!fileName.isEmpty()&& !fileName.isNull()){
        tournament->SaveToFile(fileName.toStdString());
    }
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void MainWindow::on_buttonLoadTournament_clicked()
{
    if (tournament->GetPlayers().size() != 0) {
        auto reply = QMessageBox::question(this, "Question",
                                           "Cela va effacer tout le tournoi actuel. Souhaitez vous continuer ?",
                                           QMessageBox::Yes|QMessageBox::No);
        if (reply != QMessageBox::Yes) return;
    }

    auto fileName = QFileDialog::getOpenFileName(this,
                                                 tr("Charger un tournoi"));
    if(!fileName.isEmpty()&& !fileName.isNull()){
        tournament = btm::Tournament::New();
        tournament->LoadFromFile(fileName.toStdString());
        StartNewTournament();
    }
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void MainWindow::on_actionScore_triggered()
{
    if (tournament) {
        bool ok;
        int score_max = QInputDialog::getInt(this, tr("Indiquez le score nécessaire pour gagner le set"),
                                             tr("Score:"),
                                             current_nb_of_points_to_win,
                                             3, 101, 1, &ok);
        if (ok) {
            current_nb_of_points_to_win = score_max;
            QString s = QString("Score à atteindre: %1")
                    .arg(current_nb_of_points_to_win);
            ui->actionScore->setText(s);
        }
    }
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void MainWindow::on_buttonCancelRound_clicked()
{
    if (tournament->rounds.size() == 0) return;

    // message r u sure ?
    auto reply = QMessageBox::question(this, "Question",
                                       "Cela va effacer tout le tour actuel. Souhaitez vous continuer ?",
                                       QMessageBox::Yes|QMessageBox::No);
    if (reply != QMessageBox::Yes) return;

    // Remove
    auto & r = tournament->rounds;
    int n = currentRound->round_nb-1;
    r.erase(r.begin()+n);

    // Re number rounds
    for(unsigned int i=0; i<r.size(); i++)
        r[i]->round_nb = i+1;

    // Change
    if (n > 1) currentRound = r[n-1];
    else currentRound = r[0];

    on_currentRound_changed();
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void MainWindow::on_actionRandom_triggered()
{
    rnd_allowed = !rnd_allowed;
    if (rnd_allowed) {
        ui->buttonRndScore->setEnabled(true);
        ui->pushButton_rnd_players->setEnabled(true);
        UpdateButtons();
    }
    else {
        ui->buttonRndScore->setEnabled(false);
        ui->pushButton_rnd_players->setEnabled(false);
        UpdateButtons();
    }
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void MainWindow::on_actionAbout_triggered()
{
    QString t = "http://github.com/dsarrut/btm";
    t = QString("<a href=\"%1\">%1</a>").arg(t);
    QMessageBox::about(this, "Badminton Tournament Management", t);
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    if (tablePlayersModel) {
        tablePlayersModel->SetFilter(arg1);
    }
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if (tournament) {
        auto players = tournament->GetPlayers();
        if (arg1 == 0) {
            for(auto p:players) p->SetParticipateFlag(false);
        }
        if (arg1 == 2) {
            for(auto p:players) p->SetParticipateFlag(true);
        }
    }
}
//----------------------------------------------------------------------------
