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

readDB::readDB() {
    DBLOCATE = "-";
}

void readDB::OpenDB(){


}

fileObj& readDB::RemoteFill(fileObj &src, int type){
    QSqlDatabase db2 = QSqlDatabase::addDatabase("QSQLITE");
    db2.setDatabaseName(DBLOCATE.c_str());
    int count = 0;
    if(db2.open()){
        QSqlQuery query(db2);

        //// sync Remote
        if(type == 1){
            query = QString("SELECT * FROM artists");
        }
        else if(type == 2){
            query = QString("SELECT * FROM albums");
        }
        else if(type == 3){
            query = QString("SELECT * FROM songs");
        }
        else if(type == 4){
            query = QString("SELECT * FROM viddirs");
        }
        else if(type == 5){
            query = QString("SELECT * FROM videos");
        }

        while(query.next()){
            QString QVal1 = query.value(1).toString();
            QString QVal2 = query.value(2).toString();
            QString QVal3 = query.value(3).toString();

            if(QVal2.toInt() != 0){
                src.set(count, QVal2.toInt(), QVal3.toInt(), QVal1.toStdString().c_str());
                count++;
            }
        }
        db2.close();
    }
 //   QSqlDatabase::removeDatabase("connectReadFiles");

    return src;

}

fileObj& readDB::LocalFill(fileObj &src, int type){
    QSqlDatabase db2 = QSqlDatabase::addDatabase("QSQLITE");
    db2.setDatabaseName(DBLOCATE.c_str());
    int count = 0;
    if(db2.open()){
        QSqlQuery query(db2);

        /// sync Local
        if(type == 1){
            query = QString("SELECT * FROM lcl_songdirs");
        }
        else if(type == 2){
            query = QString("SELECT * FROM lcl_songs");
        }
        else if(type == 3){
            query = QString("SELECT * FROM lcl_viddirs");
        }
        else if(type == 4){
            query = QString("SELECT * FROM lcl_videos");
        }

        while(query.next()){
            QString QVal1 = query.value(1).toString();
            QString QVal2 = query.value(2).toString();
            QString QVal3 = query.value(3).toString();
            QString QVal4 = query.value(4).toString();

            if(QVal1.toStdString() != "-"){
                src.set(count, QVal3.toInt(), QVal4.toInt(), QVal1.toStdString().c_str(), QVal2.toStdString().c_str());
                count++;
            }
        }
        db2.close();
    }
    //    QSqlDatabase::removeDatabase("connectReadFiles");
    return src;
}

fileObj& readDB::PlaylistFill( fileObj &src, int type){
    QSqlDatabase db2 = QSqlDatabase::addDatabase("QSQLITE", "playlistDBread");
    db2.setDatabaseName(DBLOCATE.c_str());
    int count = 0;
    if(db2.open()){
        QSqlQuery query(db2);
        if(type == 1){
            query = QString("SELECT * FROM playlists");
        }
        else if(type == 2){
            query = QString("SELECT * FROM playlist_items");
        }

        while (query.next()){
            QString QVal1 = query.value(1).toString();
            QString QVal2 = query.value(2).toString();
            QString QVal3 = query.value(3).toString();
            QString QVal4 = query.value(4).toString();

            if(QVal1.toStdString() != "-"){
                src.set(count, QVal3.toInt(), QVal4.toInt(), QVal1.toStdString().c_str(), QVal2.toStdString().c_str());
                count++;
            }
        }
        db2.close();
    }
    return src;
}

fileObj& readDB:: RadioFill(fileObj &src){
    QSqlDatabase db2 = QSqlDatabase::addDatabase("QSQLITE");
    db2.setDatabaseName(DBLOCATE.c_str());
    int count = 0;
    if(db2.open()){
        QSqlQuery query(db2);
            query = QString("SELECT * FROM radio");

        while (query.next()){
            QString QVal1 = query.value(1).toString();
            QString QVal2 = query.value(2).toString();
            QString QVal3 = query.value(3).toString();
            QString QVal4 = query.value(4).toString();

            if(QVal1.toStdString() != "-"){
                src.set(count, QVal3.toInt(), QVal4.toInt(), QVal1.toStdString().c_str(), QVal2.toStdString().c_str());
                count++;
            }
        }
        db2.close();
    }
    return src;
}

readDB::~readDB(){

}
