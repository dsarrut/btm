#include "formtoto.h"
#include "ui_formtoto.h"

FormToto::FormToto(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormToto)
{
    ui->setupUi(this);
}

FormToto::~FormToto()
{
    delete ui;
}

void FormToto::on_textBrowser_textChanged()
{

}
