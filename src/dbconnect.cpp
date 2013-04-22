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
#include "dbconnect.h"

dbconnect::dbconnect()
{
    string DB = "/.cache/beagleplayer/BPmedia.db";
    DBlocation = getenv("HOME") + DB;
    OpenDB();

}

void dbconnect::OpenDB(){
    if(!initDB()){
        control();
    }
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(getSQL().c_str());
}
void dbconnect::closeDB(){
    QSqlDatabase::removeDatabase(getSQL().c_str());
}

/*
* Create Local Database Table
*/
void dbconnect::createLocalDB() {
    string finalQry[12];
    finalQry[0] = "create table lcl_songdirs (key INTEGER PRIMARY KEY,lcl_dir_par integer,lcl_dir_name TEXT,lcl_dir_path TEXT)";
    finalQry[1] = "create table lcl_songs (key INTEGER PRIMARY KEY,lcl_dir_par integer,lcl_dir_name TEXT,lcl_dir_path TEXT)";
    finalQry[2] = "create table lcl_viddirs (key INTEGER PRIMARY KEY,lcl_dir_par integer,lcl_dir_name TEXT,lcl_dir_path TEXT)";
    finalQry[3] = "create table lcl_videos (key INTEGER PRIMARY KEY,lcl_dir_par integer,lcl_dir_name TEXT,lcl_dir_path TEXT)";

    finalQry[4] = "create table rem_Artists(key INTEGER PRIMARY KEY,Artist TEXT,ArtistID integer, ArtistPar integer) ";
    finalQry[5] = "create table rem_Albums(key INTEGER PRIMARY KEY,Album TEXT,AlbumID integer, AlbumPar integer)";
    finalQry[6] = "create table rem_Songs(key INTEGER PRIMARY KEY,Song TEXT,SongID integer, SongPar integer)";
    finalQry[7] = "create table rem_Videos(key INTEGER PRIMARY KEY,Video TEXT,VideoID integer, VideoPar integer)";
    finalQry[8] = "create table rem_VidDirs(key INTEGER PRIMARY KEY,VidDir TEXT,VidDirID integer, VidDirPar integer)";

    finalQry[9] = "create table playlists (key INTEGER PRIMARY KEY,lcl_dir_par integer,lcl_dir_name TEXT,lcl_dir_path TEXT)";
    finalQry[10] = "create table playlist_items (key INTEGER PRIMARY KEY,lcl_dir_par integer,lcl_dir_name TEXT,lcl_dir_path TEXT)";
    finalQry[11] = "create table pref(key INTEGER PRIMARY KEY,usr TEXT,PASS TEXT,SERVER TEXT,PRT TEXT,SQLTABLE TEXT,SQL TEXT)";

    for(int i=0; i<12; i++){
        writeMe(finalQry[i]);
    }
}

/*
  * Delete Database tables
  */
void dbconnect::dropTable(int mode){
    string finalQry[5];
    int itemCount = 0;

    if( mode == 1)  // drop local audio/video files
    {
        finalQry[0] = "drop table lcl_songdirs if exists";
        finalQry[1] = "drop table lcl_songs if exists";
        finalQry[2] = "drop table lcl_viddirs if exists";
        finalQry[3] = "drop table lcl_videos if exists";
        itemCount = 4;
    }
    else if(mode == 2){  // drop remote audio/video files
        finalQry[0] = "drop table rem_Artists if exists";
        finalQry[1] = "drop table rem_Albums if exists";
        finalQry[2] = "drop table rem_Songs if exists";
        finalQry[3] = "drop table rem_Videos if exists";
        finalQry[4] = "drop table rem_VidDirs if exists";
        itemCount = 5;
    }
    else if(mode == 3){
        finalQry[0] = "drop table pref if exists";
        itemCount = 1;

    }
    else if(mode == 4){
        finalQry[0] = "drop table playlists if exists";
        finalQry[1] = "drop table playlist_items if exists";
        itemCount = 2;
    }

    for(int i=0; i<itemCount; i++){
        writeMe(finalQry[i]);
    }
}

/*
* Write Local Database Folders to local database table  type: 0 Audio 1 Video
*/
void dbconnect::writeDB(fileObj &src, int itemCount, int type){
    int  pos = 0, posMax = 0, counter = 0, countRemind = 0;
    string dbTable;

    if(type == 0){  // directory
        dbTable = "lcl_songDirs";
    }
    else if(type ==1){
        dbTable = "lcl_songs";
    }
    else if(type == 2){
        dbTable = "lcl_vidDirs";
    }
    else if(type == 3){
        dbTable = "lcl_videos";
    }
    else if(type == 4){
        dbTable = "playlist_items";
    }
    string str2;
    if(type == 1 || type == 3){
        counter = getMaxPos(itemCount);
    }
    else{
        counter = 1;
    }
    posMax = counter;
    /// reminder to get previous import folder position on second import
    for (int m = 0; m <= (itemCount / counter); m++) {
        countRemind = 0;
        stringstream os;
        for (int i = pos; i <= posMax; i++) {
            //   string strFin = lclD
            //            str2.erase(remove(str2.begin(), str2.end(), '\"'), str2.end());
            if (i != posMax && countRemind == 0) {
                os << " INSERT INTO "<< dbTable << " (lcl_dir_par,lcl_dir_name,lcl_dir_path) "
                   <<  "SELECT \"" << src.getPar(i) << "\" AS \"" << "lcl_dir_par" << "\", \""
                   <<  src.getName(i) << "\" AS \"" << "lcl_dir_name" << "\", \""
                   <<  src.getPath(i) << "\" AS \"" << "lcl_dir_path" << "\"";
                countRemind++;
            }
            if (i != posMax && countRemind != 0) {
                os << " UNION SELECT \""<< src.getPar(i) <<"\",\""<<src.getName(i) << "\",\""<< src.getPath(i) << "\"";

            } else if (i == posMax && countRemind != 0) {
                os << ";";
            }
        }
        str2 = os.str();
        writeMe(str2);
        posMax += counter;
        pos += counter;

        if (m == (itemCount / counter) - 1) {
            posMax = pos + itemCount - ((itemCount / counter)
                                       * counter);
        }
    }
}

/*
  * Write All Remote Medaitomb objects
  */
void dbconnect::writeAllRemote(fileObj &Artist, fileObj &Album, fileObj &Song, fileObj &VidDir, fileObj &Video){
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
            insertStr =  " INSERT INTO rem_Artists (Artist,ArtistID,ArtistPar) ";
            col1 = "Artist"; col2 = "ArtistID"; col3 = "ArtistPar";
        }
        else if(TotalWrites == 2){
            objSize = Album.getSize()-1;
            src = Album;
            insertStr =  " INSERT INTO rem_Albums (Album,AlbumID,AlbumPar) ";
            col1 = "Album"; col2 = "AlbumID"; col3 = "AlbumPar";
        }
        else if(TotalWrites == 3){
            objSize = Song.getSize()-1;
            src = Song;
            insertStr =  " INSERT INTO rem_Songs (Song,SongID,SongPar) ";
            col1 = "Song"; col2 = "SongID"; col3 = "SongPar";
        }
        else if(TotalWrites == 4){
            objSize = VidDir.getSize();
            src = VidDir;
            insertStr =  " INSERT INTO rem_VidDirs (VidDir,VidDirID,VidDirPar) ";
            col1 = "VidDir"; col2 = "VidDirID"; col3 = "VidDirPar";
        }
        else if(TotalWrites == 5){
            objSize = Video.getSize()-1;
            src = Video;
            insertStr =  " INSERT INTO rem_Videos (Video,VideoID,VideoPar) ";
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
                posMax += counter;
                pos += counter;

                if (m == (objSize / counter) - 1) {
                    posMax = pos + objSize - ((objSize / counter)
                                              * counter);
                }
            }
        }


}


/*
  * Write all preferences
  */
void dbconnect::writePref(prefObj &src){
    string str2;
    stringstream os;
    os << "INSERT INTO pref (usr, PASS, SERVER, PRT, SQLTABLE, SQL) VALUES ('"
       << src.USER << "','" << src.UPASS << "','" << src.HOSTIP << "','" << src.HOSTPORT  << "','" << src.HostTable  << "','" << src.localDBPath << "')";

    str2 = os.str();
    writeMe(str2);
}


/*
* Write Any string to database
*/
void dbconnect::writeMe(string qry){
    OpenDB();
    if(db.open()){
        QSqlQuery myQry;
        myQry.prepare(qry.c_str());
        myQry.exec();
        db.close();
    }
}
void dbconnect::readLocal(fileObj &Artist, fileObj &Song, fileObj &VidDir, fileObj &Video ){
    int local = 0;
    OpenDB();

    readDB(Artist, "SELECT * FROM lcl_songdirs", local);
    readDB(Song, "SELECT * FROM lcl_songs", local);
    readDB(VidDir, "SELECT * FROM lcl_viddirs", local);
    readDB(Video, "SELECT * FROM lcl_videos", local);
}
void dbconnect::readRemote(fileObj &RemArtist, fileObj &RemAlbum, fileObj &RemSong, fileObj &RemVidDir, fileObj &RemVideo ){
    int remote = 1;
    OpenDB();

    readDB(RemArtist, "SELECT * FROM rem_Artists", remote);
    readDB(RemAlbum, "SELECT * fROM rem_Albums", remote);
    readDB(RemSong, "SELECT * FROM rem_Songs", remote);
    readDB(RemVidDir, "SELECT * FROM rem_viddirs", remote);
    readDB(RemVideo, "SELECT * FROM rem_videos" ,remote);
}
/*
  * read database and fill object src for local/remote files
  * @param: SyncMode 1)local 2) remote
  */
void dbconnect::readDB(fileObj &src, string qry, int SyncMode){
    src.initFile(100);
    QSqlQuery query;
    int count = 0;

    if(db.open()){
        query = QString(qry.c_str());
        while(query.next()){
            if(SyncMode == 0){
                QString QValID = query.value(0).toString();   // ID
                QString QValPAR = query.value(1).toString();   // PARID
                QString QValNAME = query.value(2).toString();   // NAME
                QString QValPATH = query.value(3).toString();   // PATH
                if(QValNAME.toStdString() != "-"){
                    src.set(count, QValID.toInt(), QValPAR.toInt(), QValNAME.toStdString().c_str(), QValPATH.toStdString().c_str());
                    count++;
                }
            }
            else if(SyncMode == 1){
                QString QValID = query.value(2).toString();   // ID
                QString QValPAR = query.value(3).toString();   // PARID
                QString QValNAME = query.value(1).toString();   // NAME
                QString QValPATH = query.value(0).toString();   // PATH
                if(QValNAME.toStdString() != "-"){
                    src.set(count, QValID.toInt(), QValPAR.toInt(), QValNAME.toStdString().c_str(), QValPATH.toStdString().c_str());
                    count++;
                }
            }
        }
    }
}

/// read preference table from sql
void dbconnect::readPref(prefObj &src){
     QSqlQuery query;

        if(db.open()){

            query = QString("SELECT * FROM pref");

            while (query.next()){
                QString QVal1 = query.value(1).toString();
                QString QVal2 = query.value(2).toString();
                QString QVal3 = query.value(3).toString();
                QString QVal4 = query.value(4).toString();
                QString QVal5 = query.value(5).toString();
                QString QVal6 = query.value(6).toString();


                src.setPref(QVal1.toStdString(),QVal2.toStdString(), QVal3.toStdString(),QVal4.toStdString(), QVal5.toStdString(), QVal6.toStdString());
            }

        }
        closeDB();
}

/// controls inital functions at once
void dbconnect::control(){
    PrefDialog prefDg;
    prefObj pref;
    if(prefDg.exec()==QDialog::Accepted){
        pref = prefDg.getPref();
        setSQL(pref.localDBPath);
        createCache();
        setInitDB();
        createLocalDB();
    //    dropTable(3);
        writePref(pref);
    }
}
/// get initial db file from text cache
bool dbconnect::initDB(){
    bool found = false;
    char PrefIn[100];
    FILE* fp;
    string tempcache = TEMPCACHE;
    string Cache = getenv("HOME") + tempcache;
    fp = fopen(Cache.c_str(), "r");   /// open cached db location
    if(fp != NULL){
        cout << "cache found " << endl;
        rewind(fp);
        while(!feof(fp)){
            fscanf(fp, "%s", &PrefIn);
            found = true;
        }
    }
    else{
        return false;
    }

    if(found){   // if the db (listed in this text cache) exists
        setSQL(PrefIn);  /// set SQL location
        fclose(fp);
        return true;
    }
    else{
        fclose(fp);
        return false;
    }
}
/// set initial db file in text cache
void dbconnect::setInitDB(){
    string tempcache = TEMPCACHE;
    ofstream myfile;
    string cache = getenv("HOME") + tempcache;
    myfile.open (cache.c_str());
    myfile << DBlocation.c_str();
    myfile.close();
}

/// create initial cache folders
void dbconnect::createCache(){
    string main = "/.cache/beagleplayer";
    string u_home = getenv("HOME");
    string finMain = u_home + main;
    QString q_main = finMain.c_str();
    QDir(q_main).mkdir(q_main);
}

void dbconnect::getLastIDs(int *lastID){
    if(db.open()){
        QSqlQuery query;
        query = QString("SELECT * FROM playlists");

        while(query.next()){
            *lastID = query.value(0).toInt();
        }
    }
}
/*
  * Get last ID from last entry in database
  */
void dbconnect::getLastIDs(int *AudFolderCount, int *VidFolderCount){
    int IDcounter =0;
    OpenDB();
        if(db.open()){
            QSqlQuery query;
            for(int i=0; i<4; i++){
                IDcounter = i;
                if(IDcounter == 0){
                    query = QString("SELECT * FROM lcl_songdirs");
                }
                else if(IDcounter == 1){
                    query = QString("SELECT * FROM lcl_viddirs");
                }
                else if(IDcounter == 2){
                    query = QString("SELECT * FROM lcl_songs");
                }
                else if(IDcounter == 3){
                    query = QString("SELECT * FROM lcl_videos");
                }

                while (query.next()){
                    if(IDcounter == 0){
                        *AudFolderCount = query.value(0).toInt();
                    }
                    else if(IDcounter == 1){
                        *VidFolderCount = query.value(0).toInt();
                    }
                }
            }
        }
}
/*
  *  Get maximum write count
  */
int dbconnect::getMaxPos(int count) {
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
dbconnect::dbconnect(const dbconnect& src){
    DBlocation = src.DBlocation;
}
dbconnect& dbconnect::operator=(const dbconnect& src){
    if(this != &src)
    {
        setSQL(src.DBlocation);
    }
    return *this;
}
dbconnect::~dbconnect(){
    db.close();
    closeDB();
}
