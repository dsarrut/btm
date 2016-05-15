#include "btmQRoundWidget2.h"
#include "ui_btmQRoundWidget2.h"
#include <QGridLayout>

QRoundWidget2::QRoundWidget2(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::QRoundWidget2)
{
    ui->setupUi(this);
    round = NULL;
    gridLayout = new QGridLayout();
    setLayout(gridLayout);
    nbOfColumns = 2;
}

QRoundWidget2::~QRoundWidget2()
{
    delete ui;
}

void QRoundWidget2::SetRound(btm::Round::pointer r)
{
    DD(" new round");
    round = r;
    auto nb = round->matches.size();
    DD(nb);
    DD(matchWidgets.size());
    matchWidgets.clear();
    // Add the widget if some are needed
    int row=0;
    int col=0;
    for(unsigned int i=0; i<nb; i++) {
        DD(i);
        QMatchWidget2 * w = new QMatchWidget2(this);
        gridLayout->addWidget(w, row, col);
        matchWidgets.push_back(w);
        ++col;
        if (col == nbOfColumns) { col = 0; ++row; }
    }
    DD(matchWidgets.size());

    // Install widget
    for(unsigned int i=0; i<nb; i++) {
        DD(i);
        matchWidgets[i]->SetMatch(round->matches[i]);
    }
}

void QRoundWidget2::SetNumberOfColumns(int i)
{
    nbOfColumns = i;
}

