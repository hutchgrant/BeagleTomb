#include "newplaylist.h"
#include "ui_newplaylist.h"

newplaylist::newplaylist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newplaylist)
{

    plName = "-";
    ui->setupUi(this);
}

newplaylist::~newplaylist()
{
    delete ui;
}

void newplaylist::on_playlist_accept_accepted()
{
    plName = ui->playlist_entry->text().toStdString();
}
