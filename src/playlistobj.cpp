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

#include "playlistobj.h"
playlistobj::playlistobj()
{
    initPlaylist();
    pl_mode = 0;
    db_location = "-";
    playlistCount = 0;
}

playlistobj::~playlistobj(){
}

/*
  * write sqlite anything
  */
void playlistobj::writeMe(string sQry){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(db_location.c_str());
    if(db.open()){
        QSqlQuery finQry(db);
        finQry.prepare(sQry.c_str());
        finQry.exec();
        db.close();
    }
    db.removeDatabase(db_location.c_str());
}
/*
  * Initialize and allocate playlist
  */
void playlistobj::initPlaylist(){
    playlist_obj.initFile(100);
    pl_obj_count = 0;
   playlistCount = 0;
    playlistName = "newplaylist";
}



/*
  * create new playlist
  */
void playlistobj::AddNew(string name){
    initPlaylist();
    string newQry[2];
    newQry[0] = "create table playlists (key INTEGER PRIMARY KEY,lcl_dir_name TEXT,lcl_dir_path TEXT,lcl_dir_id integer,lcl_dir_par integer,lcl_dir_type TEXT)";
    newQry[1] = "create table playlist_items (key INTEGER PRIMARY KEY,lcl_dir_name TEXT,lcl_dir_path TEXT,lcl_dir_id integer,lcl_dir_par integer,lcl_dir_type TEXT)";
    for(int i =0; i<2; i++){
        writeMe(newQry[i]);
    }
    playlistCount++;  // number of playlists
    playlistName = name;
}

/*
  * Fill new playlist
  */
void playlistobj::writeNew(int writemode){

    char *qryState;
     if(writemode == 1){

         for(int i =0; i< playlistCount; i++){
            qryState = new char[strlen(playlistName.c_str())+250];
            sprintf(qryState, "INSERT INTO playlists (lcl_dir_name, lcl_dir_path, lcl_dir_id, lcl_dir_par, lcl_dir_type) VALUES ('%s', '%s', '%d', '%d', '%s')",
            playlistName.c_str(), "-", playlistCount, 0, 0, "playlist");
         }
     }
     else if(writemode == 2){

         for(int i =0; i< pl_obj_count; i++){
            qryState = new char[strlen(playlist_obj.getName(i))+strlen(playlist_obj.getPath(i))+250];
            sprintf(qryState, "INSERT INTO playlist_items (lcl_dir_name, lcl_dir_path, lcl_dir_id, lcl_dir_par, lcl_dir_type) VALUES ('%s', '%s', '%d', '%d', '%s')",
            playlist_obj.getName(i), playlist_obj.getPath(i), playlist_obj.getID(i), playlistCount, "song");
         }
     }

     writeMe(string(qryState));
     delete [] qryState;
    }

/*
  * Add to existing playlist
  */
void playlistobj::AddTo(int id, int par, string name, string path, fileObj &src){
    setPlObj(src);
    playlist_obj.setInit(100);
    /// Add to our playlist object
    playlist_obj.set(pl_obj_count, id, par, name.c_str(), path.c_str());
    pl_obj_count++;
    if(pl_obj_count >= playlist_obj.getInit()){
        playlist_obj.REinitFile(playlist_obj.getInit(), 100);
    }
}

/*
  * Move a playlist item
  */
void playlistobj::Move(int selected, int direction){

    fileObj tempPl;
    int moving =0, moveTo = 0;
    moving = playlist_obj.getID(selected);

    if(direction == 0 && selected-1 > 0 && selected-1 < playlist_obj.getSize()){ // move down
        moveTo = playlist_obj.getID(selected--);
        tempPl.set(0, playlist_obj.getID(selected--), playlist_obj.getPar(selected--), playlist_obj.getName(selected--), playlist_obj.getPath(selected--));
        tempPl.set(1, playlist_obj.getID(selected--), playlist_obj.getPar(selected--), playlist_obj.getName(selected--), playlist_obj.getPath(selected--));

        playlist_obj.set(selected--, tempPl.getID(0), tempPl.getPar(0), tempPl.getName(0), tempPl.getPath(0));
         playlist_obj.set(selected++, tempPl.getID(1), tempPl.getPar(1), tempPl.getName(1), tempPl.getPath(1));
    }
    else if(direction == 1 && selected+1 > 0 && selected+1 < playlist_obj.getSize()){  // move up
        moveTo = playlist_obj.getID(selected++);
        tempPl.set(0, playlist_obj.getID(selected++), playlist_obj.getPar(selected++), playlist_obj.getName(selected++), playlist_obj.getPath(selected++));
        playlist_obj.set(selected, tempPl.getID(0), tempPl.getPar(0), tempPl.getName(0), tempPl.getPath(0));
        playlist_obj.set(selected++, tempPl.getID(1), tempPl.getPar(1), tempPl.getName(1), tempPl.getPath(1));

    }
}

/*
  * Remove the entire playlist or an item
  */
void playlistobj::RemoveFrom(int selected){
    int removalID = 0;
/*
    removalID = playlist_obj.getID(selected);

    QSqlQuery rem;
    // remove playlist
    if(type == 0){
        if(db.open()){

            rem = ""
        }
    }
    else{

    } */
}


/*
  * remove playlist entry from database
  */
void playlistobj::removeFromDB(int item){

}


playlistobj::playlistobj(const playlistobj& src){
    playlist_obj = src.playlist_obj;
    pl_obj_count = src.pl_obj_count;
    playlistName = src.playlistName;
}
playlistobj& playlistobj::operator=(const playlistobj& src)
{
    if(this != &src)
    {
        playlist_obj = src.playlist_obj;
        pl_obj_count = src.pl_obj_count;
        playlistName = src.playlistName;
    }
    return *this;
}

