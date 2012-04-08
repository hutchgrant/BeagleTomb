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


#include "preferences.h"

preferences::preferences(){
    
    USER = "mediatomb";
    PASS = "mediatomb";
    SERVER = "192.168.1.113";
    TABLE = "mediatomb";
    PORT = "49154";
    string DB = "/.beagletomb/BTmedia.db";
    string PL = "/.beagletomb/playlist/";
    DBlocation = getenv("HOME") + DB;
    PLAYLISTDIR = getenv("HOME") + PL;
}
preferences::preferences(const preferences& src){
    USER = src.USER;
    PASS = src.PASS;
    SERVER = src.SERVER;
    PORT = src.PORT;
    TABLE = src.TABLE;
    DBlocation = src.DBlocation;
    PLAYLISTDIR = src.PLAYLISTDIR;
}

/// construct with default sql location
preferences::preferences(string DFLTSQL)
{
    DBlocation = DFLTSQL;
}


/// get initial db file from text cache
bool preferences::initDB(){
    bool found = false;
    char PrefIn[100];
    FILE* fp;
    string tempcache = TEMPCACHE;
    string Cache = getenv("HOME") + tempcache;
    fp = fopen(Cache.c_str(), "r");   /// open cached db location

    if(fp != NULL){
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
        readDB();   // read that db
        fclose(fp);
        return true;
    }
    else{
        fclose(fp);
        return false;
    }
}

/// set initial db file in text cache
void preferences::setInitDB(){

    ofstream myfile;
    string tempcache = TEMPCACHE;
    string cache = getenv("HOME") + tempcache;
    myfile.open (cache.c_str());
    myfile << DBlocation.c_str();
    myfile.close();

}



/// remove Preference database
void preferences::deletePrefDB() {
    string finalRMPrefqry =  "drop table pref if exists";
    if(QFile::exists(DBlocation.c_str())){
        writeMe(finalRMPrefqry);
    }
}

/// create Preference database
void preferences::createPrefDB() {
    OpenDB();
    string finalQry;
        finalQry = "create table pref(key INTEGER PRIMARY KEY,usr TEXT,PASS TEXT,SERVER TEXT,PRT TEXT,SQLTABLE TEXT,SQL TEXT,PLAYLISTDIR TEXT)";
       writeMe(finalQry);
}


void preferences::OpenDB(){
    db2 = QSqlDatabase::addDatabase("QSQLITE");
    db2.setDatabaseName(DBlocation.c_str());
}

/// read preference table from sql
void preferences::readDB(){
    OpenDB();
    int count = 0;
    if(QFile::exists(DBlocation.c_str())){
        if(db2.open()){
            QSqlQuery query(db2);

            query = QString("SELECT * FROM pref");

            while (query.next()){
                QString QVal1 = query.value(1).toString();
                QString QVal2 = query.value(2).toString();
                QString QVal3 = query.value(3).toString();
                QString QVal4 = query.value(4).toString();
                QString QVal5 = query.value(5).toString();
                QString QVal6 = query.value(6).toString();
                QString QVal7 = query.value(7).toString();


                setUser(QVal1.toStdString());
                setPass(QVal2.toStdString());
                setServ(QVal3.toStdString());
                setPort(QVal4.toStdString());
                setTable(QVal5.toStdString());
                setSQL(QVal6.toStdString());
                setPlaylistDir(QVal7.toStdString());
            }
            db2.close();
        }
    }
}

/// write to preference table sql
void preferences::writeDB(){
    OpenDB();
    string str2;
    stringstream os;
    os << "INSERT INTO pref (usr, PASS, SERVER, PRT, SQLTABLE, SQL, PLAYLISTDIR) VALUES ('"
       << USER << "','" << PASS << "','" << SERVER << "','" << PORT  << "','" << TABLE  << "','" << DBlocation << "','" << PLAYLISTDIR << "')";

    str2 = os.str();
    //    cout << str2 << endl;
    writeMe(str2);
}

//// write to output file temp qry
void preferences::writeMe(string qry){

    if(db2.open()){
        QSqlQuery myQry(db2);
        myQry.prepare(qry.c_str());
        myQry.exec();
        db2.close();
    }
}

void preferences::createCache(){
    string main = "/.beagletomb";
    string cache = "/cache";
    string playlist = "/playlist";
    string u_home = getenv("HOME");
    string finMain = u_home + main;
    string finCache = u_home + main + cache;
    string finPL = u_home + main + playlist;
    QString q_main = finMain.c_str();
    QString q_cache = finCache.c_str();
    QString q_playlist = finPL.c_str();
    QDir(q_main).mkdir(q_main);
    QDir(q_main).mkdir(q_cache);
    QDir(q_main).mkdir(q_playlist);
}

preferences& preferences::operator=(const preferences& src){

    if(this != &src)
    {
        setUser(src.USER);
        setPass(src.PASS);
        setServ(src.SERVER);
        setPort(src.PORT);
        setTable(src.TABLE);
        setSQL(src.DBlocation);
        setPlaylistDir(src.PLAYLISTDIR);
    }
    
    return *this;
}
