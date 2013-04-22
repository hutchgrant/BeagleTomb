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

#ifndef LOCALSYNC_H
#define LOCALSYNC_H
#include <QDir>
#include <QStringListModel>
#include <QDirIterator>
#include <QtGui/QMainWindow>
#include <qstringlist.h>
#include <QMainWindow>
#include <QFileDialog>
#include <iostream>
#include "fileobj.h"
#include <QtSql>
#include <sstream>
#include "dbconnect.h"

using namespace std;

class localsync
{
    int AudItemCount; // counter for local Audio Files
    int VidItemCount; // counter for local Video Files
    int AudDirCount;  // counter for local Audio directories
    int VidDirCount; // counter for local Video directories

    int AudFolderCount; // counter for overal audio folder imports i.e. last folder ID
    int VidFolderCount;  // counter for overall video folder imports i.e. last folder ID
    int AudioCount;      // counter for overall audio file imports i.e. last file ID
    int VideoCount;      // counter for overall video file imports i.e. last file ID

    dbconnect dbCon;
    int curVidCount, curAudCount;
    fileObj localDir, localFile;
public:
    localsync();
    virtual ~localsync();
    void scanFiles(int scanType);
    void scanDir(QString dir, int scanType);
    void Sync(QDir usrDir, int syncType);
    void Remove();

private:
    QDir mydir;

};

#endif // LOCALSYNC_H
