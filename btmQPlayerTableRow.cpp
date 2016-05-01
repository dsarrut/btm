#include "btmQPlayerTableRow.h"

#include "btmQTableWidgetItemWithPlayer.h"

btm::QPlayerTableRow::QPlayerTableRow(btm::Player::pointer p,
                       QTableWidget * t,
                       int row)
{
    player = p;
    table = t;
    items.resize(5);
    InsertItem(row, 0, true);
    InsertItem(row, 1, false);
    InsertItem(row, 2, false);
    InsertItem(row, 3, false);
    InsertItem(row, 4, false);
}

void btm::QPlayerTableRow::InsertItem(int row, int col, bool editable)
{
    QTableWidgetItemWithPlayer * item = new QTableWidgetItemWithPlayer(player);
    if (!editable)
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    table->setItem(row, col, item);
    items[col] = item;
}

void btm::QPlayerTableRow::Update()
{
    items[0]->setText(QString::fromStdString(player->name));
    items[1]->setText(QString("%1").arg(player->nb_of_matches));
    items[2]->setText(QString("%1").arg(player->nb_of_win_matches));
    items[3]->setText(QString("%1").arg(player->nb_of_lost_matches));
    items[4]->setText(QString("%1").arg(player->nb_of_wait_rounds));
}


btm::QPlayerTableRow::pointer btm::QPlayerTableRow::New(btm::Player::pointer p,
                                              QTableWidget *t,
                                              int r)
{
    return std::make_shared<QPlayerTableRow>(p, t, r);
}
