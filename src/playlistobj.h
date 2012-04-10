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
#include <QtSql>
#include <QFileInfo>
#include <QString>
#include <QDebug>
#include "fileobj.h"
using namespace std;

class playlistobj
{
   // Q_OBJECT
public:
    fileObj playlist_obj;   /// playlist object holds all ids, pars, names, paths of items
    int pl_obj_count;       /// number of items in playlist
    string playlistName;    /// name of the current playlist
    int pl_mode;            /// boolean for browsing playlist names or items
    string db_location;     /// database location
    QSqlDatabase db;

    playlistobj();
    void initPlaylist();
    fileObj control();
    void AddTo(int id, int par, string name, string path, fileObj &src);
    void AddNew(string name);
    void Move(int selected, int direction);

    void openDB();
    void readPlDB(fileObj &src, int type);
    void writeToDB();
    void removeFromDB(int item);
    void RemoveFrom(int selected);
    void writeMe(string sQry);
    void writeNew();

    QStringList fillPlaylist(fileObj &src);
    virtual ~playlistobj();
    playlistobj& operator=(const playlistobj& src);
    playlistobj(const playlistobj& src);


    void setMode(int type){
        pl_mode = type;
    }
    void setLocation(string locate){
        db_location = locate;
    }
    void setPlObj(fileObj &src){
        playlist_obj = src;
        pl_obj_count = src.getSize();
    }
};

#endif // PLAYLISTOBJ_H
