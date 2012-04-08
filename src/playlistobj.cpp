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
#define MAXPLAYSIZE 1000
playlistobj::playlistobj()
{
    initPL();
    /// set temp defaults later sync from db
    setFileName("newplaylist.pl");
    setFileLocation("/.beagletomb/playlist/");
    playlistOpen = false;
    playlistCount = 0;
    pl_obj_count = 0;
}

playlistobj::~playlistobj(){


}

void playlistobj::initPL(){
    /// re initialize playlist object
    playlist_obj.initFile(100);
}



void playlistobj::writePLfile(){
    ofstream myfile;
    char *mystring;

    mystring = NULL;
    myfile.open(fullLocation.c_str());
    for(int i=0; i<=pl_obj_count; i++){
        mystring = new char[strlen(playlist_obj.getPath(i))+1];
        strcpy(mystring, playlist_obj.getPath(i));
        //// check each string for blanks, replace with underscores
        replace(&mystring[0], &mystring[strlen(mystring)], ' ', '_');

        myfile << mystring << " : "<< playlist_obj.getID(i)<< endl;

        delete [] mystring;
     }
    myfile.close();

}

void playlistobj::readPLfile(string location){
    FILE* fp = NULL;
    initPL();
    char *Track;
    int TrackID;
    int TrackCount=0;
    int myExit = 0;
    fullLocation = location;
    fp = fopen(fullLocation.c_str(), "r");
    rewind(fp);

    while(!feof(fp) && !myExit){
    Track = new char[100];
        fscanf(fp, "%s : %d", Track, &TrackID);
        if(strncmp(Track, "-",1)== 0){

           myExit = 1;
           pl_obj_count = TrackCount;
         }
        else{
         replace(&Track[0], &Track[strlen(Track)], '_', ' ');
        setTrackName(TrackCount, Track);
        setTrackID(TrackID, TrackCount);
        TrackCount++;
        }
        delete [] Track;
    }
    close();

}

/*
  * remove playlist item from playlist object at integer pos
  */
void playlistobj::RemoveFrom(int pos){

    fileObj temp_pl;   // temp playlist object
    int tempCount = 0;  // count the temp items

    /// get everything before the position we're removing
    for(int i = 0; i< pos; i++){
        temp_pl.setName(tempCount, playlist_obj.getName(i));
        temp_pl.setPath(tempCount, playlist_obj.getPath(i));
        temp_pl.setID(tempCount, playlist_obj.getID(i));
        temp_pl.setPar(tempCount, playlist_obj.getPar(i));
        tempCount++;
    }
    /// get everything after the position we're removing;
    for(int i = pos+1; i> pos && i<=pl_obj_count; i++){
        temp_pl.setName(tempCount, playlist_obj.getName(i));
        temp_pl.setPath(tempCount, playlist_obj.getPath(i));
        temp_pl.setID(tempCount, playlist_obj.getID(i));
        temp_pl.setPar(tempCount, playlist_obj.getPar(i));
        tempCount++;
    }
    pl_obj_count--;
    playlistCount--;
    initPL();
    /// refill original playlist object with altered temp object
    playlist_obj = temp_pl;
}


void playlistobj::AddTo(int selected, char *FinSong)
{

    /// Add to our playlist object
    playlist_obj.set(pl_obj_count, selected, 0, FinSong);
    pl_obj_count++;
    if(pl_obj_count >= playlist_obj.getInit()){
        playlist_obj.REinitFile(playlist_obj.getInit(), 100);
    }
}

/*
  * refill playlist list with playlist object
  */
QStringList playlistobj::RefillPlaylist(){

    playlistCount = 0;
    QStringList curSong;
// retrieve track listing and store temporairly
    for(int i = 0; i< pl_obj_count; i++){
        curSong << playlist_obj.getName(i);
        playlistCount++;
    }

    return curSong;
}
playlistobj::playlistobj(const playlistobj& src){
    fileName = src.fileName;
    fileLocation = src.fileLocation;
    fullLocation = src.fullLocation;
    playlist_obj = src.playlist_obj;
    pl_obj_count = src.pl_obj_count;
    playlistCount = src.playlistCount;
    playlistOpen = src.playlistOpen;
    pl_folder = src.pl_folder;
    folder_count = src.folder_count;
    playlistOpen = src.playlistOpen;
}
playlistobj& playlistobj::operator=(const playlistobj& src)
{
    if(this != &src)
    {
        fileName = src.fileName;
        fileLocation = src.fileLocation;
        fullLocation = src.fullLocation;
        playlist_obj = src.playlist_obj;
        pl_obj_count = src.pl_obj_count;
        playlistCount = src.playlistCount;
        playlistOpen = src.playlistOpen;
        pl_folder = src.pl_folder;
        folder_count = src.folder_count;
        playlistOpen = src.playlistOpen;
    }
    return *this;
}
int playlistobj::close(){
        return 1;
}


void playlistobj::Move(int mode, int selected){
    int selection2 = 0; // hold our temporary mock selection
    int plCount = 0;   // count for temp pl item
    if(mode == 1){   // if moving up
        selection2 = selected + 1;
    }
    else if(mode == 2){  // if moving down
        selection2 = selected -1;
    }


}

QStringList playlistobj::listDirectories(const char *location){
    QStringList QPLFolder;
    QString qFold = QString(location);
    QDir myDir(qFold);
    int itemCount = 0;
       folder_count = 0;

    foreach(QFileInfo aItem, myDir.entryInfoList()){
        itemCount++;
        if(itemCount>2){
            QPLFolder << aItem.fileName();
        }
    }
    pl_folder = new string[QPLFolder.size()];
    itemCount = 0;
    foreach(QFileInfo aItem, myDir.entryInfoList()){
        itemCount++;
        if(itemCount>2){
         pl_folder[folder_count] = aItem.fileName().toStdString();
         folder_count++;
        }
    }
    return QPLFolder;

}

