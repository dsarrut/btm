#include "btmQRoundWidget.h"
#include "ui_btmQRoundWidget.h"
#include <QGridLayout>

QRoundWidget::QRoundWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::QRoundWidget)
{
    ui->setupUi(this);
    /*
    widgetMatches.push_back(ui->widgetMatch1);
    widgetMatches.push_back(ui->widgetMatch2);
    widgetMatches.push_back(ui->widgetMatch3);
    widgetMatches.push_back(ui->widgetMatch4);
    widgetMatches.push_back(ui->widgetMatch5);
    widgetMatches.push_back(ui->widgetMatch6);
    widgetMatches.push_back(ui->widgetMatch7);
    widgetMatches.push_back(ui->widgetMatch8);
    widgetMatches.push_back(ui->widgetMatch9);
    */
    QGridLayout *layout = new QGridLayout();
    ui->frameMatches->setLayout(layout);
}

QRoundWidget::~QRoundWidget()
{
    delete ui;
}

void QRoundWidget::SetTournament(btm::Tournament::pointer t)
{
    tournament = t;
}

void QRoundWidget::AddWidget()
{
    static int row = 0;
    static int col = 0;
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
}

void QRoundWidget::Update()
{
   //  add widget if too much matches
   for(unsigned int i=widgetMatches.size(); i<round->matches.size(); i++)
      AddWidget();
   // Update match widgets
   for(unsigned int i=0; i<round->matches.size(); i++) {
        widgetMatches[i]->SetMatch(round->matches[i]);
    }
   // Update round nb
   ui->labelRound->setText(QString("Tour n°%1").arg(round->round_nb));
   if (tournament->rounds.back()->status == btm::Round::Terminated)
       ui->buttonNewRound->setEnabled(true);
   else ui->buttonNewRound->setEnabled(false);
   // Set button status
   if (round->status == btm::Round::Terminated)
       ui->buttonRandomScores->setEnabled(false);
   else ui->buttonRandomScores->setEnabled(true);
   if (round->round_nb == 1) ui->buttonBack->setEnabled(false);
   else ui->buttonBack->setEnabled(true);
   if (round->round_nb == tournament->rounds.size())
       ui->buttonForward->setEnabled(false);
   else ui->buttonForward->setEnabled(true);
}

void QRoundWidget::on_buttonRandomScores_clicked()
{
    std::mt19937 rng(std::time(0));
    for(auto & m:round->matches)
        m->GenerateRandomScore(rng);
    round->status = btm::Round::Terminated;
    Update();
}

void QRoundWidget::on_buttonNewRound_clicked()
{
   if (!tournament) return;
   if (!round or round->GetStatus() == btm::Round::Terminated) {
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