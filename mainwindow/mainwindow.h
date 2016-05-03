#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include "btmTournament.h"
#include <btmQPlayersTable.h>
#include <btmQTableWidgetItemWithPlayer.h>
#include "btmQMatchWidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void SetStatus(std::string & s);
    void AddToStatus(std::string & s);

    void UpdateDisplayCurrentRound();
    void UpdateDisplayPlayersStatus();

    btm::Tournament tournament;
    btm::QPlayersTable * players_table;


private slots:
    void on_pushButton_clicked();
    void on_pushButton_rnd_players_clicked();
    void on_pushButton_rnd_scores_clicked();
    void on_tablePlayers_cellChanged(int row, int column);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
