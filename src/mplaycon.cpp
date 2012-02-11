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

void mplayCon::run(){

    system(strBuffer);
}
void mplayCon::set(int id){
    strBuffer= new char[100];
    sprintf(strBuffer, "mplayer -slave -quiet http://192.168.1.116:49154/content/media/object_id/%d/res_id/0", id);

}

void mplayCon::Pause(){
    strBuffer= new char[100];
    strcpy(strBuffer, "mplayer pause");
    system(strBuffer);
}

void mplayCon::Exec(char *str){
    system(str);

}
mplayCon::~mplayCon(){
    delete [] strBuffer;
}
