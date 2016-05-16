#include "btmQRoundWidget2.h"
#include "btmQMatchWidget2.h"
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
    switchPlayerMode = false;
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
    // remove old widget
    for(auto w:matchWidgets)
        gridLayout->removeWidget(w);
    matchWidgets.clear();

    // Add the widget if some are needed
    int row=0;
    int col=0;
    for(unsigned int i=0; i<nb; i++) {
        DD(i);
        QMatchWidget2 * w = new QMatchWidget2(this);
        w->ConnectPlayerSelection(this);
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

void QRoundWidget2::SetSwitchPlayerMode(bool b)
{
    switchPlayerMode = b;
    for(auto w:matchWidgets) w->SetSwitchPlayerMode(b);
}

bool QRoundWidget2::GetSwitchPlayerMode() const
{
    return switchPlayerMode;
}

void QRoundWidget2::on_player_selected(btm::Player::pointer p, bool b)
{
    DD("recu");
    DD(selectedPlayers.size());
    DD(b);
    // Update list of selected players
    if (b) selectedPlayers.push_back(p);
    else {
          auto i = std::find(selectedPlayers.begin(), selectedPlayers.end(), p);
          if (i != selectedPlayers.end()) selectedPlayers.erase(i);
    }
    // check if 2
    if (selectedPlayers.size() == 2) {
        DD("switch");
        round->SwitchPlayers(selectedPlayers[0], selectedPlayers[1]);
        selectedPlayers.clear();
        for(auto w:matchWidgets) w->ResetSelection();
    }
}

