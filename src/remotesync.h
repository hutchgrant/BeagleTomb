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
#ifndef REMOTESYNC_H
#define REMOTESYNC_H

#include "prefobj.h"
#include "fileobj.h"
#include <QtSql>

class remotesync
{
#define MAXQRY 100


public:
    prefObj pref;
    QSqlDatabase db;

    remotesync();

    void setPref(prefObj &src);

    void openDB();

    void closeDB();
    void Fill(fileObj &Artist, fileObj &Album, fileObj &Song, fileObj &VidDir, fileObj &Video);

    int getAudioMenu();

    int getVideoMenu();

    void connectTracks(fileObj &folder, fileObj &src, int lookID, int mode);

    virtual ~remotesync();

};

#endif // REMOTESYNC_H
