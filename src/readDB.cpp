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


#include "readDB.h"

readDB::readDB(const char *dbLocation) {
    DBlocation2 = new char[strlen(dbLocation) + 1];
    strcpy(DBlocation2, dbLocation);

    Artist = new songObj[MAX];
    for(int i = 0; i<= MAX; i++){
        Artist[i].set("-",0,0);
    }

    Album = new songObj[MAX];
    for(int i = 0; i<= MAX; i++){
        Album[i].set("-",0,0);
    }
    Song = new songObj[MAX];
    for(int i = 0; i<= MAX; i++){
        Song[i].set("-", 0, 0);
    }
    VidDir = new songObj[MAX];
    for(int i = 0; i<= MAX; i++){
        VidDir[i].set("-", 0, 0);
    }
    Video = new songObj[MAX];
    for(int i = 0; i<= MAX; i++){
        Video[i].set("-", 0, 0);
    }
}

QSqlDatabase readDB::OpenDB(){
   QSqlDatabase db2 = QSqlDatabase::addDatabase("QSQLITE");
   cout << DBlocation2 << endl;
   db2.setDatabaseName(DBlocation2);

   if(!db2.open()){
       cout << "error connecting with database" << endl;
        exit(1);
   }
   return db2;
}

songObj* readDB::SongFill(int *songSize){
    QSqlDatabase db2 = OpenDB();
    int count = 0;
    if(!db2.open()){
        cout << "couldn't connect to database";
    }
    else{
    QSqlQuery query(db2);

     query = QString("SELECT * FROM songs");

     while (query.next()){
         QString QVal1 = query.value(1).toString();
         QString QVal2 = query.value(2).toString();
         QString QVal3 = query.value(3).toString();

         if(QVal2.toInt() != 0){
             string QstrConvert = QVal1.toStdString();
             char *QVal1Convert;
             QVal1Convert = new char[QstrConvert.length() + 1];
             strcpy(QVal1Convert, QstrConvert.c_str());
             Song[count].set(QVal1Convert, QVal2.toInt(), QVal3.toInt());
             count++;
         }
     }
     *songSize = count;
     db2.close();
    }
    return Song;
}

songObj* readDB::AlbumFill(int *albSize){

    int count = 0;
    QSqlDatabase db2 = OpenDB();
    if(!db2.open()){
        cout << "couldn't connect to database";
    }
    else{
    QSqlQuery query(db2);
            query = QString("SELECT * FROM albums");

            while (query.next()){
                QString QVal1 = query.value(1).toString();
                QString QVal2 = query.value(2).toString();
                QString QVal3 = query.value(3).toString();

                if(QVal2.toInt() != 0){
                    string QstrConvert = QVal1.toStdString();
                    char *QVal1Convert;
                    QVal1Convert = new char[QstrConvert.length() + 1];
                    strcpy(QVal1Convert, QstrConvert.c_str());
                    Album[count].set(QVal1Convert, QVal2.toInt(), QVal3.toInt());
                    count++;
                }
            }
            *albSize = count;
             db2.close();
    }
    return Album;
}

songObj* readDB::ArtistFill( int *artSize){

    int count = 0;
    QSqlDatabase db2 = OpenDB();
    if(!db2.open()){
        cout << "couldn't connect to database";
    }
    else{
    QSqlQuery query(db2);
              query = QString("SELECT * FROM artists");

            while (query.next()){
                QString QVal1 = query.value(1).toString();
                QString QVal2 = query.value(2).toString();
                QString QVal3 = query.value(3).toString();

                if(QVal2.toInt() != 0){
                    string QstrConvert = QVal1.toStdString();
                    char *QVal1Convert;
                    QVal1Convert = new char[QstrConvert.length() + 1];
                    strcpy(QVal1Convert, QstrConvert.c_str());
                    Artist[count].set(QVal1Convert, QVal2.toInt(), QVal3.toInt());
                    count++;
                }
            }
            *artSize = count;
             db2.close();
    }
    return Artist;
}
songObj* readDB::VidDirFill( int *vidDirSize){

    int count = 0;
   QSqlDatabase db2 = OpenDB();
    if(!db2.open()){
        cout << "couldn't connect to database";
    }
    else{
    QSqlQuery query(db2);
              query = QString("SELECT * FROM viddirs");

            while (query.next()){
                QString QVal1 = query.value(1).toString();
                QString QVal2 = query.value(2).toString();
                QString QVal3 = query.value(3).toString();

                if(QVal2.toInt() != 0){
                    string QstrConvert = QVal1.toStdString();
                    char *QVal1Convert;
                    QVal1Convert = new char[QstrConvert.length() + 1];
                    strcpy(QVal1Convert, QstrConvert.c_str());
                    VidDir[count].set(QVal1Convert, QVal2.toInt(), QVal3.toInt());
                    count++;
                }
            }
            *vidDirSize = count;
             db2.close();
    }
    return VidDir;
}
songObj* readDB::VideoFill( int *vidSize){

    int count = 0;
    QSqlDatabase db2 = OpenDB();
    if(!db2.open()){
        cout << "couldn't connect to database";
    }
    else{
    QSqlQuery query(db2);
             query = QString("SELECT * FROM videos");

            while (query.next()){
                QString QVal1 = query.value(1).toString();
                QString QVal2 = query.value(2).toString();
                QString QVal3 = query.value(3).toString();

                if(QVal2.toInt() != 0){
                    string QstrConvert = QVal1.toStdString();
                    char *QVal1Convert;
                    QVal1Convert = new char[QstrConvert.length() + 1];
                    strcpy(QVal1Convert, QstrConvert.c_str());
                    Video[count].set(QVal1Convert, QVal2.toInt(), QVal3.toInt());
                    count++;
                }
            }
            *vidSize = count;
             db2.close();
    }
    return Video;
}

radioObj readDB::RadioFill(int *radSize){

    int count = 0;
    QSqlDatabase db2 = OpenDB();
    if(!db2.open()){
        cout << "couldn't connect to database";
    }
    else{
    QSqlQuery query(db2);
              query = QString("SELECT * FROM radio");

            while (query.next()){
                QString QVal1 = query.value(1).toString();
                QString QVal2 = query.value(2).toString();


                if(QVal1.toStdString() != "" && QVal1.toStdString() != "-"){
                    string QstrConvert = QVal1.toStdString();
                    char *QVal1Convert;
                    QVal1Convert = new char[QstrConvert.length() + 1];
                    strcpy(QVal1Convert, QstrConvert.c_str());

                    string QstrConvert2 = QVal2.toStdString();
                    char *QVal2Convert;
                    QVal2Convert = new char[QstrConvert2.length() + 1];
                    strcpy(QVal2Convert, QstrConvert2.c_str());
                    play_list.Add(QVal1Convert, QVal2Convert);
                    count++;
                }
             }
        *radSize = count;
         db2.close();
    }
    return play_list;


}

void readDB::display(int artSize, int albSize, int songSize){
    int choice = 0;
    bool Exit = 0;
    while(!Exit){
        cout << endl;
	cout << "Which do you want to display?" << endl;
	cout << "1)Artists 2) Albums 3)Songs 4) exit" << endl;
	cin >> choice;

	if(choice == 1){
            for(int i = 0; i<=artSize; i++){
                cout << Artist[i];
            }
            cout << "total artists: " << artSize;
	}
	if(choice == 2){
            for(int i = 0; i<=albSize; i++){
                cout << Album[i];
            }
            cout << "Total Albums: " << albSize;
	}
	if(choice == 3){
            for(int i = 0; i<=songSize; i++){
                cout << Song[i];
            }
            cout << "Total Songs: " << songSize;
	}
	if(choice == 4){
            Exit = 1;
	}
    }
}
readDB::~readDB() {
    // TODO Auto-generated destructor stub
    delete [] DBlocation2;
}
