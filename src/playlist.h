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
#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QWidget>
#include <QStringListModel>
#include "fileobj.h"
#include "dbconnect.h"
#include "newplaylist.h"
namespace Ui {
class playlist;
}

class playlist : public QWidget
{
    Q_OBJECT
    
public:

    dbconnect dbCon;
    fileObj playlists, playlistItems, newPList;
    newplaylist newplDg;
    int *curPLlist;
    int plSelected, playlistSelected;     /// items and playlists index selected
    int PLMODE;         /// current playlist mode: 0) playlists 1) playlist items
    string newPLName;   ///  name for new playlist
    int newItemCount;   /// counter for items in new playlist
    string tempPLName, tempPLPath;
    int tempPLID, tempPLPar;
    int lastPlaylistID;

    explicit playlist(QWidget *parent = 0);
    ~playlist();
    void initCueID(int initial, int newsize);
    void createPLTable();
    void writeNew(int type);
    void removePL(int type);
    void createNewPL();
    void fillPL();
    bool readPL();
    void AddToPL(){
        if(newItemCount == 0){
            newPList.initFile(100);
        }
        dbCon.getLastIDs(&lastPlaylistID);
        newPList.set(newItemCount, tempPLID, lastPlaylistID, tempPLName.c_str(), tempPLPath.c_str());
        newItemCount++;
    }

public slots:

    void AddToTempPL(string tempName, string tempPath, int tempID, int tempPar){
        tempPLName = tempName;
        tempPLPath = tempPath;
        tempPLID = tempID;
        tempPLPar = tempPar;
    }


signals:
    void playlistChanged(fileObj &plItem, int * plItemList);
    void playlistSelection(int selected);
    void playlistFullSelection(int selected);
private slots:

    void on_PLAYLIST_doubleClicked(const QModelIndex &index);

    void on_PLAYLIST_clicked(const QModelIndex &index);

    void on_open_tool_clicked();

    void on_add_tool_clicked();

    void on_remove_tool_clicked();

private:
    Ui::playlist *ui;
    QStringListModel *pl_model;

};

#endif // PLAYLIST_H
