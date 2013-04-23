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
#include "remotesync.h"

/*
  * constructor
  */
remotesync::remotesync()
{

}

/*
  * Set global preferences and initialize database
  */
void remotesync::setPref(prefObj &src){
    pref = src;
    openDB();
}
/*
  * open mysql database from global preferences
  */
void remotesync::openDB(){
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(pref.getQHOSTIP());
    db.setDatabaseName(pref.getQTable());
    db.setUserName(pref.getQUser());
    db.setPassword(pref.getQPass());
}

void remotesync::closeDB(){
    QSqlDatabase::removeDatabase("QMYSQL");
}

/*
  * fill file objects from mysql
  */
void remotesync::Fill(fileObj &Artist, fileObj &Album, fileObj &Song, fileObj &VidDir, fileObj &Video){
    int artMenu, vidDirMenu; /// main Artist Menu ID

     artMenu = getAudioMenu();
    cout << "connected to artist menu" << endl;
     vidDirMenu = getVideoMenu();
     cout << "connected to video menu" << endl;
     connectTracks(Artist, Artist, artMenu, 1);
     cout << "received Artists from artMenu: " << artMenu << endl;
     connectTracks(Artist, Album, 0, 2);
     cout << "received Albums" << endl;
     connectTracks(Album, Song, 0, 3);
     cout << "received songs from albums"  << endl;
     connectTracks(VidDir,VidDir,vidDirMenu, 1);
     cout << "received VidDirs from VidDirMenu: " << vidDirMenu  << endl;
     connectTracks(VidDir,Video, 0, 3);
     cout << "all videos received" << endl;

}

/*
  * get mediatomb audio menu
  */
int remotesync::getAudioMenu(){
    int audMenu = 0;


    int  QryCount = 0, menu = 0, artMenu = 0;
    bool Myexit = false; // exit variable

    char *myQry = NULL;

    if(db.open()){

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
                    audMenu);
        }

            QSqlQuery query;
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
                        audMenu = QVal.toInt();
                    }
                }

                //check for Audio menus
                else if (QVal2.toInt() == audMenu) {
                    artMenu++;
                    //set ID of artist sub Menu
                    if (artMenu == 4) {
                        audMenu = QVal.toInt();
                    }
                }

            }
            QryCount++;
            if (QryCount > 3) { // + albCount
                Myexit = true;
            }
    }
}else{
            cout << "error couldn't connect to mysql" << endl;
            Myexit = true;
}

    return audMenu;
}

/*
  * get mediatomb Video menu
  */
int remotesync::getVideoMenu(){
 int vidMenu = 0;
 int vidDirMenuID = 0;

 bool Myexit = false; // exit variable
 int QryCount = 0;
 int rowCount = 0;
 char *myQry = NULL;

 if(db.open()){

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
                 vidMenu);
     }


         QSqlQuery query;
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
                 vidMenu = QVal.toInt();
             }

             if(QVal2.toInt() == vidMenu && rowCount == 1){
                 vidDirMenuID = QVal.toInt();
             }
             rowCount++;

         }
         QryCount++;
         if (QryCount > 2) { // + albCount
             Myexit = true;
         }
     }
 }else{
         cout << "error couldn't connect to vid menu in mysql" << endl;
         Myexit = true;
}
return vidMenu;
}

/*
  * connect objects with mysql
  */
void remotesync::connectTracks(fileObj &folder, fileObj &src, int lookID, int mode){
    char *myQry = NULL;     /// string for final query

    if(mode == 1){  // ARTISTS
        int artCount = 0;
        if(!myQry){
            myQry = new char[MAXQRY];
            sprintf(myQry, "SELECT * FROM mt_cds_object WHERE parent_id = %d", lookID );
        }
        if(db.open()){
            QSqlQuery query;
            query = QString(myQry);
            while(query.next()){
                QString QVal = query.value(0).toString();
                QString QVal1 = query.value(1).toString();
                QString QVal2 = query.value(2).toString();
                QString QVal3 = query.value(3).toString();
                QString QVal4 = query.value(4).toString();
                QString QVal5 = query.value(5).toString();

                ///////*****  Query for Songs
                if (QVal2.toInt() == lookID) {
                    src.set(artCount, QVal.toInt(), QVal2.toInt(), QVal5.toStdString().c_str());
                    artCount++;
                }

            }
        }
    }
    else if(mode == 2 || mode == 3){  // ALBUMS // SONGS
        int albCount = 0;
        int songCount = 0;
        int qryCount = 0;
        int curID = 0;
        bool Exit = false;

        if(db.open()){
        while(!Exit){
            if(!myQry){
                myQry = new char[MAXQRY];
            }
            curID = folder.getID(qryCount);
            if(curID == 0){
                Exit = 1;
            }
            sprintf(myQry, "SELECT * FROM mt_cds_object WHERE parent_id = %d", curID );


                QSqlQuery query;
                query = QString(myQry);
                while(query.next()){
                    QString QVal = query.value(0).toString();
                    QString QVal1 = query.value(1).toString();
                    QString QVal2 = query.value(2).toString();
                    QString QVal3 = query.value(3).toString();
                    QString QVal4 = query.value(4).toString();
                    QString QVal5 = query.value(5).toString();

                    ///////*****  Query for Album rows using artist
                    if(mode == 2 && QVal4.toStdString().compare("object.container.album.musicAlbum") == 0){
                        if (QVal2.toInt() == curID) {
                            src.set(albCount, QVal.toInt(), QVal2.toInt(), QVal5.toStdString().c_str());
                            albCount++;
                        }
                    }
                    if(mode == 3 && QVal2.toInt() == curID){
                            src.set(songCount, QVal.toInt(), QVal2.toInt(), QVal5.toStdString().c_str());
                            songCount++;
                    }

                }
                qryCount++;
                if (qryCount == folder.getSize()-1) {
                    Exit = true;
                }
            }
        }
    }
}
/*
  * deconstructor
  */
remotesync::~remotesync(){
    closeDB();
}
