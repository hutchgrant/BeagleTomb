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
#ifndef DBCONNECT_H
#define DBCONNECT_H

#include <QtSql>
#include "fileobj.h"
#include "prefdialog.h"
#include "prefobj.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#define TEMPCACHE "/.cache/beagleplayer/dbcache.txt"

using namespace std;
class dbconnect
{
public:
    string DBlocation;
    QSqlDatabase db;

    dbconnect();
    dbconnect(const dbconnect& src);
    dbconnect& operator=(const dbconnect& src);
    virtual ~dbconnect();

    void control();
    void createLocalDB();
    void createCache();
    void setInitDB();

    void OpenDB();
    bool initDB();

    void readPref(prefObj &pref);
    void readLocal(fileObj &Artist, fileObj &Song, fileObj &VidDir, fileObj &Video);
    void readRemote(fileObj &Artist, fileObj &Album, fileObj &Song, fileObj &VidDir, fileObj &Video);
    void readDB(fileObj &src, string qry, int mode);
    void readPL(fileObj &playlists, fileObj &playlistItems);

    void writeAllRemote(fileObj &Artist, fileObj &Album, fileObj &Song, fileObj &VidDir, fileObj &Video);
    void writePref(prefObj &pref);
    void writeDB(fileObj &src, int itemCount, int type);
    void writeMe(string qry);

    void removeDir(int selected, int mode);
    void removePL(int selected, int mode);
    void closeDB();


    void dropTable(int mode);

    void getLastIDs(int *lastID);
    void getLastIDs(int *AudFolderCount, int *VidFolderCount);
    int getMaxPos(int count);
    void getLastIDs();

    void setSQL(string strLocate){
       DBlocation = strLocate;
    }
    string getSQL(){

        return getenv("HOME") + DBlocation;
    }


};

#endif // DBCONNECT_H
