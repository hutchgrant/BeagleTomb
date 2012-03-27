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
}

void readDB::OpenDB(){
    db2 = QSqlDatabase::addDatabase("QSQLITE");
    db2.setDatabaseName(DBlocation2);

}

fileObj& readDB::SongFill(fileObj& Song){
    int count = 0;
     if(db2.open()){
       QSqlQuery query(db2);

     query = QString("SELECT * FROM songs");

     while (query.next()){
         QString QVal1 = query.value(1).toString();
         QString QVal2 = query.value(2).toString();
         QString QVal3 = query.value(3).toString();

         if(QVal2.toInt() != 0){
             Song.set(count, QVal2.toInt(), QVal3.toInt(), QVal1.toStdString().c_str());
             count++;
         }
     }
     db2.close();
    }
    return Song;
}

fileObj& readDB::AlbumFill(fileObj& Album){

    int count = 0;
     if(db2.open()){
    QSqlQuery query(db2);
            query = QString("SELECT * FROM albums");

            while (query.next()){
                QString QVal1 = query.value(1).toString();
                QString QVal2 = query.value(2).toString();
                QString QVal3 = query.value(3).toString();

                if(QVal2.toInt() != 0){
                    Album.set(count, QVal2.toInt(), QVal3.toInt(), QVal1.toStdString().c_str());
                    count++;
                }
            }
             db2.close();
    }
    return Album;
}

fileObj& readDB::ArtistFill(fileObj& Artist){
    OpenDB();
    int count = 0;
    if(db2.open()){
   QSqlQuery query(db2);
              query = QString("SELECT * FROM artists");

            while (query.next()){
                QString QVal1 = query.value(1).toString();
                QString QVal2 = query.value(2).toString();
                QString QVal3 = query.value(3).toString();

                if(QVal2.toInt() != 0){
                    Artist.set(count, QVal2.toInt(), QVal3.toInt(), QVal1.toStdString().c_str());
                    count++;
                }
            }
             db2.close();
    }
    return Artist;
}
fileObj& readDB::VidDirFill( fileObj& VidDir){

    int count = 0;
    if(db2.open()){
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
                    VidDir.set(count, QVal2.toInt(), QVal3.toInt(), QVal1.toStdString().c_str());
                    count++;
                }
            }
             db2.close();
    }
    return VidDir;
}
fileObj& readDB::VideoFill( fileObj& Video){

    int count = 0;
    if(db2.open()){
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
                    Video.set(count, QVal2.toInt(), QVal3.toInt(), QVal1.toStdString().c_str());
                    count++;
                }
            }
             db2.close();
    }
    return Video;
}

radioObj readDB::RadioFill(int *radSize){

    int count = 0;
    if(db2.open()){
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

void readDB::display( fileObj&Artist, fileObj& Song,fileObj& Album ){
    int choice = 0;
    bool Exit = 0;
    while(!Exit){
        cout << endl;
	cout << "Which do you want to display?" << endl;
	cout << "1)Artists 2) Albums 3)Songs 4) exit" << endl;
	cin >> choice;

	if(choice == 1){
            Artist.display();
            cout << "total artists: " << Artist.getSize();
	}
	if(choice == 2){
            Album.display();
            cout << "Total Albums: " << Album.getSize();
	}
	if(choice == 3){
            Song.display();
            cout << "Total Songs: " << Song.getSize();
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
