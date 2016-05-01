#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <btmTournament.h>

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


private slots:
    void on_pushButton_clicked();
    void on_pushButton_rnd_players_clicked();
    void on_pushButton_rnd_scores_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
