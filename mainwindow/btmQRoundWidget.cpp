#include "btmQRoundWidget.h"
#include "ui_btmQRoundWidget.h"
#include <QGridLayout>

QRoundWidget::QRoundWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::QRoundWidget)
{
    ui->setupUi(this);
    QGridLayout *layout = new QGridLayout();
    ui->frameMatches->setLayout(layout);
    waitingPlayersWidget = new QWaitingPlayersWidget(this);
    layout->addWidget(waitingPlayersWidget, 0, 0);
    switchPlayerMode = false;
}

QRoundWidget::~QRoundWidget()
{
    delete ui;
}

void QRoundWidget::SetTournament(btm::Tournament::pointer t)
{
    tournament = t;
    round = NULL;
    Update();
}

void QRoundWidget::AddWidget()
{
    static int row = 0;
    static int col = 1;
    QMatchWidget * w = new QMatchWidget(this);
    QGridLayout * layout =
            static_cast<QGridLayout*>(ui->frameMatches->layout());
    layout->addWidget(w, row, col);
    ++col;
    if (col ==2) {
        col = 0;
        ++row;
    }
    widgetMatches.push_back(w);
    QObject::connect(w, SIGNAL(matchScoreChanged(btm::Match::pointer)),
                     this, SLOT(Update()));
}

void QRoundWidget::Update()
{
    if (round == NULL) {
        for(auto w:widgetMatches) w->setVisible(false);
        ui->labelRound->setText("Tour n°0");
        waitingPlayersWidget->setVisible(false);
        ui->buttonSwitch->setEnabled(false);
        //ui->butt
        return;
    }
    else {
        ui->buttonSwitch->setEnabled(true);
    }

    // Update matches
    for(unsigned int i=0; i<round->matches.size(); i++)
        widgetMatches[i]->on_match_changed();

    // Update round nb
    ui->labelRound->setText(QString("Tour n°%1").arg(round->round_nb));
    if (tournament->rounds.back()->GetStatus() == btm::Terminated)
        ui->buttonNewRound->setEnabled(true);
    else ui->buttonNewRound->setEnabled(false);

    // Set button status
    if (round->GetStatus() == btm::Terminated)
        ui->buttonRandomScores->setEnabled(false);
    else ui->buttonRandomScores->setEnabled(true);
    if (round->round_nb == 1) ui->buttonBack->setEnabled(false);
    else ui->buttonBack->setEnabled(true);
    if (round->round_nb == tournament->rounds.size())
        ui->buttonForward->setEnabled(false);
    else ui->buttonForward->setEnabled(true);

    if (switchPlayerMode) {
        ui->buttonBack->setEnabled(false);
        ui->buttonForward->setEnabled(false);
        ui->buttonNewRound->setEnabled(false);
        ui->buttonRandomScores->setEnabled(false);
        ui->buttonSwitch->setText("Reprendre");
    }
    else {
        ui->buttonSwitch->setText("Modifier les matchs");
    }
}

void QRoundWidget::playerSwitched(QMatchWidget *w, int player)
{
    static QMatchWidget * w1 = NULL;
    static int player1;
    return;

    if (w1 != NULL) {
        auto w2 = w;
        auto player2 = player;
        auto m1 = w1->GetMatch();
        auto m2 = w2->GetMatch();
        // Change data
        m1->SwitchPlayer(player1, m2, player2);
        // Change ui
        w1->SetPlayer(player1, m1->GetPlayer(player1));
        w2->SetPlayer(player2, m2->GetPlayer(player2));
        w1->ResetSelection();
        w2->ResetSelection();
        w1 = NULL;
        Update();
    }
    else {
        w1 = w;
        player1 = player;
    }
}

void QRoundWidget::playerSelectionToggled(QPlayerWidget *w, bool checked)
{
    auto player = w->GetPlayer();
    if (!checked) return;
    static QPlayerWidget * previous = NULL;
    if (previous != NULL) {
        auto p2 = previous->GetPlayer();
        auto p1 = w->GetPlayer();
        SwapPlayers(p1,p2);
        w->ResetSelection();
        previous->ResetSelection();
        previous = NULL;
    }
    else {
        previous = w;
    }
}

void QRoundWidget::on_buttonRandomScores_clicked()
{
    DD("old random");
    std::mt19937 rng(std::time(0));
    for(auto & m:round->matches)
        m->GenerateRandomScore(rng);
    Update();
}

void QRoundWidget::on_buttonNewRound_clicked()
{
    if (!tournament) return;
    if (!round or round->GetStatus() == btm::Terminated) {
        round = tournament->StartNewRound();
        SetRound(round);
        emit newCurrentRound(round);
    }
}


void QRoundWidget::SetRound(btm::Round::pointer r)
{
    round = r;
    waitingPlayersWidget->SetPlayers(round->waiting_players);
    for(unsigned int i=widgetMatches.size(); i<round->matches.size(); i++)
        AddWidget();
    for(unsigned int i=0; i<round->matches.size(); i++)
        widgetMatches[i]->SetMatch(round->matches[i]);
    Update();
}

void QRoundWidget::SwapPlayers(btm::Player::pointer p1,
                               btm::Player::pointer p2)
{
    waitingPlayersWidget->ChangePlayer(p1,p2);
    for(auto w:widgetMatches) w->ChangePlayer(p1,p2);
}


void QRoundWidget::on_buttonBack_clicked()
{
    auto i = round->round_nb;
    if (i==1) return;
    SetRound(tournament->rounds[i-2]);
}

void QRoundWidget::on_buttonForward_clicked()
{
    auto i = round->round_nb;
    if (i==tournament->rounds.size()) return;
    SetRound(tournament->rounds[i]);
}

void QRoundWidget::on_buttonSwitch_clicked()
{
    switchPlayerMode = !switchPlayerMode;
    for(auto & w:widgetMatches)
        w->enableModeSwitchPlayer(switchPlayerMode);
    waitingPlayersWidget->enableModeSwitchPlayer(switchPlayerMode);
    Update();
}
