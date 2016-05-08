#include "btmQPlayerWidget.h"
#include "ui_btmQPlayerWidget.h"

QPlayerWidget::QPlayerWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::QPlayerWidget)
{
    ui->setupUi(this);
    player = btm::Player::New();
    player->name = "noname";
    selectMode = false;
}

QPlayerWidget::~QPlayerWidget()
{
    delete ui;
}

void QPlayerWidget::SetPlayer(btm::Player::pointer p)
{
    player = p;
    Update();
}

void QPlayerWidget::EnableSelectMode(bool b)
{
    selectMode = b;
    Update();
}

void QPlayerWidget::ResetSelection()
{
    ui->radioButton->setChecked(false);
}

void QPlayerWidget::Update()
{
    ui->label->setText(QString::fromStdString(player->name));
    if (selectMode) {
        ui->radioButton->setVisible(true);
        ui->radioButton->setText(" ");
    }
    else {
        ui->radioButton->setVisible(false);
    }
}

void QPlayerWidget::ChangePlayer(btm::Player::pointer p1,
                                 btm::Player::pointer p2)
{
    if (player == p1) { SetPlayer(p2); return; }
    if (player == p2) SetPlayer(p1);
}

void QPlayerWidget::on_radioButton_toggled(bool checked)
{
    emit selectedToggled(this, checked);
}
