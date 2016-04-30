#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <btmRound.h>
#include <btmPlayer.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_rnd_players_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
