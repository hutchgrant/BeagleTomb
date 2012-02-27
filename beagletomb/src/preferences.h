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


#ifndef PREFERENCES_H
#define PREFERENCES_H
#include "Database.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <QMainWindow>
#include <QDir>
#define TEMPPREF "/.BeagleTomb/cache/tempPref.txt"
#define TEMPCACHE "/.BeagleTomb/cache/dbcache.txt"
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;
class preferences
{
public:
    preferences();
    preferences(const preferences& src);
    preferences(string DFLTQRY);
    void writeDB( );
    void readDB();
    void writeMe(string qry);
    void deleteDB(const char *dbLocation);
    void createDB(const char *dbLocation, const char *createSQLocation);
    void sendToShell();
    void createCache();
    /// get initial db file from text cache
    bool initDB();
    /// set initial db file in text cache
    void setInitDB();

    string USER, PASS, SERVER, PORT, TABLE, DBlocation, PLAYLISTDIR;
    void setUser(string strUser){
        USER = strUser;
    }
    void setPass(string strPass){
        PASS = strPass;
    }

    void setServ(string strServer){
        SERVER = strServer;
    }

    void setPort(string strPort){
        PORT = strPort;
    }

    void setTable(string strTable){
        TABLE = strTable;
    }

    void setSQL(string strSQL){
        DBlocation = strSQL;
    }

    void setPlaylistDir(string playlist){
        PLAYLISTDIR = playlist;
    }

    QString getQUser(){
        QString q_User = USER.c_str();
        return q_User;
    }
    QString getQPass(){
        QString q_Pass = PASS.c_str();
        return q_Pass;
    }
    QString getQServer(){
        QString q_Serv = SERVER.c_str();
        return q_Serv;
    }
    QString getQPort(){
        QString q_Port = PORT.c_str();
        return q_Port;
    }

    QString getQTable(){
        QString q_Table = TABLE.c_str();
        return q_Table;
    }
    QString getQSQL(){
        QString q_SQL = DBlocation.c_str();
        return q_SQL;
    }
    QString getQPLDir(){
        QString q_PL = PLAYLISTDIR.c_str();
        return q_PL;
    }

    string getUser(){
        return USER;
    }
    string getPass(){
        return PASS;
    }
    string getServ(){
        return SERVER;
    }
    string getPort(){
        return PORT;
    }

    string getTable(){
        return TABLE;
    }
    string getSQL(){
        return DBlocation;
    }
    string getPlaylistDir(){
        return PLAYLISTDIR;
    }

    preferences& operator=(const preferences& src);

signals:

public slots:

};


#endif // PREFERENCES_H
