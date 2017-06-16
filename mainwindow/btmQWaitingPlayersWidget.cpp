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
   /* for(auto p:playerWidgets)
        QObject::connect(p, SIGNAL(selectedToggled(p->GetPlayer(), bool)),
                         parent, SLOT(playerSelectionToggled(p->GetPlayer(), bool)));
                         */
}

QWaitingPlayersWidget::~QWaitingPlayersWidget()
{
    delete ui;
}

void QWaitingPlayersWidget::SetPlayers(btm::Player::vector p)
{
    setVisible(true);
    players = p;
    for(auto p:playerWidgets) p->setVisible(false);
    for(unsigned int i=0; i<players.size(); i++) {
        playerWidgets[i]->SetPlayer(players[i]);
        playerWidgets[i]->setVisible(true);
    }
    if (players.size() == 0) {
        setVisible(false);
        return;
    }
}

void QWaitingPlayersWidget::SetRound(btm::Round::pointer r)
{
    round = r;
    QObject::connect(round.get(), SIGNAL(waitingPlayersHaveChanged()),
                     this, SLOT(onWaitingPlayersChanged()));
}

void QWaitingPlayersWidget::ConnectPlayerSelection(QObject *o)
{
    QObject::connect(playerWidgets[0],
            SIGNAL(selectedToggled(btm::Player::pointer,bool)),
            o, SLOT(on_player_selected(btm::Player::pointer,bool)));
    QObject::connect(playerWidgets[1],
            SIGNAL(selectedToggled(btm::Player::pointer,bool)),
            o, SLOT(on_player_selected(btm::Player::pointer,bool)));
    QObject::connect(playerWidgets[2],
            SIGNAL(selectedToggled(btm::Player::pointer,bool)),
            o, SLOT(on_player_selected(btm::Player::pointer,bool)));
}

void QWaitingPlayersWidget::ResetSelection()
{
    for(auto w:playerWidgets) w->ResetSelection();
}

void QWaitingPlayersWidget::SetSwapPlayerMode(bool b)
{
    for(unsigned int i=0; i<players.size(); i++)
        playerWidgets[i]->EnableSelectMode(b);
}

void QWaitingPlayersWidget::onWaitingPlayersChanged()
{
    SetPlayers(round->waiting_players);
}

