#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    btm::Round r;
    r.Bidon();
}

void MainWindow::on_pushButton_rnd_players_clicked()
{
    std::vector<btm::Player> players;
    btm::GenerateRandomPlayers(players, 30);
    for(auto p:players) DD(p);
    std::cout << std::endl;
}
