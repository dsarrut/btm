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
    waitingPlayersWidget = new QWaitingPlayersWidget();
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
    QMatchWidget * w = new QMatchWidget();
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
    QObject::connect(w, SIGNAL(playerSwitched(QMatchWidget*,int)),
                     this, SLOT(playerSwitched(QMatchWidget*, int)));
}

void QRoundWidget::Update()
{
    if (round == NULL) {
        for(auto w:widgetMatches) w->setVisible(false);
        ui->labelRound->setText("Tour n°0");
        btm::Player::vector a; // empty
        waitingPlayersWidget->SetPlayers(a);
        return;
    }

    //waitingPlayersWidget
    waitingPlayersWidget->SetPlayers(round->waiting_players);

    //  add widget if too much matches
    for(unsigned int i=widgetMatches.size(); i<round->matches.size(); i++)
        AddWidget();

    // hide widget if too much
    for(unsigned int i=0; i<round->matches.size(); i++)
        widgetMatches[i]->setVisible(true);
    for(unsigned int i=round->matches.size(); i<widgetMatches.size(); i++)
        widgetMatches[i]->setVisible(false);

    // Update match widgets
    for(unsigned int i=0; i<round->matches.size(); i++) {
        widgetMatches[i]->SetMatch(round->matches[i]);
    }
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
    }
}

void QRoundWidget::playerSwitched(QMatchWidget *w, int player)
{
    static QMatchWidget * previous = NULL;
    static int previous_player;

    if (previous != NULL) {
        auto m1 = w->GetMatch();
        auto m2 = previous->GetMatch();
        auto temp = m1->GetPlayer(player);
        m1->SetPlayer(player, m2->GetPlayer(previous_player));
        m2->SetPlayer(previous_player, temp);
        w->UncheckSwitch();
        previous->UncheckSwitch();
        previous = NULL;
        Update();
    }
    else {
        previous = w;
        previous_player = player;
    }
}

void QRoundWidget::on_buttonRandomScores_clicked()
{
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
        emit newRound();
        Update();
    }
}

void QRoundWidget::on_buttonBack_clicked()
{
    auto i = round->round_nb;
    if (i==1) return;
    round = tournament->rounds[i-2];
    Update();
}

void QRoundWidget::on_buttonForward_clicked()
{
    auto i = round->round_nb;
    if (i==tournament->rounds.size()) return;
    round = tournament->rounds[i];
    Update();
}

void QRoundWidget::on_pushButton_clicked()
{
    switchPlayerMode = !switchPlayerMode;
    for(auto & w:widgetMatches)
        w->enableModeSwitchPlayer(switchPlayerMode);
    Update();
}
