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
    fileObj Artist, Album, Song, VidDir, Video;
    //attempt to delete previous DB
    deleteDB(dbLocation);

    //create new DB
    createDB(dbLocation);

    /// init mysqlObject
    mysqlconn ms(server, user, pass, table);

    // get main artist menu
    artMenu = ms.connectArtMenu();
    vidDirMenu = ms.connectVidMenu();
    // query mysql each artist,album,song,vidDir,video - store and return objects
    Artist = ms.connectArtist(artMenu, Artist);
    Album = ms.connectAlbum(Artist, Album);
    //  Album.display();
    Song = ms.connectSong(Album,Song);
    VidDir = ms.connectVidDir(vidDirMenu,VidDir);
    Video = ms.connectVideo(VidDir,Video);

    if(artMenu ==0){
        cout << "empty database or invalid login" << endl;
        return 0;
    }
    else{
        ///  sync artist,album,song objects to the local sql database
        artistWrite(Artist);
        albumWrite(Album);
        songWrite(Song);
        vidDirWrite(VidDir);
        videoWrite(Video);
        return 1;
    }
}

void syncMe::artistWrite(fileObj& Artist){
    int  pos = 0, posMax = 0, counter = 0, countRemind = 0;
    int artSize =0;
    artSize = Artist.getSize();
    string str2;
    counter = getMaxPos(artSize);
    posMax = counter;

    for (int m = 0; m <= (artSize / counter); m++) {
        countRemind = 0;
        stringstream os;
        for (int i = pos; i <= posMax; i++) {
            str2 = Artist.getName(i);

            str2.erase(remove(str2.begin(), str2.end(), '\"'), str2.end());
            Artist.setName(i,(char *)str2.c_str());
            //           cout << str2 << endl;
            if (i != posMax && countRemind == 0) {
                os << " INSERT INTO artists (Artist,ArtistID,ArtistPar) " <<
                      "SELECT \"" << Artist.getName(i) << "\" AS \"" << "Artist" << "\", \""
                   <<  Artist.getID(i) << "\" AS \"" << "ArtistID" << "\", \""
                   << Artist.getPar(i) << "\" AS \"" << "ArtistPar" << "\"";
                //             cout << os;
                countRemind++;
            }
            if (i != posMax && countRemind != 0) {
                os << " UNION SELECT \""<< Artist.getName(i)<<"\",\""<< Artist.getID(i)<<"\",\""<<Artist.getPar(i)<<"\"";

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

void syncMe::albumWrite(fileObj& Album){
    int  pos = 0, posMax = 0, counter = 0, countRemind = 0;
    int albSize = 0;
    albSize = Album.getSize();
    string str2;

    counter = getMaxPos(albSize);
    posMax = counter;

    for (int m = 0; m <= (albSize / counter); m++) {
        countRemind = 0;
        stringstream os;
        for (int i = pos; i <= posMax; i++) {
            str2 = Album.getName(i);

            str2.erase(remove(str2.begin(), str2.end(), '\"'), str2.end());
            Album.setName(i,(char *)str2.c_str());
            //         cout << str2 << endl;
            if (i != posMax && countRemind == 0) {
                os << " INSERT INTO albums (Album,AlbumID,AlbumPar) " <<
                      "SELECT \"" << Album.getName(i) << "\" AS \"" << "Album" << "\", \""
                   <<  Album.getID(i) << "\" AS \"" << "AlbumID" << "\", \""
                   << Album.getPar(i) << "\" AS \"" << "AlbumPar" << "\"";
                //           cout << os;
                countRemind++;
            }
            if (i != posMax && countRemind != 0) {
                os << " UNION SELECT \""<< Album.getName(i)<<"\",\""<< Album.getID(i)<<"\",\""<<Album.getPar(i)<<"\"";

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
void syncMe::songWrite(fileObj& Song){
    int  pos = 0, posMax = 0, counter = 0, countRemind = 0;
    int songSize = 0;
    songSize = Song.getSize();
    string str2;
    counter = getMaxPos(songSize);
    posMax = counter;

    for (int m = 0; m <= (songSize / counter); m++) {
        countRemind = 0;
        stringstream os;
        for (int i = pos; i <= posMax; i++) {
            str2 = Song.getName(i);

            str2.erase(remove(str2.begin(), str2.end(), '\"'), str2.end());
            Song.setName(i,(char *)str2.c_str());
            //         cout << str2 << endl;
            if (i != posMax && countRemind == 0) {
                os << " INSERT INTO songs (Song,SongID,SongPar) " <<
                      "SELECT \"" << Song.getName(i) << "\" AS \"" << "Song" << "\", \""
                   <<  Song.getID(i) << "\" AS \"" << "SongID" << "\", \""
                   << Song.getPar(i) << "\" AS \"" << "SongPar" << "\"";
                //           cout << os;
                countRemind++;
            }
            if (i != posMax && countRemind != 0) {
                os << " UNION SELECT \""<< Song.getName(i)<<"\",\""<< Song.getID(i)<<"\",\""<<Song.getPar(i)<<"\"";

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

void syncMe::vidDirWrite(fileObj& vidDir){
    int  pos = 0, posMax = 0, counter = 0, countRemind = 0;
    int vidDirSize = 0;
    vidDirSize = vidDir.getSize();
    string str2;
    counter = getMaxPos(vidDirSize);
    posMax = counter;

    for (int m = 0; m <= (vidDirSize / counter); m++) {
        countRemind = 0;
        stringstream os;
        for (int i = pos; i <= posMax; i++) {
            str2 = vidDir.getName(i);

            str2.erase(remove(str2.begin(), str2.end(), '\"'), str2.end());
            vidDir.setName(i,(char *)str2.c_str());
            //       cout << str2 << endl;
            if (i != posMax && countRemind == 0) {
                os << " INSERT INTO viddirs (VidDir,VidDirID,VidDirPar) " <<
                      "SELECT \"" << vidDir.getName(i) << "\" AS \"" << "VidDir" << "\", \""
                   <<  vidDir.getID(i) << "\" AS \"" << "VidDirID" << "\", \""
                   << vidDir.getPar(i) << "\" AS \"" << "VidDirPar" << "\"";
                //          cout << os;
                countRemind++;
            }
            if (i != posMax && countRemind != 0) {
                os << " UNION SELECT \""<< vidDir.getName(i)<<"\",\""<< vidDir.getID(i)<<"\",\""<<vidDir.getPar(i)<<"\"";

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


void syncMe::videoWrite(fileObj& Video){
    int  pos = 0, posMax = 0, counter = 0, countRemind = 0;
    int vidSize = 0;
    vidSize = Video.getSize();
    string str2;
    counter = getMaxPos(vidSize);
    posMax = counter;

    for (int m = 0; m <= (vidSize / counter); m++) {
        countRemind = 0;
        stringstream os;
        for (int i = pos; i <= posMax; i++) {
            str2 = Video.getName(i);

            str2.erase(remove(str2.begin(), str2.end(), '\"'), str2.end());
            Video.setName(i,(char *)str2.c_str());
            //        cout << str2 << endl;
            if (i != posMax && countRemind == 0) {
                os << " INSERT INTO videos (Video,VideoID,VideoPar) " <<
                      "SELECT \"" << Video.getName(i) << "\" AS \"" << "Video" << "\", \""
                   <<  Video.getID(i) << "\" AS \"" << "VideoID" << "\", \""
                   << Video.getPar(i) << "\" AS \"" << "VideoPar" << "\"";
                //           cout << os;
                countRemind++;
            }
            if (i != posMax && countRemind != 0) {
                os << " UNION SELECT \""<< Video.getName(i)<<"\",\""<< Video.getID(i)<<"\",\""<<Video.getPar(i)<<"\"";

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
