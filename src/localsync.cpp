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

#include "localsync.h"

localsync::localsync()
{
    initLocalObj();

    home = getenv("HOME");
    db_local = home + TEMPSYNCPREF;
}

/*
  *  Initialize safe state
  */
void localsync::initLocalObj(){
    parentID = 0;
    lastID = 0;
    AudFolderCount = 0;
    VidFolderCount = 0;
    AudioCount = 0;
    VideoCount = 0;
    AudItemCount = 0;
    AudDirCount = 0;
    VidItemCount = 0;
    VidDirCount = 0;

    AudItemINIT = 5;
    VidItemINIT = 5;
    AudDirINIT = 5;
    VidDirINIT = 5;

    initDirs(0,5, 5);
    initFiles(0, 5, 5);

}

/*
  * Open DB connection
  */
QSqlDatabase localsync::openLocalDB(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(db_local.c_str());
    if(!db.open()){
        cout << "couldn't read locally from " << db_local.c_str() << endl;
    }
    return db;
}

/*
* Create Local Database Table
*/
void localsync::createLocalDB() {
    string finalQry[4];
    // string create = "create table ";
    finalQry[0] = "create table lcl_songdirs (key INTEGER PRIMARY KEY,lcl_dir_name TEXT,lcl_dir_path TEXT,lcl_dir_id integer,lcl_dir_par integer,lcl_dir_type TEXT)";
    finalQry[1] = "create table lcl_songs (key INTEGER PRIMARY KEY,lcl_dir_name TEXT,lcl_dir_path TEXT,lcl_dir_id integer,lcl_dir_par integer,lcl_dir_type TEXT)";
    finalQry[2] = "create table lcl_viddirs (key INTEGER PRIMARY KEY,lcl_dir_name TEXT,lcl_dir_path TEXT,lcl_dir_id integer,lcl_dir_par integer,lcl_dir_type TEXT)";
    finalQry[3] = "create table lcl_videos (key INTEGER PRIMARY KEY,lcl_dir_name TEXT,lcl_dir_path TEXT,lcl_dir_id integer,lcl_dir_par integer,lcl_dir_type TEXT)";
    for(int i=0; i<4; i++){
        writeMe(finalQry[i]);
    }
}

/*
  * Remove Directory from DB
  */
void localsync::removeDir(int selected, int mode){
    char *myQry;
    if(selected >= 0){
        if(mode == 1){
            if(selected < AudDirCount){
                myQry = new char[lclDirName[selected].length()+100];
                sprintf(myQry, "DELETE from lcl_dirs WHERE lcl_dir_name='%s'", lclDirName[selected].c_str());
                string finQry = string(myQry);
                writeMe(finQry);
            }
        }
        else{
            if(selected < VidDirCount){
                myQry = new char[lclDirName[selected].length()+100];
                sprintf(myQry, "DELETE from lcl_dirs WHERE lcl_dir_name='%s'", lclDirName[selected].c_str());
                string finQry = string(myQry);
                writeMe(finQry);
            }
        }
    }
}

/*
  * When Add is clicked
  */
void localsync::Sync(QDir usrDir, int syncType)
{
    //  QDir usrDir = QFileDialog::getExistingDirectory(this, tr("Import a directory"), QDir::currentPath());  // get folder import directory
    int lclSyncExit = 0;                    // loop check if db was created properly
    QString curDir = NULL;

    if(usrDir != QString(getenv("HOME"))){
        curDir = usrDir.absolutePath();  // get chosen path
        initLocalObj();

        //sync to db
        if(syncType == 0){  /// sync Audio
            // add main import folder
            addFolder(AudDirCount, curDir.toStdString(), usrDir.dirName().toStdString(), syncType);
            // scan main for directories
            scanDir(curDir, 0);
            scanFiles(0);
            createLocalDB();
            /// fill query
            writeDBDirs("lcl_songdirs", AudFolderCount, syncType);
            writeDBFiles("lcl_songs", AudioCount, syncType);
        }
        else{
            // add main import folder
            addFolder(VidDirCount, curDir.toStdString(), usrDir.dirName().toStdString(), syncType);
            scanDir(curDir, 1);
            scanFiles(1);
            createLocalDB();
            /// fill query
            writeDBDirs("lcl_viddirs", VidFolderCount, syncType);
            writeDBFiles("lcl_videos", VideoCount, syncType);
            lclSyncExit = 1;
        }
    }
}

/*
* Scan User Directory for folders. Add all discovered folders
*/
void localsync::scanDir(QString dir, int scanType){
    QDirIterator directories(dir, QDir::Dirs | QDir::NoDotAndDotDot);
    int count = 0;
    if(scanType == 0){
        count = AudDirCount;
    }
    else{
        count = VidDirCount;
    }
    while(directories.hasNext()){
        directories.next();
        addFolder(count, directories.filePath().toStdString(), directories.fileName().toStdString(), scanType);
        count++;
    }
}

/*
* Scan User Directory for folders. Add all discovered files
*/
void localsync::scanFiles(int scanType){
    int count = 0;
    int countSize = 0;
    if(scanType == 0){
        //   count = AudItemCount;
        countSize = AudDirCount;
    }
    else{
        //    count = VidItemCount;
        countSize = VidDirCount;
    }
    for(int i=0; i<countSize; i++){

        QDirIterator dirWalk(QString::fromStdString(lclDir[i]), QDir::Files | QDir::NoSymLinks);

        while(dirWalk.hasNext())
        {
            dirWalk.next();
            if(scanType == 0){  // if scanning audio
                if(dirWalk.fileInfo().completeSuffix() == "mp3" || dirWalk.fileInfo().completeSuffix() == "flac"){
                    addFile(count, dirWalk.filePath().toStdString(), dirWalk.fileName().toStdString(), lclDirID[i], scanType);
                    count++;
                }
            }
            else{   // if scanning video
                if(dirWalk.fileInfo().suffix() == "avi" || dirWalk.fileInfo().suffix() == "mp4"){
                    addFile(count, dirWalk.filePath().toStdString(), dirWalk.fileName().toStdString(), lclDirID[i], scanType);
                    count++;
                }
            }
        }
    }
}


/*
* Write Local Database files to local database table  type: 0 Audio 1 Video
*/
void localsync::writeDBFiles(char *dbTable, int init, int type){
    int  pos = 0, posMax = 0, counter = 0, countRemind = 0, fileCount;
    if(type == 0){ // Audio
        fileCount = AudItemCount;
    }
    else{
        fileCount = VidItemCount;
    }
    string str2;
    counter = getMaxPos(fileCount);
    posMax = counter;

    for (int m = 0; m <= (fileCount / counter); m++) {
        countRemind = 0;
        stringstream os;
        for (int i = pos; i <= posMax; i++) {
            if (i<fileCount){
                if (i != posMax && countRemind == 0) {
                    os << " INSERT INTO "<< dbTable << " (lcl_dir_name,lcl_dir_path,lcl_dir_id, lcl_dir_par,lcl_dir_type) " <<
                          "SELECT \"" << lclFileNames[i] << "\" AS \"" << "lcl_dir_name" << "\", \""
                       <<  lclFiles[i] << "\" AS \"" << "lcl_dir_path" << "\", \""
                       <<  lclFileID[i] << "\" AS \"" << "lcl_dir_id" << "\", \""
                       <<  lclFilePar[i] << "\" AS \"" << "lcl_dir_par" << "\", \""
                       <<  "songs" << "\" AS \"" << "lcl_dir_type" << "\"";
                    cout << os;
                    countRemind++;
                }
                if (i != posMax && countRemind != 0 ) {
                    os << " UNION SELECT \"" << lclFileNames[i] << "\",\""<< lclFiles[i] << "\",\"" << lclFileID[i] <<"\",\""<< lclFilePar[i]<<"\",\""<< "song" << "\"";

                } else if (i == posMax && countRemind != 0) {
                    os << ";";
                }
            }
        }
        str2 = os.str();
        writeMe(str2);
        posMax += counter;
        pos += counter;

        if (m == (fileCount / counter) - 1) {
            posMax = pos + fileCount - ((fileCount / counter)
                                        * counter);
        }
    }
}

/*
* Write Local Database Folders to local database table  type: 0 Audio 1 Video
*/
void localsync::writeDBDirs(char *dbTable, int init, int type){
    int  pos = 0, posMax = 0, counter = 0, countRemind = 0, dirCount;
    if(type == 0){ // Audio Dir
        dirCount = AudDirCount;
    }
    else{
        dirCount = VidDirCount;
    }
    string str2;
    counter = getMaxPos(dirCount);
    posMax = counter;
    /// reminder to get previous import folder position on second import
    for (int m = 0; m <= (dirCount / counter); m++) {
        countRemind = 0;
        stringstream os;
        for (int i = pos; i <= posMax; i++) {
            //   string strFin = lclD
            //            str2.erase(remove(str2.begin(), str2.end(), '\"'), str2.end());
            if (i != posMax && countRemind == 0) {
                os << " INSERT INTO "<< dbTable << " (lcl_dir_name,lcl_dir_path,lcl_dir_id,lcl_dir_par,lcl_dir_type) "
                   <<  "SELECT \"" << lclDirName[i] << "\" AS \"" << "lcl_dir_name" << "\", \""
                   <<  lclDir[i] << "\" AS \"" << "lcl_dir_path" << "\", \""
                   <<  lclDirID[i] << "\" AS \"" << "lcl_dir_id" << "\", \""
                   <<  lclDirPar[i] << "\" AS \"" << "lcl_dir_par" << "\", \""
                   <<  "folder" << "\" AS \"" << "lcl_dir_type" << "\"";
                countRemind++;
            }
            if (i != posMax && countRemind != 0) {
                os << " UNION SELECT \""<< lclDirName[i] <<"\",\""<< lclDir[i] << "\",\"" << lclDirID[i] << "\",\""<< lclDirPar[i] << "\",\""<< "folder" << "\"";

            } else if (i == posMax && countRemind != 0) {
                os << ";";
            }
        }
        str2 = os.str();
        writeMe(str2);
        posMax += counter;
        pos += counter;

        if (m == (dirCount / counter) - 1) {
            posMax = pos + dirCount - ((dirCount / counter)
                                       * counter);
        }
    }
}


/*
* Write Any string to database
*/
void localsync::writeMe(string qry){
    QSqlDatabase db = openLocalDB();
    if(db.open()){
        QSqlQuery myQry;
        myQry.prepare(qry.c_str());
        myQry.exec();

        db.close();
    }
}

/*
* allocate new initial Directory array
*/
void localsync::initDirs(int beg, int end, int count){
    string *dirCopy, *dirNameCopy;
    int *dirParCopy, *dirIDCopy;
    if(beg !=0){    // if not the inital allocation
        ///allocate copy
        dirCopy = new string[count];
        dirNameCopy = new string[count];
        dirParCopy = new int[count];
        dirIDCopy = new int[count];
        for(int i=0; i<count; i++){
            dirCopy[i] = "-"; dirNameCopy[i] = "-";
            dirParCopy[i] = 0; dirIDCopy[i] = 0;
        }
        /// copy from resideFiles to resideCopy
        for(int i=0; i<count; i++){
            dirCopy[i] = lclDir[i]; dirNameCopy[i] = lclDirName[i];
            dirParCopy[i] = lclDirPar[i];dirIDCopy[i] = lclDirID[i];
        }
        delete [] lclDir; delete [] lclDirName;
        delete [] lclDirPar; delete [] lclDirID;
    }
    /// initialize new resideFileArray
    lclDir = new string[count+end];
    lclDirName = new string[count+end];
    lclDirPar = new int[count+end];
    lclDirID = new int[count+end];
    for(int i=0; i<end; i++){
        lclDir[i] = "-"; lclDirName[i] = "-";
        lclDirPar[i] = 0; lclDirID[i] = 0;
    }

    if(beg != 0){    // if not the inital allocation
        /// fill with contents of copy
        for(int i=0; i<count; i++){
            lclDir[i] = dirCopy[i];
            lclDirName[i] = dirNameCopy[i];
            lclDirPar[i] = dirParCopy[i];
            lclDirID[i] = dirIDCopy[i];
        }
    }
}

/*
* allocate new initial file array
*/
void localsync::initFiles(int beg, int end, int count){
    string *fileCopy, *fileNameCopy;
    int *fileIDCopy, *fileParCopy;
    if(beg !=0){    // if not the inital allocation
        ///allocate copy
        fileCopy = new string[count];
        fileNameCopy = new string[count];
        fileIDCopy = new int[count];
        fileParCopy = new int[count];
        for(int i=0; i<count; i++){
            fileCopy[i] = "-"; fileNameCopy[i] = "-";
            fileIDCopy[i] = 0; fileParCopy[i] = 0;
        }
        /// copy from resideFiles to resideCopy
        for(int i=0; i<count; i++){
            fileCopy[i] = lclFiles[i]; fileNameCopy[i] = lclFileNames[i];
            fileParCopy[i] = lclFilePar[i]; fileIDCopy[i] = lclFileID[i];
        }
        delete [] lclFiles; delete [] lclFileNames;
        delete [] lclFilePar; delete [] lclFileID;
    }
    /// initialize new resideFileArray
    lclFiles = new string[count+end];
    lclFileNames = new string[count+end];
    lclFilePar = new int[count+end];
    lclFileID = new int[count+end];
    for(int i=0; i<end; i++){
        lclFiles[i] = "-"; lclFileNames[i] = "-";
        lclFilePar[i] = 0;  lclFileID[i] = 0;
    }

    if(beg != 0){    // if not the inital allocation
        /// fill with contents of copy
        for(int i=0; i<count; i++){
            lclFiles[i] = fileCopy[i];
            lclFileNames[i] = fileNameCopy[i];
            lclFilePar[i] = fileParCopy[i];
            lclFileID[i] = fileIDCopy[i];
        }
    }
}

/*
  * Get last ID from last entry in database
  */
void localsync::getLastIDs(){
    int IDcounter =0;
    if(QFile::exists(db_local.c_str())){
        QSqlDatabase db = openLocalDB();
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
                        AudFolderCount = query.value(3).toInt();
                    }
                    else if(IDcounter == 1){
                        VidFolderCount = query.value(3).toInt();
                    }
                    else if(IDcounter == 2){
                        AudioCount = query.value(3).toInt();
                    }
                    else if(IDcounter == 3){
                        VideoCount = query.value(3).toInt();
                    }
                }
            }

            db.close();
        }
    }
}

/*
  *  Get maximum write count
  */
int localsync::getMaxPos(int count) {
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


localsync::~localsync()
{
    delete [] lclFiles;
    delete [] lclFileNames;
    delete [] lclFilePar;
    delete [] lclFileID;
    delete [] lclDir;
    delete [] lclDirName;
    delete [] lclDirPar;
    delete [] lclDirID;
}
