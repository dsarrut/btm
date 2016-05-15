#ifndef BTMQREMOTEDISPLAYDIALOG_H
#define BTMQREMOTEDISPLAYDIALOG_H

#include <QDialog>
#include "btmRound.h"

namespace Ui {
class QRemoteDisplayDialog;
}

class QRemoteDisplayDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QRemoteDisplayDialog(QWidget *parent = 0);
    ~QRemoteDisplayDialog();

    //QRemoteDisplay *GetWidget();
    void SetRound(btm::Round::pointer r);

protected:
    btm::Round::pointer round;

private:
    Ui::QRemoteDisplayDialog *ui;
};

#endif // BTMQREMOTEDISPLAYDIALOG_H
