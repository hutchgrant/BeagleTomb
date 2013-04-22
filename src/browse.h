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

#ifndef BROWSE_H
#define BROWSE_H

#include <QWidget>
#include <QStringListModel>
#include "fileobj.h"
#include "localsync.h"
#include "dbconnect.h"
#include "mysqlconn.h"
#include "remotesync.h"
#include "prefobj.h"

namespace Ui {
class browse;
}

class browse : public QWidget
{
    Q_OBJECT
    
public:
    int songCount;
    int vidCount;
    localsync lclSync;
    dbconnect dbCon;
    prefObj pref;

    int remoteMode; /// 0  = local  , 1 = remote

    explicit browse(QWidget *parent = 0);
    ~browse();
    void Sync(int mode);
    void ToggleMode();
    void getPref();
signals:
    void curListChanged(fileObj &filelist, int *itemList);
    void plItemChanged(string plName, string plPath, int plID, int plPar);
    void selectionChanged(int);                         //  a track was selected
    void FullSelection(int);                            // a track was double clicked
    void MenuSelection(int);                            // a Menu Item was selected
    void prefChanged(prefObj &src, int selID);
public slots:
    void updateTitle(int);                               // update Right ViewList
    void updateMenu();                                   // update Left ViewList
    void updateMode(int mode){                          // update view mode
        MenuMode = mode;
        updateMenu();
    }
private slots:
    void on_MenuList_clicked(const QModelIndex &index);
    void on_TrackList_clicked(const QModelIndex &index);

    void on_TrackList_doubleClicked(const QModelIndex &index);

private:
    int MenuMode;   /// 0  = Artist , 1 = VidDir
    fileObj Artist, Album, Song, VidDir, Video;
    fileObj RemArtist, RemAlbum, RemSong, RemVidDir, RemVideo;
    int *curSongID, *curVidID;
    Ui::browse *ui;
    QStringListModel *m_Model;
    QStringListModel *t_Model;
};

#endif // BROWSE_H
