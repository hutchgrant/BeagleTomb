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


#include "songObj.h"

using namespace std;

songObj::songObj(){
    File = new char[MAXSTR];
    File = NULL;
    FileID = 0;
    FilePar = 0;
}

songObj::songObj(const songObj& src){
    FileID = src.FileID;
    FilePar = src.FilePar;
    if (src.File != NULL){
        File = new char[strlen(src.File) + 1];
        strcpy(File, src.File);
    }
    else{
        File = NULL;
    }
}

void songObj::set(char *name, int id, int par) {
    // TODO Auto-generated constructor stub
    if(name != NULL){
        setFile(name);
    }
    if(id != 0){
        setFileID(id);
    }
    if(par != 0){
        setFilePar(par);
    }
}

void songObj::display(ostream& os) const{
    os << "File: " << getFile() << "\t"
       << "FileID: " << getFileID() << "\t"
       << "FilePar: " << getFilePar() << endl;
}

songObj::songObj(char *n, int id, int par){
    if(n != NULL){
        setFile(n);
    }
    else{
        File = NULL;
    }
    if( id != 0){
        setFileID(id);
    }
    else{
        setFileID(0);
    }
    if(par != 0){
        setFilePar(par);
    }
    else{
        setFilePar(0);
    }
}

songObj& songObj::operator=(const songObj& src)
{
    if(this != &src)
    {
        if(File != NULL){
            delete [] File;
        }
        if(src.File != NULL){
            setFile(src.File);
        }
        if(src.FileID != 0){
            setFileID(src.FileID);
        }
        if(src.FilePar != 0){
            setFilePar(src.FilePar);
        }
    }
    return *this;
}

ostream& operator<<(ostream& os, const songObj& s){
    s.display(os);
    return os;
}
songObj::~songObj() {
    // TODO Auto-generated destructor stub
    delete [] File;
}

/*
  *  Search any Object for a track name by the using the ID
  */
char* checkSongObjByID(int id, songObj *src, int ObjSize){
    char *FinSong;
    if(ObjSize > 0){
        for(int i = 0; i<= ObjSize; i++){
            if(src[i].getFileID() == id){

                FinSong = new char[strlen(src[i].getFile())+1];
                strcpy(FinSong,src[i].getFile());
            }
        }
    }
    return FinSong;
}

/*
  *  Search any Object for a track ID by the using the parent
  */
int checkSongObjIDbyPar(int par, songObj *src, int ObjSize){
    int FinID = 0;
    if(ObjSize > 0){
        for(int i = 0; i<= ObjSize; i++){
            if(src[i].getFilePar() == par){

                FinID = src[i].getFileID();
            }
        }
    }
    return FinID;
}

/*
  *  Search any Object for a track Par by the using the ID
  */
int checkSongObjParByID(int id, songObj *src, int ObjSize){
    int FinPar;
    if(ObjSize > 0){
        for(int i = 0; i<= ObjSize; i++){
            if(src[i].getFileID() == id){

                FinPar = src[i].getFilePar();
            }
        }
    }
    return FinPar;
}
