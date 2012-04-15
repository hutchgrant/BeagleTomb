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
syncMe::syncMe(preferences &src) {

    if(control(src) == 0){

    }

}


/// remove All File databases
void syncMe::deleteDB() {
    string finalRMPrefqry[5];
    finalRMPrefqry[0] =  "drop table if exists artists";
    finalRMPrefqry[1] =  "drop table if exists albums";
    finalRMPrefqry[2] =  "drop table if exists songs";
    finalRMPrefqry[3] =  "drop table if exists videos";
    finalRMPrefqry[4] =  "drop table if exists viddirs";

        for(int i= 0; i<=4; i++){
            writeMe(finalRMPrefqry[i]);
        }
}

QSqlDatabase syncMe::OpenDB(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(pref.getQSQL());
    if(!db.open()){
        cout << "unable to connect with " << pref.getSQL() << endl;
    }
    return db;
}

void syncMe::closeDB(){
    QSqlDatabase::removeDatabase("QSQLITE");
}

void syncMe::createDB() {
    string finalQry[5];
    finalQry[0] = "create table Artists(key INTEGER PRIMARY KEY,Artist TEXT,ArtistID integer, ArtistPar integer) ";
    finalQry[1] = "create table Albums(key INTEGER PRIMARY KEY,Album TEXT,AlbumID integer, AlbumPar integer)";
    finalQry[2] = "create table Songs(key INTEGER PRIMARY KEY,Song TEXT,SongID integer, SongPar integer)";
    finalQry[3] = "create table Videos(key INTEGER PRIMARY KEY,Video TEXT,VideoID integer, VideoPar integer)";
    finalQry[4] = "create table VidDirs(key INTEGER PRIMARY KEY,VidDir TEXT,VidDirID integer, VidDirPar integer)";
    for(int i=0; i<=4; i++){
        writeMe(finalQry[i]);
    }
}

int syncMe::control(preferences &src) {
    DBLocation = src.getQSQL();
    pref = src;
    int artMenu, vidDirMenu; /// main Artist Menu ID
    int artSize, albSize, songSize, vidSize, vidDirSize; /// sizes of each Object array

    artMenu = 0, artSize = 0, albSize = 0 ,songSize = 0;
    vidSize = 0, vidDirSize = 0;

    /// init Objects
    fileObj Artist, Album, Song, VidDir, Video;

    deleteDB();
    createDB();

    // connect to new db

    /// init mysqlObject
    mysqlconn ms(src);
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
        writeAllRemote(Artist, Album, Song, VidDir, Video);
        return 1;
    }
}


/*
  * Write All Remote Medaitomb objects
  */
void syncMe::writeAllRemote(fileObj &Artist, fileObj &Album, fileObj &Song, fileObj &VidDir, fileObj &Video){
    int pos = 0, posMax = 0, countRemind = 0, counter = 0;   /// counter for individual files within each file object

    int objSize = 0;   // size of each object
    int TotalWrites = 0;    /// counter for number of objects looped
    string str2;
    string insertStr, col1, col2, col3;
    fileObj src;
    while(TotalWrites<=5){
        TotalWrites++;
        if(TotalWrites == 1){
            objSize = Artist.getSize();
            src = Artist;
            insertStr =  " INSERT INTO artists (Artist,ArtistID,ArtistPar) ";
            col1 = "Artist"; col2 = "ArtistID"; col3 = "ArtistPar";
        }
        else if(TotalWrites == 2){
            objSize = Album.getSize();
            src = Album;
            insertStr =  " INSERT INTO albums (Album,AlbumID,AlbumPar) ";
            col1 = "Album"; col2 = "AlbumID"; col3 = "AlbumPar";
        }
        else if(TotalWrites == 3){
            objSize = Song.getSize();
            src = Song;
            insertStr =  " INSERT INTO songs (Song,SongID,SongPar) ";
            col1 = "Song"; col2 = "SongID"; col3 = "SongPar";
        }
        else if(TotalWrites == 4){
            objSize = VidDir.getSize();
            src = VidDir;
            insertStr =  " INSERT INTO viddirs (VidDir,VidDirID,VidDirPar) ";
            col1 = "VidDir"; col2 = "VidDirID"; col3 = "VidDirPar";
        }
        else if(TotalWrites == 5){
            objSize = Video.getSize();
            src = Video;
            insertStr =  " INSERT INTO videos (Video,VideoID,VideoPar) ";
            col1 = "Video"; col2 = "VideoID"; col3 = "VideoPar";
        }
        pos = 0, posMax = 0,counter = 0, countRemind = 0;   /// counter for individual files within each file object

            counter = getMaxPos(objSize);
            posMax = counter;
            for (int m = 0; m <= (objSize / counter); m++) {
                countRemind = 0;
                stringstream os;
                for (int i = pos; i <= posMax; i++) {
                    str2 = src.getName(i);

                    str2.erase(remove(str2.begin(), str2.end(), '\"'), str2.end());
                    src.setName(i,(char *)str2.c_str());

                    if (i != posMax && countRemind == 0) {
                        os << insertStr << "SELECT \""
                           << src.getName(i) << "\" AS \"" << col1 << "\", \""
                           <<  src.getID(i) << "\" AS \"" << col2 << "\", \""
                           << src.getPar(i) << "\" AS \"" << col3 << "\"";
                        countRemind++;
                    }
                    if (i != posMax && countRemind != 0) {
                        os << " UNION SELECT \""<< src.getName(i)<<"\",\""<< src.getID(i)<<"\",\""<< src.getPar(i)<<"\"";

                    } else if (i == posMax && countRemind != 0) {
                        os << ";";
                    }
                }
                str2 = os.str();
             //   cout << str2 << endl;
                writeMe(str2);

                closeDB();
                posMax += counter;
                pos += counter;

                if (m == (objSize / counter) - 1) {
                    posMax = pos + objSize - ((objSize / counter)
                                              * counter);
                }
            }
        }


}

void syncMe::writeMe(string qry){
    QSqlDatabase db = OpenDB();
    if(db.open()){
        QSqlQuery dbqry;
        dbqry.prepare(qry.c_str());
        dbqry.exec();
    }
    closeDB();



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
    closeDB();
}
