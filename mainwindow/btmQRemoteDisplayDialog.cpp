#include "btmQRemoteDisplayDialog.h"
#include "ui_btmQRemoteDisplayDialog.h"

QRemoteDisplayDialog::QRemoteDisplayDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QRemoteDisplayDialog)
{
    ui->setupUi(this);
}

QRemoteDisplayDialog::~QRemoteDisplayDialog()
{
    delete ui;
}

void QRemoteDisplayDialog::SetRound(btm::Round::pointer r)
{
    round = r;
    ui->frame_2->SetNumberOfColumns(1);
    ui->frame_2->SetRound(round);
}

