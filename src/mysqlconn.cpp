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


#include "mysqlconn.h"
using namespace std;

mysqlconn::mysqlconn(const char *server, const char* user, const char *pass, const char *table) {

    // connect to the database with the details attached.
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(server);
    db.setDatabaseName(table);
    db.setUserName(user);
    db.setPassword(pass);
}

fileObj& mysqlconn::connectAlbum(fileObj& Artist, fileObj& Album){
     cout << "artists:: " << Artist.getSize() << endl;
    bool Exit = false;
    int curID = 0;          /// current ID of query
    char *myQry = NULL;     /// string for final query
    int albCount = 0;      /// counter for number of album items
    int qryCount = 0;      /// counter for number of queries

    while(!Exit){
        if(!myQry){
            myQry = new char[MAXQRY];
        }
        curID = Artist.getID(qryCount);
        if(curID == 0){
            Exit = 1;
        }
        sprintf(myQry, "SELECT * FROM mt_cds_object WHERE parent_id = %d", curID );

        if(db.open()){
            QSqlQuery query(db);
            query = QString(myQry);
            while(query.next()){
                QString QVal = query.value(0).toString();
                QString QVal1 = query.value(1).toString();
                QString QVal2 = query.value(2).toString();
                QString QVal3 = query.value(3).toString();
                QString QVal4 = query.value(4).toString();
                QString QVal5 = query.value(5).toString();

                ///////*****  Query for Album rows using artist
                if(QVal4.toStdString().compare("object.container.album.musicAlbum") == 0){
                    if (QVal2.toInt() == curID) {
                        Album.set(albCount, QVal.toInt(), QVal2.toInt(), QVal5.toStdString().c_str());
                         albCount++;
                    }
                }
            }
            qryCount++;
            if (qryCount == Artist.getSize()-1) {
                Exit = true;
            }
            db.close();
        }
        else{
            cout << "error couldn't connect to mysql" << endl;
        }
    }
    return Album;
}



fileObj& mysqlconn::connectSong(fileObj& Album, fileObj& Song){
    cout << "albums: " << Album.getSize() << endl;
    bool Exit = false;
    int curID = 0;          /// current ID of query
    char *myQry = NULL;     /// string for final query
    int songCount = 0;      /// counter for number of album items
    int qryCount = 0;      /// count for number of queries

    while(!Exit){
        if(!myQry){
            myQry = new char[MAXQRY];
        }
        curID = Album.getID(qryCount);
        if(curID == 0){
            Exit = 1;
        }
        sprintf(myQry, "SELECT * FROM mt_cds_object WHERE parent_id = %d", curID );

        if(db.open()){
            QSqlQuery query(db);
            query = QString(myQry);
            while(query.next()){
                QString QVal = query.value(0).toString();
                QString QVal1 = query.value(1).toString();
                QString QVal2 = query.value(2).toString();
                QString QVal3 = query.value(3).toString();
                QString QVal4 = query.value(4).toString();
                QString QVal5 = query.value(5).toString();

                ///////*****  Query for Songs
                if (QVal2.toInt() == curID) {
                    Song.set(songCount, QVal.toInt(), QVal2.toInt(), QVal5.toStdString().c_str());
                     songCount++;
                }

            }
            qryCount++;
            if (qryCount == Album.getSize()-1) {
                Exit = true;
            }
            db.close();
        }
        else{
            cout << "error couldn't connect to mysql" << endl;
        }
    }
     cout << "songs: " << Song.getSize() << endl;
    return Song;
}

fileObj& mysqlconn::connectArtist(int artMenu, fileObj& Artist){

    int curID = 0;          /// current ID of query
    char *myQry = NULL;     /// string for final query
    int artCount = 0;      /// counter for number of Artist items

        if(!myQry){
            myQry = new char[MAXQRY];
        }

        sprintf(myQry, "SELECT * FROM mt_cds_object WHERE parent_id = %d", artMenu );

        if(db.open()){
            QSqlQuery query(db);
            query = QString(myQry);

            while(query.next()){
                QString QVal = query.value(0).toString();
                QString QVal1 = query.value(1).toString();
                QString QVal2 = query.value(2).toString();
                QString QVal3 = query.value(3).toString();
                QString QVal4 = query.value(4).toString();
                QString QVal5 = query.value(5).toString();
                ///////*****  Query for MAIN root menu
                if (QVal2.toInt() == artMenu) {
                    Artist.set(artCount, QVal.toInt(), QVal2.toInt(), QVal5.toStdString().c_str());
                    artCount++;
                }

            }
           db.close();
        }
        else{
            cout << "error couldn't connect to mysql" << endl;
        }
    return Artist;
}

fileObj& mysqlconn::connectVideo(fileObj& VidDir, fileObj& Video){
 cout << "Video Directories: " << VidDir.getSize() << endl;
    bool Exit = false;
    int curID = 0;          /// current ID of query
    char *myQry = NULL;     /// string for final query
    int VidCount = 0;      /// counter for number of video items
    int qryCount = 0;      /// count for number of queries

    while(!Exit){

        if(!myQry){
            myQry = new char[MAXQRY];
        }
        curID = VidDir.getID(qryCount);
        if(curID == 0){
            Exit = 1;
        }
        sprintf(myQry, "SELECT * FROM mt_cds_object WHERE parent_id = %d", curID );

        if(db.open()){
            QSqlQuery query(db);
            query = QString(myQry);

            while(query.next()){
                QString QVal = query.value(0).toString();
                QString QVal1 = query.value(1).toString();
                QString QVal2 = query.value(2).toString();
                QString QVal3 = query.value(3).toString();
                QString QVal4 = query.value(4).toString();
                QString QVal5 = query.value(5).toString();

                ///////*****  Query for Videos

                if (QVal2.toInt() == curID) {
                    Video.set(VidCount,QVal.toInt(), QVal2.toInt(),  QVal5.toStdString().c_str());
                    VidCount++;
                }

            }
            qryCount++;
            if (qryCount == VidDir.getSize()-1) {
                Exit = true;
            }
            db.close();
        }
        else{
            cout << "error couldn't connect to mysql" << endl;
        }
    }
     cout << "videos: " << Video.getSize() << endl;
    return Video;
}

fileObj& mysqlconn::connectVidDir(int vidMenu, fileObj& VidDir){

    int curID = 0;          /// current ID of query
    char *myQry = NULL;     /// string for final query
    int VidDirCount = 0;      /// counter for number of video directory items
    int qryCount = 0;      /// count for number of queries

        if(!myQry){
            myQry = new char[MAXQRY];
        }

        sprintf(myQry, "SELECT * FROM mt_cds_object WHERE parent_id = %d", vidMenu );

        if(db.open()){
            QSqlQuery query(db);
            query = QString(myQry);

            while(query.next()){
                QString QVal = query.value(0).toString();
                QString QVal1 = query.value(1).toString();
                QString QVal2 = query.value(2).toString();
                QString QVal3 = query.value(3).toString();
                QString QVal4 = query.value(4).toString();
                QString QVal5 = query.value(5).toString();

                ///////*****  Query for Vid Dir
                if (QVal2.toInt() == vidMenu) {
                    VidDir.set(VidDirCount, QVal.toInt(), QVal2.toInt(), QVal5.toStdString().c_str());
                    VidDirCount++;
                }

            }

            db.close();
        }
        else{
            cout << "error couldn't connect to mysql" << endl;
        }
    return VidDir;
}



int mysqlconn::connectVidMenu(){
    int vidMenuID = 0, vidDirMenuID = 0, vidMenu = 0;


    bool Myexit = false; // exit variable
    int QryCount = 0;
    int rowCount = 0;
    char *myQry = NULL;


    while (Myexit != true) {

        if (!myQry) {
            myQry = new char[MAXQRY];
        }


        /// use root to query for the Main menu's (audio + video)
        if (QryCount == 0) {
            sprintf(myQry, "SELECT * FROM mt_cds_object WHERE parent_id = %d",
                    0);
        }

        else if(QryCount == 1){
            sprintf(myQry, "SELECT * FROM mt_cds_object WHERE parent_id = %d",
                    vidMenuID);
        }

        if(db.open()){
            QSqlQuery query(db);
            query = QString(myQry);
            rowCount = 0;
            while (query.next()){

                QString QVal = query.value(0).toString();
                QString QVal1 = query.value(1).toString();
                QString QVal2 = query.value(2).toString();
                QString QVal3 = query.value(3).toString();
                QString QVal4 = query.value(4).toString();
                QString QVal5 = query.value(5).toString();

                if (QVal2.toInt() == 0 && rowCount == 3){
                    vidMenuID = QVal.toInt();
                }

                if(QVal2.toInt() == vidMenuID && rowCount == 1){
                    vidDirMenuID = QVal.toInt();
                }
                rowCount++;

            }
            QryCount++;
            if (QryCount > 2) { // + albCount
                Myexit = true;
            }
            db.close();

        }
        else{
            cout << "error couldn't connect to vid menu in mysql" << endl;
            Myexit = true;
        }
    }
    return vidDirMenuID;
}

int mysqlconn::connectArtMenu() {


    int audMenuID = 0, artMenuID = 0, QryCount = 0, menu = 0, artMenu = 0;
    bool Myexit = false; // exit variable

    char *myQry = NULL;

    while (Myexit != true) {

        if (!myQry) {
            myQry = new char[MAXQRY];
        }

        /// use root to query for the Main menu's (audio + video)
        if (QryCount == 0) {
            sprintf(myQry, "SELECT * FROM mt_cds_object WHERE parent_id = %d",
                    0);
        }

        /// use audio menu ID to get Artist Menu ID
        else if (QryCount == 1) {
            sprintf(myQry, "SELECT * FROM mt_cds_object WHERE parent_id = %d",
                    audMenuID);
        }
        if(db.open()){
            QSqlQuery query(db);
            query = QString(myQry);
            while (query.next()){

                QString QVal = query.value(0).toString();
                QString QVal1 = query.value(1).toString();
                QString QVal2 = query.value(2).toString();
                QString QVal3 = query.value(3).toString();
                QString QVal4 = query.value(4).toString();
                QString QVal5 = query.value(5).toString();
                ///////*****  Query for MAIN root menu
                if (QVal2.toInt() == 0 && QryCount == 0) {
                    menu++;
                    if (menu == 1) {
                        audMenuID = QVal.toInt();
                    }
                }

                //check for Audio menus
                else if (QVal2.toInt() == audMenuID) {
                    artMenu++;
                    //set ID of artist sub Menu
                    if (artMenu == 4) {
                        artMenuID = QVal.toInt();
                    }
                }

            }
            QryCount++;
            if (QryCount > 3) { // + albCount
                Myexit = true;
            }
            db.close();
        }
        else{
            cout << "error couldn't connect to mysql" << endl;
            Myexit = true;
        }
    }
    return artMenuID;
}

mysqlconn::~mysqlconn() {
    QSqlDatabase::removeDatabase("connectSQL");
}
