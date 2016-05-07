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

    void StartNewTournament();

    btm::Tournament::pointer tournament;
    btm::QPlayersTable * players_table;


private slots:
    void on_pushButton_rnd_players_clicked();
    void on_tablePlayers_cellChanged(int row, int column);
    void UpdateDisplayPlayersStatus();
    void on_tablePlayers_itemClicked(QTableWidgetItem *item);
    void on_buttonSave_clicked();
    void on_buttonLoad_clicked();

    void on_buttonAddPlayer_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
