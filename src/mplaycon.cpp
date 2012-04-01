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


#include "mplaycon.h"
#include <QApplication>
mplayCon::mplayCon(QObject *parent)
    : QThread(parent)

{
}

mplayCon::mplayCon(){

}

void mplayCon::run(){


 //   while(widget2.state() != 2 || widget2.state() != -1){

        int selID = 0;


        char* FinSong;
     /*    for(int i = 0; i<= pl.getCount(); i++){
            if(pl.getTrackID(i) == selID){
                FinSong = new char[strlen(pl.getTrackName(i).c_str())];
                strcpy(FinSong,pl.getTrackName(i).c_str());
            }
        }*/

        selID = pl.getTrackID(pl_selected);

        if(widget2.state() == -1) {   // if loaded but doing nothing
            startSong(FinSong, selID);
       }
        else if(widget2.state() == 0){  // if idle state
              pl_selected++;
             startSong(FinSong, selID);
        }
        else if(widget2.state() == 1) {  // if in loading state

        }
        else if(widget2.state() == 2) {  // if in stopped state
           // widget2.stop();
        }
  // }

}
void mplayCon::set(playlistobj &plobj, preferences prefs, int plselected){

    QMPwidget Twidget;
    pl = plobj;
    pref = prefs;

    if(pl_selected >=0){
        pl_selected = plselected;
    }
}

void mplayCon::startSong(char *FinSong, int selID){

    char * strBuffer;
    strBuffer= new char[100];
    sprintf(strBuffer, "http://%s:%s/content/media/object_id/%d/res_id/0", pref.getServ().c_str(), pref.getPort().c_str(), selID);
    //cout << strBuffer << endl;
    //ui->SONG_lbl->setText((QString)FinSong);
  //  widget2.show();
    widget2.start(QStringList(strBuffer));
}

mplayCon::~mplayCon(){
}
