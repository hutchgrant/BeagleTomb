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
    setFileLocation("/.BeagleTomb/playlist/");
    playlistOpen = false;
    playlistCount = 0;
    pl_obj_count = 0;
}

playlistobj::~playlistobj(){

    delete [] playlist_obj;

}

void playlistobj::initPL(){
    /// re initialize playlist object

    playlist_obj = new songObj[MAXPLAYSIZE];
    for(int i = 0; i<= MAXPLAYSIZE; i++){
        playlist_obj[i].set("-",0,0);
    }
}



void playlistobj::writePLfile(){
    ofstream myfile;
    char *mystring;

    mystring = NULL;
    myfile.open(fullLocation.c_str());
    for(int i=0; i<=pl_obj_count; i++){
        mystring = new char[strlen(playlist_obj[i].getFile())+1];
        strcpy(mystring, playlist_obj[i].getFile());
        //// check each string for blanks, replace with underscores
        replace(&mystring[0], &mystring[strlen(mystring)], ' ', '_');

        myfile << mystring << " : "<< playlist_obj[i].getFileID()<< endl;

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

    songObj *temp_pl;   // temp playlist object
    int tempCount = 0;  // count the temp items

    /// init temp playlist object
    temp_pl = new songObj[MAXPLAYSIZE];
    for(int i = 0; i<= MAXPLAYSIZE; i++){
        temp_pl[i].set("-",0,0);
    }
    /// get everything before the position we're removing
    for(int i = 0; i< pos; i++){
        temp_pl[tempCount].setFile(playlist_obj[i].getFile());
        temp_pl[tempCount].setFileID(playlist_obj[i].getFileID());
        tempCount++;
    }
    /// get everything after the position we're removing;
    for(int i = pos+1; i> pos && i<=pl_obj_count; i++){
        temp_pl[tempCount].setFile(playlist_obj[i].getFile());
        temp_pl[tempCount].setFileID(playlist_obj[i].getFileID());
        tempCount++;
    }
    pl_obj_count--;
    playlistCount--;
    initPL();
    /// refill original playlist object with altered temp object
    for(int i=0; i<= tempCount; i++){
        playlist_obj[i] = temp_pl[i];
    }
    /// clear memory
    delete [] temp_pl;
}


void playlistobj::AddTo(int selected, char *FinSong)
{

    /// Add to our playlist object
    playlist_obj[pl_obj_count].setFile(FinSong);
    playlist_obj[pl_obj_count].setFileID(selected);
    pl_obj_count++;
}

/*
  * refill playlist list with playlist object
  */
QStringList playlistobj::RefillPlaylist(){

    playlistCount = 0;
    QStringList curSong;
// retrieve track listing and store temporairly
    for(int i = 0; i< pl_obj_count; i++){
        curSong << playlist_obj[i].getFile();
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
     //           fclose(fp);
        return 1;
}


void playlistobj::Move(int mode, int selected){
    int selection2 = 0; // hold our temporary mock selection
    songObj temp_pl;   // temp playlist object
    songObj temp_pl2;   // temp playlist object
    int plCount = 0;   // count for temp pl item
    if(mode == 1){
        selection2 = selected + 1;
    }
    else if(mode == 2){
        selection2 = selected -1;
    }

    for(int i=0; i<= pl_obj_count; i++){
        if(i == selection2){
            temp_pl = playlist_obj[i];
        }
        else if(i == selected){
            temp_pl2 = playlist_obj[i];
        }
    }
    /// Now reverse those values
    playlist_obj[selection2] = temp_pl2;
    playlist_obj[selected] = temp_pl;


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

///    QStringList plFolder = myDir.entryList("*.pl");
    return QPLFolder;

}

