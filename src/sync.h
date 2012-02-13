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
#include <iostream>

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <fstream>
#include "songObj.h"
#define TEMPSYNCPREF "/.BeagleTomb/cache/tempcache.txt"
#define createSQL "/usr/share/BeagleTomb/src/createSQL.sql"
#include "songObj.h"
#include "mysqlconn.h"


using namespace std;

class syncMe {

public:

        string DBLocation;

	syncMe(const char *server, const char *user, const char *pass, const char *table, const char *dbLocation);

        void videoWrite(songObj* Song, int songSize);

        void vidDirWrite(songObj* Song, int songSize);

        void songWrite(songObj* Song, int songSize);

        void albumWrite(songObj* Album, int albSize);

        void artistWrite(songObj* Artist, int artSize);

        void writeMe(string qry);;

        int getMaxPos(int count);
        void sendToShell();
        void RemoveTMP();
	void display(songObj* Artist, int *artSize, songObj* Album, int *albSize, songObj *Song, int *songSize);
	void deleteDB(const char *dbLocation);
	void createDB(const char *dbLocation);
	int control(const char *server, const char *user, const char *pass, const char *table, const char *dbLocation);

	virtual ~syncMe();
};
#endif /* SYNCMe_H_ */
