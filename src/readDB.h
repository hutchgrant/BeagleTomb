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





#ifndef READDB_H_
#define READDB_H_
#define MAX 10000
#include "songObj.h"
#include "radioObj.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <QtSql>
using namespace std;
class readDB {

        songObj *Artist, *Album, *Song, *Video, *VidDir;
        radioObj play_list;
        char *DBlocation2;

public:
        QSqlDatabase db2;
        readDB(const char *dbLocation);
	songObj* SongFill(int *songSize);
	songObj* AlbumFill(int *albSize);
	songObj* ArtistFill(int *artSize);
        songObj* VidDirFill(int *vidDirSize);
        songObj* VideoFill(int *vidSize);
       radioObj RadioFill( int *radSize);
       void OpenDB();
	void display(int artSize, int albSize, int songSize);
	virtual ~readDB();
};

#endif /* READDB_H_ */
