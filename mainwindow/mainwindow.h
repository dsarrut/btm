#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include "btmTournament.h"
#include <btmQPlayersTable.h>
#include <btmQTableWidgetItemWithPlayer.h>
#include "btmQRoundWidget2.h"
#include "btmQRemoteDisplayDialog.h"

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
    QRemoteDisplayDialog * mRemoteDisplayDialog;
    btm::Round::pointer currentRound;

    void InitRemoteDisplayDialog();
    void UpdateButtons();

private slots:
    void on_pushButton_rnd_players_clicked();
    void on_tablePlayers_cellChanged(int row, int column);
    void UpdateDisplayPlayersStatus();
    void on_tablePlayers_itemClicked(QTableWidgetItem *item);
    void on_buttonSave_clicked();
    void on_buttonLoad_clicked();
    void on_buttonAddPlayer_clicked();
    void on_menuRemoteDisplayTriggered();
    void on_buttonNewRound_clicked();
    void on_buttonRndScore_clicked();
    void on_buttonRoundBack_clicked();
    void on_buttonRoundForward_clicked();
    void on_currentRound_changed();
    void on_buttonModifyPlayers_clicked();
    void on_buttonSaveTournament_clicked();
    void on_buttonLoadTournament_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
