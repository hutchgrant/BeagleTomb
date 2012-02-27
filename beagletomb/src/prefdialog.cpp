/*
 *  Written By: Grant Hutchinson
 *  License: GPLv3.
 *  h.g.utchinson@gmail.com
 *  Copyright (C) 2012 by Grant Hutchinson
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "prefdialog.h"
#include "ui_prefdialog.h"
#include <iostream>
#include "preferences.h"
using namespace std;

PrefDialog::PrefDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrefDialog)
{
    pref.readDB();
    ui->setupUi(this);
    ui->entry_user->setText(pref.getQUser());
    ui->entry_pass->setText(pref.getQPass());
    ui->entry_serv->setText(pref.getQServer());
    ui->entry_port->setText(pref.getQPort());
    ui->entry_table->setText(pref.getQTable());
    ui->entry_sql->setText(pref.getQSQL());
    ui->entry_playlist->setText(pref.getQPLDir());
}

PrefDialog::~PrefDialog()
{
    delete ui;
}

void PrefDialog::on_buttonBox_accepted()
{
    pref = setPreferences(pref);
}
void PrefDialog::setPref(preferences& my_pref){
    pref = my_pref;
}

preferences& PrefDialog::setPreferences(preferences& pref){

    QString QUser = ui->entry_user->text();
    QString Q_pass = ui->entry_pass->text();
    QString Q_server = ui->entry_serv->text();
    QString Q_table = ui->entry_table->text();
    QString Q_port = ui->entry_port->text();
    QString Q_sql = ui->entry_sql->text();
    QString Q_pl = ui->entry_playlist->text();

    string strUser = QUser.toUtf8().constData();
    string strPass = Q_pass.toUtf8().constData();
    string strServer = Q_server.toUtf8().constData();
    string strPort = Q_port.toUtf8().constData();
    string strTable = Q_table.toUtf8().constData();
    string strSQL = Q_sql.toUtf8().constData();
    string strPL = Q_pl.toUtf8().constData();

    pref.setUser(strUser);
    pref.setPass(strPass);
    pref.setServ(strServer);
    pref.setPort(strPort);
    pref.setTable(strTable);
    pref.setSQL(strSQL);
    pref.setPlaylistDir(strPL);

    return pref;
}
preferences PrefDialog::getPref(){
    return pref;
}

bool PrefDialog::exists(const char *str){
    ifstream file(str);
    return true;
}
