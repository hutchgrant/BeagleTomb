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

using namespace std;

PrefDialog::PrefDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrefDialog)
{
    ui->setupUi(this);
    setLabels();
}

void PrefDialog::setLabels(){
    dbconnect dbCon;
    dbCon.readPref(preferences);
    ui->entry_sqlPath->setText(QString(TEMPDB));
    ui->entry_remUser->setText(preferences.getQUser());
    ui->entry_remPass->setText(preferences.getQPass());
    ui->entry_remIP->setText(preferences.getQHOSTIP());
    ui->entry_remPort->setText(preferences.getQHOSTPORT());
    ui->entry_remTable->setText(preferences.getQTable());
}

PrefDialog::~PrefDialog()
{
    delete ui;
}
void PrefDialog::on_buttonBox_accepted()
{
    setPreferences();
}
void PrefDialog::setPreferences(){

    QString Q_sqlPath = ui->entry_sqlPath->text();
    QString Q_remoteUser = ui->entry_remUser->text();
    QString Q_remotePass = ui->entry_remPass->text();
    QString Q_remoteIP = ui->entry_remIP->text();
    QString Q_remotePort = ui->entry_remPort->text();
     QString Q_remoteTable = ui->entry_remTable->text();


   preferences.setPref( Q_remoteUser.toStdString(), Q_remotePass.toStdString(), Q_remoteIP.toStdString(), Q_remotePort.toStdString(), Q_remoteTable.toStdString(), Q_sqlPath.toStdString());

}
