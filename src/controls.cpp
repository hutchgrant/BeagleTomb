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

#include "controls.h"
#include "ui_controls.h"

controls::controls(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::controls)
{
    ui->setupUi(this);
    remoteMode = 0;  // init play mode to local

    CON_MODE = 0;
    widget.setSeekSlider(ui->trackSlider);
    vol = new volume(this);
    ui->volLayout->addWidget(vol, 0,0,0,0,0);
    connect(vol, SIGNAL(volChanged(int)), this, SLOT(setVol(int)));

}

/*
  *  Control for Start of local File
  */
void controls::startLocal(char *finSong, char *finPath)
{
    char *final;
    final = new char[strlen(finPath) + 10];
    sprintf(final, "%s", finPath);
    cout << "Final File Playing: " << final << endl;
    widget.show();
    ui->songTitle->setText(QString(finSong));
    widget.start(QStringList(final));
}

/*
  * Control for start of remote file
  */
 void controls::startRemote(char *finSong, int selID){
    char *final;
        final = new char[strlen(finSong) + 100];
        sprintf(final, "http://%s:%s/content/media/object_id/%d/res_id/0", pref.getHostIP().c_str(), pref.getHostPort().c_str(), selID);
        cout << "Final File Playing: " << final << endl;
        widget.show();
        ui->songTitle->setText(QString(finSong));
        widget.start(QStringList(final));
}

/*
  *  Sort the current list for
  */
void controls::startSelected(){
    int finSongSize = 0;
    int finPathSize = 0;
    int selID = 0;
    char *finPath;
    char *finSong;

    selID = curList[CurrentSelect];

    finSongSize = strlen(checkSongObjByID(selID, current));
    finSong = new char[finSongSize + 1];
    finSong = checkSongObjByID(selID, current);


    cout << "final song:" << finSong << endl;
    if(remoteMode == 0){   /// if local mode
        finPathSize = strlen(checkSongObjPathByID(selID, current));
        finPath = new char[finPathSize + 1];
        finPath = checkSongObjPathByID(selID, current);
        startLocal(finSong, finPath);
    }else{                  /// if remote mode
        startRemote(finSong, selID);
    }
}
/*
  * Slot to Change connection Mode
  */
void controls::changeCon(int mode){
    CON_MODE = mode;
}

/*
  * Set Current qeue list when list changes
  */
void controls::setCurList(fileObj &newList, int *newIDlist){
    current = newList;
    curList = newIDlist;
}


/*
  * public slot for volume
  */
void controls::setVol(int vol){
    widget.setVolume(vol);

}
controls::~controls()
{
    widget.close();
    delete ui;
}


void controls::on_PAUSE_clicked()
{
    widget.pause();
}

void controls::on_PLAY_clicked()
{
    widget.play();
}

void controls::on_STOP_clicked()
{
    widget.stop();
}

void controls::on_NEXT_clicked()
{
    CurrentSelect++;
    startSelected();
}

void controls::on_PREV_clicked()
{
    CurrentSelect--;
    startSelected();
}
