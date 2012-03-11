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

songObj* mysqlconn::connectAlbum(songObj* Artist, int *artSize, songObj* Album, int *albSize){
    bool Myexit = false;
    int albCount = 0;
    int QryCount = 0;
    char *myQry = NULL;
    int albQryCount = 0;
    int curID;

    *albSize = MAXSONG;
    Album = new songObj[MAXALB];

    for(int i= 0 ; i <= MAXALB; i++){
        Album[i].set("-", 0, 0);
    }

    while(Myexit != true){

	if (!myQry) {
            myQry = new char[MAXQRY];
	}
        curID = Artist[QryCount].getFileID();
        if(curID == 0){
            Myexit = 1;
        }


        sprintf(myQry, "SELECT * FROM mt_cds_object WHERE parent_id = %d",
                curID );

        // connect to the mysql database

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

            ///////*****  Query for Album rows using artist
            if(QVal4.toStdString().compare("object.container.album.musicAlbum") == 0){
                if (QVal2.toInt() == curID) {
                    albCount++;
                    string Qstr5Convert = QVal5.toStdString();
                    char *QVal5Convert;
                    QVal5Convert = new char[Qstr5Convert.length() + 1];
                    strcpy(QVal5Convert, Qstr5Convert.c_str());
                    Album[albCount].set(QVal5Convert, QVal.toInt(), QVal2.toInt());
                }
            }
        }
        *albSize = albCount;
        QryCount++;
        if (QryCount == *artSize) {
            Myexit = true;
        }
         db.close();
        }
        else{
            cout << "error couldn't connect to mysql" << endl;
        }
    }
    return Album;
}

songObj* mysqlconn::connectSong(songObj* Album, int *albSize, songObj* Song, int *songSize){

    int songCount = 0;
    int QryCount = 0;
    char *myQry = NULL;
    int curID = 0;
    bool Myexit = false;

    *songSize = MAXSONG;
    Song = new songObj[MAXSONG];

    for(int i= 0 ; i <= MAXSONG; i++){
        Song[i].set("-", 0, 0);
    }


    while (Myexit != true){


	if (!myQry) {
            myQry = new char[MAXQRY];
        }

	curID = Album[QryCount+1].getFileID();
	if(curID == 0){
            Myexit = true;
        }


        sprintf(myQry, "SELECT * FROM mt_cds_object WHERE parent_id = %d",
                curID);
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


            ///////*****  Query for Songs
            if (QVal2.toInt() == curID) {
                songCount++;
                string QstrConvert = QVal5.toStdString();
                char *QVal5Convert;
                QVal5Convert = new char[QstrConvert.length() + 1];
                strcpy(QVal5Convert, QstrConvert.c_str());
                Song[songCount].set(QVal5Convert, QVal.toInt(), QVal2.toInt());
            }
        }

        *songSize = songCount;
        QryCount++;
        if (QryCount == *albSize) {
            Myexit = true;
        }
        db.close();
        }
    }
    return Song;
}
songObj* mysqlconn::connectArtist(songObj* Artist, int artMenu, int *mySize){


    int artCount = 0;
    *mySize = MAXART;
    Artist = new songObj[MAXART];

    for(int i= 0 ; i <= MAXART; i++){
        Artist[i].set("-", 0, 0);
    }



    char *myQry = NULL;

    if (!myQry) {
        myQry = new char[MAXQRY];
    }

    /// use artist menu ID  to get artists

    sprintf(myQry, "SELECT * FROM mt_cds_object WHERE parent_id = %d",
            artMenu);

    if(!db.open()){
        cout << "error couldn't connect to mysql" << endl;
    }
    else{
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
        if (QVal2.toInt() == artMenu) {
            string Qstr5Convert = QVal5.toStdString();
            char *QVal5Convert;
            QVal5Convert = new char[Qstr5Convert.length() + 1];
            strcpy(QVal5Convert, Qstr5Convert.c_str());
            Artist[artCount].set(QVal5Convert, QVal.toInt(), QVal2.toInt());
            artCount++;
        }
    }

    *mySize = artCount;
    db.close();
    }

    return Artist;
}

songObj* mysqlconn::connectVideo(songObj* VidDir, int *vidDirSize, songObj* Video, int *vidSize){

    int VidCount = 0;


    int QryCount = 0;
    char *myQry = NULL;
    int curID = 0;
    bool Myexit = false;

    *vidSize = MAXVIDEO;
    Video = new songObj[MAXVIDEO];

    for(int i= 0 ; i <= MAXVIDEO; i++){
        Video[i].set("-", 0, 0);
    }

    while (Myexit != true){


        if (!myQry) {
            myQry = new char[MAXQRY];
        }


        curID = VidDir[QryCount+1].getFileID();
        if(curID == 0){
            Myexit = true;
        }


        sprintf(myQry, "SELECT * FROM mt_cds_object WHERE parent_id = %d",
                curID);
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
            ///////*****  Query for Songs

            if (QVal2.toInt() == curID) {
                VidCount++;
                string Qstr5Convert = QVal5.toStdString();
                char *QVal5Convert;
                QVal5Convert = new char[Qstr5Convert.length() + 1];
                strcpy(QVal5Convert, Qstr5Convert.c_str());
                Video[VidCount].set(QVal5Convert, QVal.toInt(), QVal2.toInt());
            }
        }

        *vidSize = VidCount;
        QryCount++;
        if (QryCount == *vidDirSize) {
            Myexit = true;
        }

        db.close();
        }
        else{
            cout << "error couldn't to mysql" << endl;
              Myexit = true;
        }
    }
    return Video;
}



songObj* mysqlconn::connectVidDir(songObj* VidDir, int vidMenu, int *vidDirSize){

    int VidDirCount = 0;

    *vidDirSize = MAXVIDEO;
    VidDir = new songObj[MAXVIDEO];

    for(int i= 0 ; i <= MAXVIDEO; i++){
        VidDir[i].set("-", 0, 0);
    }

    char *myQry = NULL;

    if (!myQry) {
        myQry = new char[MAXQRY];
    }

    /// use video menu ID  to get vid directory

    sprintf(myQry, "SELECT * FROM mt_cds_object WHERE parent_id = %d",
            vidMenu);
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
        if (QVal2.toInt() == vidMenu) {
            string Qstr5Convert = QVal5.toStdString();
            char *QVal5Convert;
            QVal5Convert = new char[Qstr5Convert.length() + 1];
            strcpy(QVal5Convert, Qstr5Convert.c_str());
            VidDir[VidDirCount].set(QVal5Convert, QVal.toInt(), QVal2.toInt());
            VidDirCount++;
        }
    }

    *vidDirSize = VidDirCount;
    db.close();
    }
    else{
        cout << "error couldn't connect to vid dir in mysql" << endl;
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


}
