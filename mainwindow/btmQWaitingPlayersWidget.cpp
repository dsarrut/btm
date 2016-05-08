#include "btmQWaitingPlayersWidget.h"
#include "ui_btmQWaitingPlayersWidget.h"

QWaitingPlayersWidget::QWaitingPlayersWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::QWaitingPlayersWidget)
{
    ui->setupUi(this);
    setVisible(false);
    playerWidgets.push_back(ui->widgetPlayer1);
    playerWidgets.push_back(ui->widgetPlayer2);
    playerWidgets.push_back(ui->widgetPlayer3);
    for(auto p:playerWidgets)
        QObject::connect(p, SIGNAL(selectedToggled(QPlayerWidget*, bool)),
                         parent, SLOT(playerSelectionToggled(QPlayerWidget*, bool)));
}

QWaitingPlayersWidget::~QWaitingPlayersWidget()
{
    delete ui;
}

void QWaitingPlayersWidget::SetPlayers(btm::Player::vector p)
{
    setVisible(true);
    players = p;
    for(unsigned int i=0; i<players.size(); i++)
        playerWidgets[i]->SetPlayer(players[i]);
    if (players.size() == 0) {
        setVisible(false);
        return;
    }
}

void QWaitingPlayersWidget::enableModeSwitchPlayer(bool b)
{
    for(unsigned int i=0; i<players.size(); i++)
        playerWidgets[i]->EnableSelectMode(b);
}

void QWaitingPlayersWidget::ChangePlayer(btm::Player::pointer p1,
                                         btm::Player::pointer p2)
{
    for(auto w:playerWidgets) w->ChangePlayer(p1,p2);
}

