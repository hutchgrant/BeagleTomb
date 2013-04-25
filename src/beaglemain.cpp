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

#include "beaglemain.h"
#include "ui_beaglemain.h"

beaglemain::beaglemain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::beaglemain)
{
    ui->setupUi(this);
    addWidgets();
    conSignals();
}

void beaglemain::addWidgets(){
   brow = new browse(this);
   cntrl = new controls(this);
   plList = new playlist(this);
    ui->widgetLayout->addWidget(brow,0,0,0,0,0);
    ui->cntrlWidget->addWidget(cntrl,0,0,0,0,0);
    ui->playwidget->addWidget(plList,0,0,0,0,0);

}

void beaglemain::conSignals(){
    connect(brow, SIGNAL(MenuSelection(int)), brow, SLOT(updateTitle(int)));
    connect(ui->ModeCombo, SIGNAL(currentIndexChanged(int)), brow, SLOT(updateMode(int)));
    connect(brow, SIGNAL(curListChanged(fileObj&,int*)), cntrl, SLOT(setCurList(fileObj&,int*)));
    connect(brow, SIGNAL(plItemChanged(string,string,int,int)), plList, SLOT(AddToTempPL(string, string, int, int)));
    connect(brow,SIGNAL(FullSelection(int)), cntrl, SLOT(setSelectionAndPlay(int)));
    connect(brow,SIGNAL(selectionChanged(int)), cntrl, SLOT(setSelection(int)));
    // preferences
    connect(brow, SIGNAL(prefChanged(prefObj&, int)), cntrl, SLOT(setCurPref(prefObj&, int)));
    // playlist
    connect(plList, SIGNAL(playlistChanged(fileObj&,int*)), cntrl, SLOT(setCurList(fileObj&,int*)));
    connect(plList, SIGNAL(playlistSelection(int)), cntrl, SLOT(setSelection(int)));
    connect(plList, SIGNAL(playlistFullSelection(int)), cntrl, SLOT(setSelectionAndPlay(int)));
}

beaglemain::~beaglemain()
{

    cntrl->close();
    delete ui;
}


void beaglemain::on_actionImport_Video_triggered()
{

    ui->ModeCombo->setCurrentIndex(1);
    brow->Sync(3);
}

void beaglemain::on_actionImport_triggered()
{
    ui->ModeCombo->setCurrentIndex(0);
    brow->Sync(2);
}

void beaglemain::on_actionQuit_triggered()
{

    cntrl->close();
    close();
}

void beaglemain::on_actionPreferences_triggered()
{
    brow->dbCon.control(0);
    brow->getPref();
}

void beaglemain::on_actionDonate_triggered()
{
      QDesktopServices::openUrl(QUrl("https://flattr.com/profile/hutchgrant", QUrl::TolerantMode));
}

void beaglemain::on_actionAbout_triggered()
{
    ab.show();
    if(ab.exec()==QDialog::Accepted) {
        ab.close();
    }
}
void beaglemain::closeEvent(QCloseEvent *){
    cntrl->close();
}

void beaglemain::on_actionEnable_remote_triggered()
{
    brow->ToggleMode();
    /// Toggle Combo Box List
    QStringList curComboMenu;
    m_ComboModel = new QStringListModel(this);
    if(brow->remoteMode == 1){
        curComboMenu << "Remote Artists";
        curComboMenu << "Remote Albums";
        curComboMenu << "Remote VidDirs";
    }
    else{
        curComboMenu << "Artists";
        curComboMenu << "Videos";
    }

    m_ComboModel->setStringList(curComboMenu);
    ui->ModeCombo->setModel(m_ComboModel);
}

void beaglemain::on_actionSync_remote_triggered()
{
    brow->Sync(5);


}
