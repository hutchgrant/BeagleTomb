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
    SERVER = "192.168.1.116";
    TABLE = "mediatomb";
    PORT = "49154";
    DBlocation = "BTmedia.db";
    PLAYLISTDIR = "/BeagleTomb/playlist/";
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


/*
 * Open any filename
 *
 */


/// get initial db file from text cache
bool preferences::initDB(){
    bool found = false;
    char PrefIn[100];
    FILE* fp;
    fp = fopen("dbcache.txt", "r");   /// open cached db location

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
    myfile.open ("dbcache.txt");
    myfile << DBlocation.c_str();
    myfile.close();

}

/// remove database
void preferences::deleteDB(const char *dbLocation) {
    char FinalLink[150];
    sprintf(FinalLink, "rm %s ", dbLocation);
    system(FinalLink);
}

/// create database
void preferences::createDB(const char *dbLocation, const char *createSQL) {
    char FinalLink[150];
    sprintf(FinalLink, "sqlite3 %s < %s ", dbLocation, createSQL );
    system(FinalLink);
}

/// read preference table from sql
void preferences::readDB(){

    Database *db;
    db = new Database(DBlocation.c_str());
    vector<vector<string> > result = db->query("SELECT * FROM pref;");
    for(vector<vector<string> >::iterator it = result.begin(); it < result.end() ; ++it)
    {
        vector<string> row = *it;
        string str = "", str2, str3, str4, str5, str6, str7;
        str = row.at(1);
        str2 = row.at(2);
        str3 = row.at(3);
        str4 = row.at(4);
        str5 = row.at(5);
        str6 = row.at(6);
        str7 = row.at(7);

        setUser(str);
        setPass(str2);
        setServ(str3);
        setPort(str4);
        setTable(str5);
        setSQL(str6);
        setPlaylistDir(str7);
        cout << "read playlist dir " << getPlaylistDir() << endl;
    }
}


/// write to preference table sql
void preferences::writeDB(){
    
    string str2;
    stringstream os;
    os << " INSERT INTO pref (usr, PASS, SERVER, PRT, SQLTABLE, SQL, PLAYLISTDIR) " <<
          "SELECT \"" << USER << "\" AS \"" << "usr" << "\", \""

       <<  PASS << "\" AS \"" << "PASS" << "\", \""
       << SERVER << "\" AS \"" << "SERVER" << "\", \""
       <<  PORT << "\" AS \"" << "PRT" << "\", \""
       <<  TABLE << "\" AS \"" << "SQLTABLE" << "\", \""
       <<  DBlocation << "\" AS \"" << "SQL" << "\", \""
       << PLAYLISTDIR << "\" AS \"" << "PLAYLISTDIR" << "\""
       << ";";
    // cout << os;
    str2 = os.str();
    writeMe(str2);
    sendToShell();
}

//// write to output file temp qry
void preferences::writeMe(string qry){

    ofstream outputFile;
    outputFile.open(TEMPPREF);

    outputFile << qry;

    outputFile.close();
}

/// pipe temp output fil to sqlite
void preferences::sendToShell() {
    char FinalLink[150];
    sprintf(FinalLink, "sqlite3 %s < %s", DBlocation.c_str(), TEMPPREF);
    system(FinalLink);
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
