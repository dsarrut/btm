#include "btmQPlayerWidget.h"
#include "ui_btmQPlayerWidget.h"

// ----------------------------------------------------------------------------
QPlayerWidget::QPlayerWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::QPlayerWidget)
{
    ui->setupUi(this);
    player = btm::Player::New();
    player->name = "noname";
    selectMode = false;
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
QPlayerWidget::~QPlayerWidget()
{
    delete ui;
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
void QPlayerWidget::SetPlayer(btm::Player::pointer p)
{
    player = p;
    Update();
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
void QPlayerWidget::EnableSelectMode(bool b)
{
    selectMode = b;
    Update();
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
void QPlayerWidget::ResetSelection()
{
    ui->radioButton->setChecked(false);
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
void QPlayerWidget::Update()
{
    ui->label->setText(QString::fromStdString(player->GetName()));
    if (selectMode) {
        ui->radioButton->setVisible(true);
        ui->radioButton->setText(" ");
    }
    else {
        ui->radioButton->setChecked(false);
        ui->radioButton->setVisible(false);
    }
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
void QPlayerWidget::on_radioButton_toggled(bool checked)
{
    if (checked) {
        ui->label->setStyleSheet("QLabel { font-weight: bold;  color : blue; }");
    }
    else {
        ui->label->setStyleSheet("QLabel { font-weight: normal; color : black; }");
    }
    emit selectedToggled(player, checked);
}
// ----------------------------------------------------------------------------
