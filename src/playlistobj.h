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

#ifndef PLAYLISTOBJ_H
#define PLAYLISTOBJ_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <QMainWindow>

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <fstream>
#include <QDir>
#include <QFileInfo>
#include <QString>
#include <QDebug>
#include "songObj.h"
using namespace std;

class playlistobj
{
   // Q_OBJECT
public:
    songObj* playlist_obj;

    string fullLocation;
    string fileLocation;
    string fileName;
    string * pl_folder;
    int folder_count;
    int playlistCount;
    int pl_obj_count;

    bool playlistOpen;

    playlistobj();

    virtual ~playlistobj();

    bool plExists(string p_locate);

    bool locationExists(string p_locate);

    bool fileExists(string file);

   void readPLfile(string location);
   void writePLfile();
   void initPL();


    void AddTo(int pos, char* FinSong);
    void RemoveFrom(int pos);

    void setTrackName(int pos, string name){
        char chName[100];
        strcpy(chName, name.c_str());
        playlist_obj[pos].setFile(chName);
    }
    void setTrackID(int id, int pos){
        playlist_obj[pos].setFileID(id);
    }
    void setFileName(string name){
        fileName = name;
    }
    void setFileLocation( string name){
        fileLocation = name;
    }
    void setCount(int count){
        pl_obj_count = count;
    }
    void setFullLocation(string name, string location){
        stringstream strLocate;
        strLocate << location << "/" << name;
        fullLocation = strLocate.str();
    }

    string getFullLocation(){
        return fullLocation;
    }

    int getCount(){
        return pl_obj_count;
    }

    string getTrackName(int pos){
        return playlist_obj[pos].getFile();
    }
    int getTrackID(int pos){
         return playlist_obj[pos].getFileID();
    }
    string getFileName(){
        return fileName;
    }
    string getFileLocation(){
        return fileLocation;
    }
    string getPLFolder(int pos){
        return pl_folder[pos];
    }

QStringList RefillPlaylist();
FILE* open(const char filename[]);
int close();
void Move(int mode, int selected);
QStringList listDirectories(const char * location);
playlistobj(const playlistobj& src);
playlistobj& operator=(const playlistobj& src);

};

#endif // PLAYLISTOBJ_H
