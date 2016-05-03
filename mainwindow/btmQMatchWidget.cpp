#include "btmQMatchWidget.h"
#include "ui_btmQMatchWidget.h"

QMatchWidget::QMatchWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QMatchWidget)
{
    ui->setupUi(this);
}

QMatchWidget::~QMatchWidget()
{
    delete ui;
}

void QMatchWidget::on_pushButton_clicked()
{
    DD("toto");
}
