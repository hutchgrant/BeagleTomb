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


#include "sync.h"
using namespace std;
syncMe::syncMe(const char *server, const char *user, const char *pass,
               const char *table, const char *dbLocation) {
    string home = getenv("HOME");
     string temp_pref = home + TEMPSYNCPREF;
   db = QSqlDatabase::addDatabase("QSQLITE", "connection");
   db.setDatabaseName(temp_pref.c_str());


   if(control(server, user, pass, table, dbLocation)==0){
        // future error popup
   }


}

void syncMe::deleteDB(const char *dbLocation) {
    char FinalLink[150];
    sprintf(FinalLink, "rm %s ", dbLocation);
    system(FinalLink);
}

void syncMe::OpenDB(){

}

void syncMe::createDB(const char *dbLocation) {
    string finalQry[7];
    finalQry[0] = "create table Artists(key INTEGER PRIMARY KEY,Artist TEXT,ArtistID integer, ArtistPar integer) ";
    finalQry[1] = "create table Albums(key INTEGER PRIMARY KEY,Album TEXT,AlbumID integer, AlbumPar integer)";
    finalQry[2] = "create table Songs(key INTEGER PRIMARY KEY,Song TEXT,SongID integer, SongPar integer)";
    finalQry[3] = "create table Videos(key INTEGER PRIMARY KEY,Video TEXT,VideoID integer, VideoPar integer)";
    finalQry[4] = "create table VidDirs(key INTEGER PRIMARY KEY,VidDir TEXT,VidDirID integer, VidDirPar integer)";
    finalQry[5] = "create table pref(key INTEGER PRIMARY KEY,usr TEXT,PASS TEXT,SERVER TEXT,PRT TEXT,SQLTABLE TEXT,SQL TEXT,PLAYLISTDIR TEXT)";
    finalQry[6] = "create table radio(id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL DEFAULT (0),name TEXT NOT NULL,url TEXT NOT NULL)";
    for(int i=0; i<7; i++){
        writeMe(finalQry[i]);
    }
}

int syncMe::control(const char *server, const char *user, const char *pass,
                    const char *table, const char *dbLocation) {
    DBLocation = dbLocation;
    int artMenu, vidDirMenu; /// main Artist Menu ID
    int artSize, albSize, songSize, vidSize, vidDirSize; /// sizes of each Object array

    artMenu = 0, artSize = 0, albSize = 0 ,songSize = 0;
    vidSize = 0, vidDirSize = 0;

    /// init Objects
    songObj *Artist = NULL, *Album = NULL, *Song = NULL, *VidDir = NULL, *Video = NULL;
    songObj *newSong, *newAlbum, *newArtist;
    songObj *newVideo, *newVidDir;
    //attempt to delete previous DB
    deleteDB(dbLocation);

    //create new DB
    createDB(dbLocation);

    /// init mysqlObject
    mysqlconn ms(server, user, pass, table);

    // get main artist menu
    artMenu = ms.connectArtMenu();
    vidDirMenu = ms.connectVidMenu();
    // get from mysql each artist,album,song - store and return objects
    newArtist = ms.connectArtist(Artist, artMenu, &artSize);
    newAlbum = ms.connectAlbum(newArtist, &artSize, Album, &albSize);
    newSong = ms.connectSong(newAlbum, &albSize, Song, &songSize);
    newVidDir = ms.connectVidDir(VidDir, vidDirMenu, &vidDirSize);
    newVideo = ms.connectVideo(newVidDir, &vidDirSize, Video, &vidSize);
    if(artMenu ==0){
        cout << "empty database or invalid login" << endl;
        return 0;
    }
    else{
    ///  sync artist,album,song objects to the local sql database
    artistWrite(newArtist, artSize);
    albumWrite(newAlbum, albSize);
    songWrite(newSong, songSize);
    vidDirWrite(newVidDir, vidDirSize);
    videoWrite(newVideo, vidSize);
    return 1;
    }
}

void syncMe::artistWrite(songObj* Artist, int artSize){
    int  pos = 0, posMax = 0, counter = 0, countRemind = 0;

    string str2;
    counter = getMaxPos(artSize);
    posMax = counter;

    for (int m = 0; m <= (artSize / counter); m++) {
        countRemind = 0;
        stringstream os;
        for (int i = pos; i <= posMax; i++) {
            str2 = Artist[i].getFile();

            str2.erase(remove(str2.begin(), str2.end(), '\"'), str2.end());
            Artist[i].setFile((char *)str2.c_str());
            //           cout << str2 << endl;
            if (i != posMax && countRemind == 0) {
                os << " INSERT INTO artists (Artist,ArtistID,ArtistPar) " <<
                      "SELECT \"" << Artist[i].getFile() << "\" AS \"" << "Artist" << "\", \""
                   <<  Artist[i].getFileID() << "\" AS \"" << "ArtistID" << "\", \""
                   << Artist[i].getFilePar() << "\" AS \"" << "ArtistPar" << "\"";
                //             cout << os;
                countRemind++;
            }
            if (i != posMax && countRemind != 0) {
                os << " UNION SELECT \""<< Artist[i].getFile()<<"\",\""<< Artist[i].getFileID()<<"\",\""<<Artist[i].getFilePar()<<"\"";

            } else if (i == posMax && countRemind != 0) {
                os << ";";
            }
        }
        str2 = os.str();
        writeMe(str2);
        posMax += counter;
        pos += counter;

        if (m == (artSize / counter) - 1) {
            posMax = pos + artSize - ((artSize / counter)
                                      * counter);
        }
    }
}

void syncMe::albumWrite(songObj* Album, int albSize){
    int  pos = 0, posMax = 0, counter = 0, countRemind = 0;

    string str2;
    counter = getMaxPos(albSize);
    posMax = counter;

    for (int m = 0; m <= (albSize / counter); m++) {
        countRemind = 0;
        stringstream os;
        for (int i = pos; i <= posMax; i++) {
            str2 = Album[i].getFile();

            str2.erase(remove(str2.begin(), str2.end(), '\"'), str2.end());
            Album[i].setFile((char *)str2.c_str());
            //         cout << str2 << endl;
            if (i != posMax && countRemind == 0) {
                os << " INSERT INTO albums (Album,AlbumID,AlbumPar) " <<
                      "SELECT \"" << Album[i].getFile() << "\" AS \"" << "Album" << "\", \""
                   <<  Album[i].getFileID() << "\" AS \"" << "AlbumID" << "\", \""
                   << Album[i].getFilePar() << "\" AS \"" << "AlbumPar" << "\"";
                //           cout << os;
                countRemind++;
            }
            if (i != posMax && countRemind != 0) {
                os << " UNION SELECT \""<< Album[i].getFile()<<"\",\""<< Album[i].getFileID()<<"\",\""<<Album[i].getFilePar()<<"\"";

            } else if (i == posMax && countRemind != 0) {
                os << ";";
            }
        }
        str2 = os.str();
        writeMe(str2);
        posMax += counter;
        pos += counter;

        if (m == (albSize / counter) - 1) {
            posMax = pos + albSize - ((albSize / counter)
                                      * counter);
        }
    }
}
void syncMe::songWrite(songObj* Song, int songSize){
    int  pos = 0, posMax = 0, counter = 0, countRemind = 0;

    string str2;
    counter = getMaxPos(songSize);
    posMax = counter;

    for (int m = 0; m <= (songSize / counter); m++) {
        countRemind = 0;
        stringstream os;
        for (int i = pos; i <= posMax; i++) {
            str2 = Song[i].getFile();

            str2.erase(remove(str2.begin(), str2.end(), '\"'), str2.end());
            Song[i].setFile((char *)str2.c_str());
            //         cout << str2 << endl;
            if (i != posMax && countRemind == 0) {
                os << " INSERT INTO songs (Song,SongID,SongPar) " <<
                      "SELECT \"" << Song[i].getFile() << "\" AS \"" << "Song" << "\", \""
                   <<  Song[i].getFileID() << "\" AS \"" << "SongID" << "\", \""
                   << Song[i].getFilePar() << "\" AS \"" << "SongPar" << "\"";
                //           cout << os;
                countRemind++;
            }
            if (i != posMax && countRemind != 0) {
                os << " UNION SELECT \""<< Song[i].getFile()<<"\",\""<< Song[i].getFileID()<<"\",\""<<Song[i].getFilePar()<<"\"";

            } else if (i == posMax && countRemind != 0) {
                os << ";";
            }
        }
        str2 = os.str();
        writeMe(str2);
        posMax += counter;
        pos += counter;

        if (m == (songSize / counter) - 1) {
            posMax = pos + songSize - ((songSize / counter)
                                       * counter);
        }
    }
}

void syncMe::vidDirWrite(songObj* vidDir, int vidDirSize){
    int  pos = 0, posMax = 0, counter = 0, countRemind = 0;

    string str2;
    counter = getMaxPos(vidDirSize);
    posMax = counter;

    for (int m = 0; m <= (vidDirSize / counter); m++) {
        countRemind = 0;
        stringstream os;
        for (int i = pos; i <= posMax; i++) {
            str2 = vidDir[i].getFile();

            str2.erase(remove(str2.begin(), str2.end(), '\"'), str2.end());
            vidDir[i].setFile((char *)str2.c_str());
            //       cout << str2 << endl;
            if (i != posMax && countRemind == 0) {
                os << " INSERT INTO viddirs (VidDir,VidDirID,VidDirPar) " <<
                      "SELECT \"" << vidDir[i].getFile() << "\" AS \"" << "VidDir" << "\", \""
                   <<  vidDir[i].getFileID() << "\" AS \"" << "VidDirID" << "\", \""
                   << vidDir[i].getFilePar() << "\" AS \"" << "VidDirPar" << "\"";
                //          cout << os;
                countRemind++;
            }
            if (i != posMax && countRemind != 0) {
                os << " UNION SELECT \""<< vidDir[i].getFile()<<"\",\""<< vidDir[i].getFileID()<<"\",\""<<vidDir[i].getFilePar()<<"\"";

            } else if (i == posMax && countRemind != 0) {
                os << ";";
            }
        }
        str2 = os.str();
        writeMe(str2);
        posMax += counter;
        pos += counter;

        if (m == (vidDirSize / counter) - 1) {
            posMax = pos + vidDirSize - ((vidDirSize / counter)
                                         * counter);
        }
    }
}


void syncMe::videoWrite(songObj* Video, int vidSize){
    int  pos = 0, posMax = 0, counter = 0, countRemind = 0;

    string str2;
    counter = getMaxPos(vidSize);
    posMax = counter;

    for (int m = 0; m <= (vidSize / counter); m++) {
        countRemind = 0;
        stringstream os;
        for (int i = pos; i <= posMax; i++) {
            str2 = Video[i].getFile();

            str2.erase(remove(str2.begin(), str2.end(), '\"'), str2.end());
            Video[i].setFile((char *)str2.c_str());
            //        cout << str2 << endl;
            if (i != posMax && countRemind == 0) {
                os << " INSERT INTO videos (Video,VideoID,VideoPar) " <<
                      "SELECT \"" << Video[i].getFile() << "\" AS \"" << "Video" << "\", \""
                   <<  Video[i].getFileID() << "\" AS \"" << "VideoID" << "\", \""
                   << Video[i].getFilePar() << "\" AS \"" << "VideoPar" << "\"";
                //           cout << os;
                countRemind++;
            }
            if (i != posMax && countRemind != 0) {
                os << " UNION SELECT \""<< Video[i].getFile()<<"\",\""<< Video[i].getFileID()<<"\",\""<<Video[i].getFilePar()<<"\"";

            } else if (i == posMax && countRemind != 0) {
                os << ";";
            }
        }
        str2 = os.str();
        writeMe(str2);
        posMax += counter;
        pos += counter;

        if (m == (vidSize / counter) - 1) {
            posMax = pos + vidSize - ((vidSize / counter)
                                      * counter);
        }
    }
}

void syncMe::writeMe(string qry){

       if(db.open()){
           QSqlQuery myQry(db);
           myQry.prepare(qry.c_str());
           myQry.exec();
           db.close();
       }
}


int syncMe::getMaxPos(int count) {
    int posMax;

    if (count < 400 && count > 100) {
        posMax = 100;
    } else if (count < 100 && count > 20) {
        posMax = 10;
    } else if (count < 20) {
        posMax = 5;
    } else if (count < 20 && count > 10) {
        posMax = 1;
    } else {
        posMax = 200;
    }
    return posMax;
}

syncMe::~syncMe() {
   // db.close();
}
