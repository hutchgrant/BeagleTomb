#include "localsync.h"


localsync::localsync()
{
    dirCount = 0;
    fileCount = 0;
    fileINIT = 0;
    dirINIT = 0;
    lastID = 0;
    parentID = 0;
    folderAddCount = 0;
    initDirs(0,5);
    initFiles(0, 5);
    home = getenv("HOME");
    db_local = home + LOCALSYNC;
    openLocalDB();
}
void localsync::openLocalDB(){
    db = QSqlDatabase::addDatabase("QSQLITE", "connection");
    db.setDatabaseName(db_local.c_str());
}
localsync::~localsync()
{
    delete [] lclFiles;
    delete [] lclFilePar;
    delete [] lclFileID;
    delete [] lclDir;
    delete [] lclDirName;
    delete [] lclDirPar;
    delete [] lclDirID;
}

/*
  * When Add is clicked
  */
void localsync::Sync(QDir usrDir, int syncType)
{

    //  QDir usrDir = QFileDialog::getExistingDirectory(this, tr("Import a directory"), QDir::currentPath());  // get folder import directory
    int lclSyncExit = 0;                    // loop check if db was created properly
    QString curDir = usrDir.absolutePath();  // get chosen path

    if(curDir != NULL){
        // add main import folder
        addFolder(dirCount, curDir.toStdString(), usrDir.dirName().toStdString());
        // scan main for directories
        scanDir(curDir);
        // scan for files in directories and main.


        //sync to db
        if(syncType == 0){  /// sync Audio
            scanFiles(0);
            while(!lclSyncExit){
                if(!QFile::exists(db_local.c_str())){
                    createLocalDB();
                }
                else{
                    /// fill query
                    writeDBDirs("lcl_songdirs");
                    writeDBFiles("lcl_songs");
                    lclSyncExit = 1;
                }
            }
        }
        else{
            scanFiles(1);
            while(!lclSyncExit){
                if(!QFile::exists(db_local.c_str())){
                    createLocalDB();
                }
                else{
                    /// fill query
                    writeDBDirs("lcl_viddirs");
                    writeDBFiles("lcl_videos");
                    lclSyncExit = 1;
                }
            }
        }
    }
}

/*
  * Remove Directory from DB
  */
void localsync::removeDir(int selected){
    char *myQry;
    if(selected >= 0){
        if(selected < dirCount){
            myQry = new char[lclDirName[selected].length()+100];
            cout << "selected = " << lclDirName[selected].c_str() << endl;
            sprintf(myQry, "DELETE from lcl_dirs WHERE lcl_dir_name='%s'", lclDirName[selected].c_str());
            string finQry = string(myQry);
            writeMe(finQry);
        }
    }
}

void localsync::initDirs(int beg, int end){
    string *dirCopy, *dirNameCopy;
    int *dirParCopy, *dirIDCopy;
    if(beg !=0){    // if not the inital allocation
        ///allocate copy
        dirCopy = new string[dirCount];
        dirNameCopy = new string[dirCount];
        dirParCopy = new int[dirCount];
        dirIDCopy = new int[dirCount];
        for(int i=0; i<dirCount; i++){
            dirCopy[i] = "-"; dirNameCopy[i] = "-";
            dirParCopy[i] = 0; dirIDCopy[i] = 0;
        }
        /// copy from resideFiles to resideCopy
        for(int i=0; i<dirCount; i++){
            dirCopy[i] = lclDir[i]; dirNameCopy[i] = lclDirName[i];
            dirParCopy[i] = lclDirPar[i];dirIDCopy[i] = lclDirID[i];
        }
        delete [] lclDir; delete [] lclDirName;
        delete [] lclDirPar; delete [] lclDirID;
    }
    /// initialize new resideFileArray
    lclDir = new string[dirCount+end];
    lclDirName = new string[dirCount+end];
    lclDirPar = new int[dirCount+end];
    lclDirID = new int[dirCount+end];
    for(int i=0; i<end; i++){
        lclDir[i] = "-"; lclDirName[i] = "-";
        lclDirPar[i] = 0; lclDirID[i] = 0;
    }

    if(beg != 0){    // if not the inital allocation
        /// fill with contents of copy
        for(int i=0; i<dirCount; i++){
            lclDir[i] = dirCopy[i];
            lclDirName[i] = dirNameCopy[i];
            lclDirPar[i] = dirParCopy[i];
            lclDirID[i] = dirIDCopy[i];
        }
    }
    dirINIT = end;
}

void localsync::initFiles(int beg, int end){
    string *fileCopy;
    int *fileIDCopy, *fileParCopy;
    if(beg !=0){    // if not the inital allocation
        ///allocate copy
        fileCopy = new string[fileCount];
        fileIDCopy = new int[fileCount];
        fileParCopy = new int[fileCount];
        for(int i=0; i<fileCount; i++){
            fileCopy[i] = "-";
            fileIDCopy[i] = 0; fileParCopy[i] = 0;
        }
        /// copy from resideFiles to resideCopy
        for(int i=0; i<fileCount; i++){
            fileCopy[i] = lclFiles[i];
            fileParCopy[i] = lclFilePar[i];
            fileIDCopy[i] = lclFileID[i];
        }
        delete [] lclFiles;
        delete [] lclFilePar; delete [] lclFileID;
    }
    /// initialize new resideFileArray
    lclFiles = new string[fileCount+end];
    lclFilePar = new int[fileCount+end];
    lclFileID = new int[fileCount+end];
    for(int i=0; i<end; i++){
        lclFiles[i] = "-";
        lclFilePar[i] = 0;  lclFileID[i] = 0;
    }

    if(beg != 0){    // if not the inital allocation
        /// fill with contents of copy
        for(int i=0; i<fileCount; i++){
            lclFiles[i] = fileCopy[i];
            lclFilePar[i] = fileParCopy[i];
            lclFileID[i] = fileIDCopy[i];
        }
    }
    fileINIT = end;
}

void localsync::scanDir(QString dir){
    QDirIterator directories(dir, QDir::Dirs | QDir::NoDotAndDotDot);
    int count = dirCount;
    while(directories.hasNext()){
        directories.next();
        addFolder(count, directories.filePath().toStdString(), directories.fileName().toStdString());
        count++;
    }
}

void localsync::scanFiles(int scanType){
    int count = fileCount;
    for(int i=0; i<dirCount; i++){

        QDirIterator dirWalk(QString::fromStdString(lclDir[i]), QDir::Files | QDir::NoSymLinks);

        while(dirWalk.hasNext())
        {
            dirWalk.next();
            if(scanType == 0){  // if scanning audio
                if(dirWalk.fileInfo().completeSuffix() == "mp3" || dirWalk.fileInfo().completeSuffix() == "flac"){
                    addFile(count, dirWalk.fileName().toStdString(), lclDirID[i]);
                    count++;
                }
            }
            else{   // if scanning video
                if(dirWalk.fileInfo().suffix() == "avi"){
                    addFile(count, dirWalk.fileName().toStdString(), lclDirID[i]);
                    count++;
                }
            }
        }
    }

}

fileObj& localsync::readLocalDB(int type, fileObj &src){

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(db_local.c_str());

    int count = 0;
    if(db.open()){
        QSqlQuery query(db);
        if(type == 0){
            query = QString("SELECT * FROM lcl_songdirs");
        }
        else if(type == 1){
            query = QString("SELECT * FROM lcl_songs");
        }
        else if(type == 2){
            query = QString("SELECT * FROM lcl_viddirs");
        }
        else{
            query = QString("SELECT * FROM lcl_videos");
        }
        while (query.next()){
            QString QVal1 = query.value(1).toString();
            QString QVal2 = query.value(2).toString();
            QString QVal3 = query.value(3).toString();
            QString QVal4 = query.value(4).toString();

            cout << QVal1.toStdString() << QVal2.toStdString() << QVal3.toStdString() << QVal4.toStdString() << endl;

            if(QVal1.toStdString() != "-"){
                src.set(count, QVal3.toInt(), QVal4.toInt(), QVal1.toStdString().c_str(), QVal2.toStdString().c_str());
                count++;
            }
        }
        db.close();
    }
    return src;
}
void localsync::writeDBFiles(char *dbTable){
    int  pos = 0, posMax = 0, counter = 0, countRemind = 0;
    string str2;
    counter = getMaxPos(fileCount);
    posMax = counter;

    for (int m = 0; m <= (fileCount / counter); m++) {
        countRemind = 0;
        stringstream os;
        for (int i = pos; i <= posMax; i++) {
            if (i<fileCount){
                if (i != posMax && countRemind == 0) {
                    os << " INSERT INTO "<< dbTable << " (lcl_dir_path,lcl_dir_name,lcl_dir_id, lcl_dir_par,lcl_dir_type) " <<
                          "SELECT \"" << lclDir[lclFilePar[i]] << lclFiles[i] << "\" AS \"" << "lcl_dir_path" << "\", \""
                       <<  lclFiles[i] << "\" AS \"" << "lcl_dir_name" << "\", \""
                       <<  lclFileID[i] << "\" AS \"" << "lcl_dir_id" << "\", \""
                       <<  lclFilePar[i] << "\" AS \"" << "lcl_dir_par" << "\", \""
                       <<  "songs" << "\" AS \"" << "lcl_dir_type" << "\"";
                    cout << os;
                    countRemind++;
                }
                if (i != posMax && countRemind != 0 ) {
                    os << " UNION SELECT \"" <<  lclDir[lclFilePar[i]] << "/" << lclFiles[i] << "\",\""<< lclFiles[i] << "\",\"" << lclFileID[i] <<"\",\""<< lclFilePar[i]<<"\",\""<< "song" << "\"";

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
void localsync::writeDBDirs(char *dbTable){
    int  pos = 0, posMax = 0, counter = 0, countRemind = 0;
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

void localsync::writeMe(string qry){
    openLocalDB();
    if(db.open()){
        //    cout << qry << endl;
        QSqlQuery myQry(db);
        myQry.prepare(qry.c_str());
        myQry.exec();

        db.close();
    }

}
