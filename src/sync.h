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


#ifndef SYNCMe_H_
#define SYNCMe_H_

#include <QtSql>

#include <iostream>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <fstream>

#include "mysqlconn.h"
#include "readDB.h"
#include "radioObj.h"
#include "mysqlconn.h"
#include "fileobj.h"

#define TEMPSYNCPREF "/.beagletomb/BTmedia.db"

using namespace std;

class syncMe {

public:
        string DBLocation;
        QSqlDatabase db;

        syncMe(const char *server, const char *user, const char *pass, const char *table, const char *dbLocation);

        void writeAllRemote(fileObj &Artist, fileObj &Album, fileObj &Song, fileObj &VidDir, fileObj &Video);

        void writeMe(string qry);;

        int getMaxPos(int count);
        void sendToShell();
        void RemoveTMP();
	void deleteDB(const char *dbLocation);
	void createDB(const char *dbLocation);
        void OpenDB();
        int control(const char *server, const char *user, const char *pass, const char *table, const char *dbLocation);

	virtual ~syncMe();
};
#endif /* SYNCMe_H_ */
