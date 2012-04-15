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


#ifndef MYSQLCONN_H_
#define MYSQLCONN_H_

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <string>
#include <string.h>
#include <QtSql>
#include "fileobj.h"
#include "preferences.h"
using namespace std;

#define MAXQRY 100
class mysqlconn {

public:
        QSqlDatabase db;
        mysqlconn(preferences &pref);
        QSqlDatabase connectMySQL();

        preferences pref;

        fileObj& connectArtist(int artMenu, fileObj& Artist);
        fileObj& connectAlbum(fileObj& Artist, fileObj& Album);
        fileObj& connectSong(fileObj& Album, fileObj& Song);
        fileObj& connectVidDir(int vidMenu, fileObj& VidDir);
        fileObj& connectVideo(fileObj& VidDir, fileObj& Video);

        void OpenDB();
        void closeDB();

        int connectVidMenu();
        int connectArtMenu();
        void display(ostream& os, int pos);
         virtual ~mysqlconn();
};

#endif /* MYSQLCONN_H_ */
