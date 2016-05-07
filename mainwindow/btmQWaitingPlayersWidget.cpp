#include "btmQWaitingPlayersWidget.h"
#include "ui_btmQWaitingPlayersWidget.h"

QWaitingPlayersWidget::QWaitingPlayersWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::QWaitingPlayersWidget)
{
    ui->setupUi(this);
    setVisible(false);
}

QWaitingPlayersWidget::~QWaitingPlayersWidget()
{
    delete ui;
}

void QWaitingPlayersWidget::SetPlayers(btm::Player::vector p)
{
    setVisible(true);
    players = p;
    if (players.size() == 0) {
        ui->labelPlayers->setText("aucun");
    }
    else {
        ui->labelPlayers->setVisible(true);
        QString s="";
        for(auto p:players) {
            s.append(QString("%1\n").arg(QString::fromStdString(p->name)));
        }
        ui->labelPlayers->setText(s);
    }
}
