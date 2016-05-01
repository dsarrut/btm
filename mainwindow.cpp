#include "mainwindow.h"
#include "ui_mainwindow.h"

//----------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void MainWindow::on_pushButton_clicked()
{
    auto round = tournament.StartNewRound();
    ui->textStatus->setPlainText(QString::fromStdString(round->ToString()));
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void MainWindow::on_pushButton_rnd_players_clicked()
{
    btm::Player::vector players;
    btm::GenerateRandomPlayers(players, 30);
    for(auto p:players) DD(p);
    std::cout << std::endl;
    tournament.players = players;
}
//----------------------------------------------------------------------------

