#ifndef FORMTOTO_H
#define FORMTOTO_H

#include <QWidget>

namespace Ui {
class FormToto;
}

class FormToto : public QWidget
{
    Q_OBJECT

public:
    explicit FormToto(QWidget *parent = 0);
    ~FormToto();

private slots:
    void on_textBrowser_textChanged();

private:
    Ui::FormToto *ui;
};

#endif // FORMTOTO_H
