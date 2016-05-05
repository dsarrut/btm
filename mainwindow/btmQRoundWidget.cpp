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
   for(unsigned int i=widgetMatches.size(); i<round->matches.size(); i++) {
       DD("create widget");
       DD(i);
       AddWidget();
   }
   for(unsigned int i=0; i<round->matches.size(); i++) {
        widgetMatches[i]->SetMatch(round->matches[i]);
    }
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

