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

#include "browse.h"
#include "ui_browse.h"

browse::browse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::browse)
{
    ui->setupUi(this);
    Sync(1);
    MenuMode = 0;
    remoteMode = 0;
    songCount = 0;
    vidCount = 0;
}

browse::~browse()
{
    delete ui;
}
void browse::Sync(int type){
    // reinit objects

    if(type == 2 || type == 3){    /// import new entries into local db for each folder and file
        Artist.initFile(100); Song.initFile(100); VidDir.initFile(100); Video.initFile(100);
        QDir usrDir = QString(getenv("HOME"));
        usrDir = QFileDialog::getExistingDirectory(this, tr("Import a directory"), QDir::currentPath());  // get folder import directory
        if(type == 2){   /// import audio
           lclSync.Sync(usrDir, 0);
        }
        else if(type == 3){  /// import video
            lclSync.Sync(usrDir, 1);
        }
        remoteMode = 0;
        dbCon.readLocal(Artist, Song, VidDir, Video);
    }
    else if(type == 1){          /// read from local database and sync to local objects
        Artist.initFile(100); Song.initFile(100); VidDir.initFile(100); Video.initFile(100);
        remoteMode = 0;
        getPref();
        dbCon.readLocal(Artist, Song, VidDir, Video);
    }
    else if(type == 4){          /// read from local database and sync to remote objects
        RemArtist.initFile(100); RemAlbum.initFile(100); RemSong.initFile(100); RemVidDir.initFile(100); RemVideo.initFile(100);
        remoteMode = 1;  // turn on remote
        dbCon.readRemote(RemArtist, RemAlbum, RemSong, RemVidDir, RemVideo);
    }
    else if(type == 5){         /// sync remote files write to database then read from local database and sync to remote objects
        remoteMode = 1;
        getPref();


        fileObj newArtist, newAlbum, newSong, newVidDir, newVideo;
        newArtist.initFile(100); newAlbum.initFile(100); newSong.initFile(100); newVidDir.initFile(100); newVideo.initFile(100);

        remotesync RC;
        RC.setPref(pref);
        RC.Fill(newArtist, newAlbum, newSong, newVidDir, newVideo);
        dbCon.writeAllRemote(newArtist, newAlbum, newSong, newVidDir, newVideo);
        cout << "files written to database" << endl;
        RemArtist.initFile(100); RemAlbum.initFile(100); RemSong.initFile(100); RemVidDir.initFile(100); RemVideo.initFile(100);
        dbCon.readRemote(RemArtist, RemAlbum, RemSong, RemVidDir, RemVideo);
        cout << "remote files read" << endl;
    }
        updateMenu();
}

/*
  * Get Preference - initialize from database
  */
void browse::getPref(){
    dbCon.readPref(pref);
}

/*
  * Toggle Remote / Local Mode
  */
void browse::ToggleMode(){

    if(remoteMode == 0){

        remoteMode = 1;
        Sync(4);   /// Sync remote objects from sqlite
    }
    else if(remoteMode == 1){
        remoteMode = 0;
        Sync(1);    /// Sync local objects from sqlite
    }
     emit prefChanged(pref, remoteMode);

}

void browse::updateMenu(){

    QStringList curMenu;
    m_Model = new QStringListModel(this);
    if(MenuMode == 0 && remoteMode == 0)  // artists + local
    {
        for(int i=0; i <= Artist.getSize(); i++){
            curMenu << Artist.getName(i);
        }
    }
    else if(MenuMode == 1 && remoteMode == 0) // vid Dirs + local
    {
        for(int i=0; i <= VidDir.getSize(); i++){
            curMenu << VidDir.getName(i);
        }
    }
    else if(MenuMode == 0 && remoteMode == 1){ // Artists + remote
        for(int i = 0; i <= RemArtist.getSize(); i++){
            curMenu << RemArtist.getName(i);
        }
    }
    else if(MenuMode == 1 && remoteMode == 1){ // Albums + remote
        for(int i = 0; i <= RemAlbum.getSize(); i++){
            curMenu << RemAlbum.getName(i);
        }
    }
    else if(MenuMode == 2 && remoteMode == 1){ // VidDirs + remote
        for(int i = 0; i <= RemVidDir.getSize(); i++){
            curMenu << RemVidDir.getName(i);
        }
    }
    m_Model->setStringList(curMenu);
    ui->MenuList->setModel(m_Model);
}

void browse::updateTitle(int selected){
    int selID = 0;
    QStringList curSong;
    t_Model = new QStringListModel(this);
    songCount = 0;
    vidCount = 0;
        if(MenuMode == 0 && remoteMode == 0){    /// set Song + local
            selID = Artist.getID(selected);
            curSongID = new int[Song.getSize()];
            for(int i = 0; i<Song.getSize(); i++){
                if(Song.getPar(i) == selID){
                    curSong << Song.getName(i);
                    curSongID[songCount] = Song.getID(i);
                    songCount++;
                }
            }
           emit curListChanged(Song, curSongID);
        }
        else if(MenuMode == 1 && remoteMode == 0){    ///  set Video + local
            selID = VidDir.getID(selected);
            curVidID = new int[Video.getSize()];
            for(int i = 0; i<Video.getSize(); i++){
                if(Video.getPar(i) == selID){
                    curSong << Video.getName(i);
                    curVidID[vidCount] = Video.getID(i);
                    vidCount++;
                }
            }
            emit curListChanged(Video, curVidID);
        }
        else if(MenuMode == 0 && remoteMode == 1){ /// set Song from artist + remote
            selID = RemArtist.getID(selected);
            curSongID = new int[RemSong.getSize()];
            for(int i = 0; i< RemSong.getSize(); i++){
                if(RemSong.getPar(i) == selID){
                    curSong << RemSong.getName(i);
                    curSongID[songCount] = RemSong.getID(i);
                    songCount++;
                }
            }
            emit curListChanged(RemSong, curSongID);
        }
        else if(MenuMode == 1 && remoteMode == 1){   /// set Song from album + remote
            selID = RemAlbum.getID(selected);
            curSongID = new int[RemSong.getSize()];
            for(int i = 0; i< RemSong.getSize(); i++){
                if(RemSong.getPar(i) == selID){
                    curSong << RemSong.getName(i);
                    curSongID[songCount] = RemSong.getID(i);
                    songCount++;
                }
            }
            emit curListChanged(RemSong, curSongID);
        }
        else if(MenuMode == 2 && remoteMode == 1){  /// set video from vid dir
            selID = RemVidDir.getID(selected);
            curVidID = new int[RemVideo.getSize()];
            for(int i = 0; i< RemVideo.getSize(); i++){
                if(RemVideo.getPar(i) == selID){
                    curSong << RemVideo.getName(i);
                    curVidID[vidCount] = RemVideo.getID(i);
                    vidCount++;
                }
            }
            emit curListChanged(RemVideo, curVidID);
        }

    t_Model->setStringList(curSong);
    ui->TrackList->setModel(t_Model);
}

void browse::on_MenuList_clicked(const QModelIndex &index)
{
    emit MenuSelection(ui->MenuList->currentIndex().row());
}

void browse::on_TrackList_clicked(const QModelIndex &index)
{
    int selected = 0;
    selected = ui->TrackList->currentIndex().row();
    cout << "selected " << selected << endl;
    emit selectionChanged(selected);
    /// submit new clicked listing
    if(MenuMode == 0 && remoteMode == 0){             /// listing local songs
        for(int i=0; i<=Song.getSize(); i++){
            if(curSongID[selected] == Song.getID(i)){
                cout << Song.getName(i) << " " << Song.getPath(i) << " " << Song.getID(i) << " " << Song.getPar(i) << endl;
                emit plItemChanged(Song.getName(i), Song.getPath(i), Song.getID(i), Song.getPar(i));
            }
        }
    }
    else if(MenuMode == 1 && remoteMode == 0){         /// listing local videos
        for(int i =0; i<=vidCount; i++){
            if(curVidID[selected]== Video.getID(i)){
                emit plItemChanged(Video.getName(i), Video.getPath(i), Video.getID(i), Video.getPar(i));
            }
        }
    }
   else if(MenuMode == 0 && remoteMode == 1){          /// listing remote songs from artists
        for(int i=0; i<=RemSong.getSize(); i++){
            if(curSongID[selected] == RemSong.getID(i)){
                emit plItemChanged(RemSong.getName(i), RemSong.getPath(i), RemSong.getID(i), RemSong.getPar(i));
            }
        }
    }
    else if(MenuMode == 1 && remoteMode == 1){          /// listing remote songs from albums
        for(int i=0; i<=RemSong.getSize(); i++){
            if(curSongID[selected] == RemSong.getID(i)){
                emit plItemChanged(RemSong.getName(i), RemSong.getPath(i), RemSong.getID(i), RemSong.getPar(i));
            }
        }
    }
    else if(MenuMode == 2 && remoteMode == 1){          /// listing remote videos from directories
        for(int i =0; i<=vidCount; i++){
            if(curVidID[selected]== RemVideo.getID(i)){
                emit plItemChanged(RemVideo.getName(i), RemVideo.getPath(i), RemVideo.getID(i), RemVideo.getPar(i));
            }
        }
    }
 }

void browse::on_TrackList_doubleClicked(const QModelIndex &index)
{
    emit FullSelection(ui->TrackList->currentIndex().row());
}
