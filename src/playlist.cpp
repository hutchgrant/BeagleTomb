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

#include "playlist.h"
#include "ui_playlist.h"

playlist::playlist(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::playlist)
{
    ui->setupUi(this);
    PLMODE = 0;
    playlists.initFile(100);
    playlistItems.initFile(100);
    if(readPL()){
        fillPL();
    }
    tempPLName = "-";
    tempPLPath = "-";
    tempPLID = 0;
    tempPLPar = 0;
    playlistSelected = 0;
    plSelected = 0;
    lastPlaylistID = 0;
    plSelected = 0;
    newItemCount = 0;
}

playlist::~playlist()
{
    delete ui;
}
void playlist::createNewPL(){
    newplDg.show();
    if(newplDg.exec()==QDialog::Accepted){
        newPLName = newplDg.getName();
        cout << "new playlist "<< newPLName << endl;
        writeNew(0);
        newItemCount = 0;
    }
}

void playlist::writeNew(int type){

    if(type == 0){  // add playlist

        char *addQry;
        addQry = new char[strlen(newPLName.c_str())+200];
        sprintf(addQry, "INSERT INTO playlists (lcl_dir_par, lcl_dir_name, lcl_dir_path) VALUES ('%d', '%s', '%s')", 0, newPLName.c_str(), "-");
        dbCon.writeMe(string(addQry));
        delete [] addQry;
    }
    else if(type == 1){  // add playlist item

        char *addQry;
        addQry = new char [strlen(newPList.getPath(newItemCount-1))+strlen(newPList.getName(newItemCount-1))+strlen(newPList.getPath(newItemCount-1))+100];
        sprintf(addQry, "INSERT INTO playlist_items (lcl_dir_par, lcl_dir_name, lcl_dir_path) VALUES ('%d', '%s', '%s')", newPList.getPar(newItemCount-1), newPList.getName(newItemCount-1), newPList.getPath(newItemCount -1));
        dbCon.writeMe(string(addQry));
        delete [] addQry;
    }
    else{
    }
}

void playlist::removePL(int type){
    char *addQry;
    if(type == 0){  // remove playlist
        addQry = new char[100];
        sprintf(addQry, "DELETE FROM playlists where key = %d", playlists.getID(playlistSelected));
        dbCon.writeMe(string(addQry));
    }
    else if(type == 1) { // remove playlist item
        addQry = new char[100];
        sprintf(addQry, "DELETE FROM playlist_items where key = %d", curPLlist[playlistSelected]);
        dbCon.writeMe(string(addQry));
    }
    delete [] addQry;
}

bool playlist::readPL(){
    dbCon.readDB(playlists, "SELECT * FROM playlists", 0);
    dbCon.readDB(playlistItems, "SELECT * FROM playlist_items", 0);
    return true;
}

void playlist::fillPL(){
    QStringList curList;
    int count = 0;
    if(PLMODE == 0){  // browsing playlists
        for(int i= 0; i< playlists.getSize(); i++){
            curList << playlists.getName(i);
        }
    }
    else if(PLMODE == 1){            // browsing playlist items

        curPLlist = new int[playlistItems.getSize() + 10];
        for(int i = 0; i< playlistItems.getSize(); i++){
            if(playlistItems.getPar(i) == playlists.getID(playlistSelected)){
                curList << playlistItems.getName(i);
                curPLlist[count] = playlistItems.getID(i);
                count++;
            }
             emit playlistChanged(playlistItems, curPLlist);
        }
    }
    else if(PLMODE == 2){            // new playlist items
        curPLlist = new int[newPList.getSize()+10];
        for(int i = 0; i<= newPList.getSize(); i++){
            curList << newPList.getName(i);
            curPLlist[i] = newPList.getID(i);
        }
        emit playlistChanged(newPList, curPLlist);
    }

    pl_model = new QStringListModel(this);
    pl_model->setStringList(curList);
    ui->PLAYLIST->setModel(pl_model);
}
void playlist::on_PLAYLIST_doubleClicked(const QModelIndex &index)
{
    if(PLMODE == 0){
        playlistSelected = ui->PLAYLIST->currentIndex().row();
        PLMODE = 1;
        fillPL();
    }
    else{
        plSelected = ui->PLAYLIST->currentIndex().row();
        emit playlistFullSelection(plSelected);

    }
}

void playlist::on_PLAYLIST_clicked(const QModelIndex &index)
{
    if(PLMODE == 0){
        playlistSelected = ui->PLAYLIST->currentIndex().row();
    }
    else if(PLMODE == 1){
        plSelected = ui->PLAYLIST->currentIndex().row();
        emit playlistSelection(plSelected);
    }
}

void playlist::on_open_tool_clicked()
{
    PLMODE = 0;
    if(readPL()){
       fillPL();
    }
}

void playlist::on_add_tool_clicked()
{
    if(PLMODE==0){
        createNewPL();
        AddToPL();
        writeNew(1);
        PLMODE = 1;
        playlistSelected = playlists.getSize();

        if(readPL()){
            fillPL();
        }
    }
    else if(PLMODE==1){
        AddToPL();
        writeNew(1);
        if(readPL()){
            fillPL();
        }
    }
}

void playlist::on_remove_tool_clicked()
{
    removePL(PLMODE);
    if(readPL()){
    fillPL();
    }
}
