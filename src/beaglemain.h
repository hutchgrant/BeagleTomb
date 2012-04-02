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


#ifndef BEAGLEMAIN_H
#define BEAGLEMAIN_H

#include <QMainWindow>
#include <stdlib.h>
#include <stdio.h>
#include "sync.h"
#include "readDB.h"
#include "mplaycon.h"
#include "prefdialog.h"
#include "qmpwidget.h"
#include "preferences.h"
#include "about.h"
#include "playlistobj.h"
#include "newplaylist.h"
#include "openplaylist.h"
#include "radioObj.h"
#include "localsync.h"
namespace Ui {
class BeagleMain;
}

class BeagleMain : public QMainWindow
{
    Q_OBJECT

public:

    int MenuMode, TitleMode;
    int albCount, songCount, vidCount, vidDirCount, radCount; ///  count of each item in the list
    int *curAlbID, *curSongID, *curVidID, *curVidDirID;       ///  unique identifier for current file
    int plMode;        /// playlist mode : 1 playlist browsing and 2: browsing tracks within playlist
    int pl_selected;  /// global playlist selection
     int title_selected;  /// global title selection
    int CON_MODE;

    char *finParent;
    char *finPath;
    char *finSong;

    About ab;
    PrefDialog prefDg;
    preferences pref, pref2;
    playlistobj pl;
    newplaylist newPL;
    openplaylist openPL;
    QMPwidget widget;
    mplayCon mplay;
    localsync SyncAudioLocal, SyncVideoLocal;
    fileObj Artist, Song, Album, VidDir, Video, DirecLocal, SongLocal, vidDirecLocal, VideoLocal;
    radioObj Radio;
    int artSize, albSize, songSize, vidSize, vidDirSize, radSize;

    bool playlistOpen;

    void RefillRadioPL();
    QStringList RefillRadList();

    explicit BeagleMain(QWidget *parent = 0);
   ~BeagleMain();

    void updateMenu(int type);
    void updateTitle();
    void updateLclSongDirs();
    void updateLclSongs();
    void updateLclSongs(int selected);
    void updateLclVidDirs();
    void updateLclVideos();

    void updateAlbMenu(int select);
    void updateTitle(int select);
    void Sync(int type);

    bool isRunning();

    void setMainPref(preferences pref);
    void RefillMainPL();
    void RefillPLFolder();
    void startSong(char *FinSong, int selID);
    void startLocal(char *finSong, char *finPath);
    void PlaylistPlay(int selID);
    void closeEvent(QCloseEvent *event);

private slots:
    void on_SYNC_but_clicked();

    void on_MODE_combo_currentIndexChanged(int index);

    void on_STOP_but_clicked();

    void on_TitleList_doubleClicked(QModelIndex index);

    void on_MenuList_clicked(QModelIndex index);

    void on_VOL_dial_valueChanged(int value);

    void on_SEEK_slider_sliderMoved(int position);

    void on_FWD_but_pressed();

    void on_FWD_but_clicked();

    void on_PAUSE_but_clicked();


    void on_actionPreferences_2_activated();

    void on_actionAbout_activated();

    void on_actionSync_activated();

    void on_ADD_but_clicked();

    void on_PlayList_doubleClicked(QModelIndex index);

    void on_REMOVE_but_clicked();

    void on_SAVE_but_clicked();

    void on_OPEN_but_clicked();

    void on_FFWD_but_clicked();

    void on_RRWD_but_clicked();

    void on_UP_but_clicked();

    void on_DOWN_but_clicked();

    void on_PlayList_clicked(QModelIndex index);

    void on_actionDonate_2_triggered();

    void on_ADMIN_but_clicked();

    void on_but_RadAdd_clicked();

    void on_but_RemRad_clicked();

    void on_list_radio_clicked(QModelIndex index);

    void on_list_radio_doubleClicked(QModelIndex index);

    void on_but_import_aud_clicked();

    void on_but_remote_tog_clicked();

    void on_but_import_vid_clicked();

private:
    Ui::BeagleMain *ui;
    QStringListModel *t_Model;
    QStringListModel *m_Model;
    QStringListModel *r_Model;
};

#endif // BEAGLEMAIN_H
