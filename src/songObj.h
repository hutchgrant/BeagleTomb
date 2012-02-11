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


#include <string>
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#include <cstring>

#ifndef songObj_H_
#define songObj_H_


#define MAXSTR 60
using namespace std;
class songObj {

	char *File;
	int FileID;
	int FilePar;

public:
	songObj();
	void set(char *name, int id, int par);
	songObj(char *n, int id, int par);
	songObj(const songObj& src);
	songObj& operator=(const songObj& src);

	void display(ostream& os) const;
	virtual ~songObj();

        void setFile(char *name){
                if(name != NULL){
			File = new char[strlen(name) + 1];
                        strcpy(File, name);
		}
	}
	void setFileID(int id){
		if(id >= 0){
			FileID = id;
		}
	}
	void setFilePar(int par){
		if(par >=0){
			FilePar = par;
		}
	}
	char *getFile() const { return File; }
	int getFileID() const { return FileID; }
	int getFilePar() const { return FilePar; }
};

ostream& operator<<(ostream& os, const songObj& s);
char* checkSongObjByID(int id, songObj *src, int ObjSize);   // returns song name based on query by unique ID
int checkSongObjIDByPar(int par, songObj *src, int ObjSize);   // returns song ID based on query by parent ID
int checkSongObjParByID(int id, songObj *src, int ObjSize);   // returns song ParID based on query by ID


#endif /* songObj_H_ */
