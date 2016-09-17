#include "btmQRoundWidget2.h"
#include "btmQMatchWidget2.h"
#include "ui_btmQRoundWidget2.h"
#include <QGridLayout>

//----------------------------------------------------------------------------
QRoundWidget2::QRoundWidget2(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::QRoundWidget2)
{
    ui->setupUi(this);
    round = NULL;
    gridLayout = new QGridLayout();
    ui->scrollAreaWidgetContents->setLayout(gridLayout);
    nbOfColumns = 2;
    swapPlayerMode = false;
    waitingWidget = NULL;
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
QRoundWidget2::~QRoundWidget2()
{
    delete ui;
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void QRoundWidget2::SetRound(btm::Round::pointer r)
{
    round = r;
    auto nb = round->matches.size();
    // remove old widget
    for(auto w:matchWidgets) {
        delete w;
    }
    if (waitingWidget) {
        gridLayout->removeWidget(waitingWidget);
    }
    matchWidgets.clear();

    // Add the widget if some are needed
    int row=0;
    int col=0;
    if (!waitingWidget) {
        waitingWidget = new QWaitingPlayersWidget(this);
        waitingWidget->ConnectPlayerSelection(this);
    }
    gridLayout->addWidget(waitingWidget, row, col);
    ++col;
    if (col == nbOfColumns) { col = 0; ++row; }
    for(unsigned int i=0; i<nb; i++) {
        QMatchWidget2 * w = new QMatchWidget2(this);
        w->ConnectPlayerSelection(this);
        gridLayout->addWidget(w, row, col);
        matchWidgets.push_back(w);
        ++col;
        if (col == nbOfColumns) { col = 0; ++row; }
    }

    // Install widget
    for(unsigned int i=0; i<nb; i++) {
        matchWidgets[i]->SetMatch(round->matches[i]);
    }
    waitingWidget->SetPlayers(round->waiting_players);
    waitingWidget->SetRound(round);
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void QRoundWidget2::SetNumberOfColumns(int i)
{
    nbOfColumns = i;
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void QRoundWidget2::SetSwapPlayerMode(bool b)
{
    swapPlayerMode = b;
    for(auto w:matchWidgets) w->SetSwapPlayerMode(b);
    waitingWidget->SetSwapPlayerMode(b);
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
bool QRoundWidget2::GetSwapPlayerMode() const
{
    return swapPlayerMode;
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void QRoundWidget2::on_player_selected(btm::Player::pointer p, bool b)
{
    // Update list of selected players
    if (b) selectedPlayers.push_back(p);
    else {
        auto i = std::find(selectedPlayers.begin(), selectedPlayers.end(), p);
        if (i != selectedPlayers.end()) selectedPlayers.erase(i);
    }
    // check if 2
    if (selectedPlayers.size() == 2) {
        round->SwapPlayers(selectedPlayers[0], selectedPlayers[1]);
        selectedPlayers.clear();
        for(auto w:matchWidgets) w->ResetSelection();
        waitingWidget->ResetSelection();
    }
}
//----------------------------------------------------------------------------

