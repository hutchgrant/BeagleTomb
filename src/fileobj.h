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

#ifndef FILEOBJ_H
#define FILEOBJ_H

#define INITSIZE 100
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <QtGui/QMainWindow>

using namespace std;
class fileObj
{
public:

    string *fileName;    // Item name
    string *filePath;    // Item Path  *only if local
    int *fileID;         // Item Identification number
    int *filePar;       // Item Parent number
    int objSize;        // Number of Items
    int InitSize;       // Number size before reallocate


    fileObj();
    fileObj(const fileObj& src);
    fileObj& operator=(const fileObj& src);

    void initFile(int initSZ);
    void REinitFile(int oldsize, int newsize);
    void display();
    virtual ~fileObj();

    void setName(int item, const char *name){
        if(item >= 0 && item <= objSize){
            fileName[item] = name;
        }
    }
    void setPath(int item, const char *path){
        if(item >= 0 && item <= objSize){
            filePath[item] = path;
        }
    }

    void setID(int item, int newID){
        if(item >= 0 && item <= objSize){
            /// fill with new entry
            fileID[item] = newID;
        }
    }
    void setPar(int item, int newPar){
        if(item >= 0 && item <= objSize){

            /// fill with new entry
            filePar[item] = newPar;
        }
    }
    void set(int item, int newid, int newpar, const char *newname, const char *newpath){
        if (objSize >= InitSize-1){
            REinitFile(InitSize, 1000);
        }
        setID(item, newid);
        setPar(item, newpar);
        setName(item, newname);
        setPath(item, newpath);
        objSize++;
    }
    void set(int item, int newid, int newpar, const char *newname){
        if (objSize >= InitSize-1){
            REinitFile(InitSize, 1000);
        }
        setID(item, newid);
        setPar(item, newpar);
        setName(item, newname);
        setPath(item, "-");
        objSize++;
    }
    void setInit(int item, int newid, int newpar, const char *newname, const char *newpath){
        setID(item, newid);
        setPar(item, newpar);
        setName(item, newname);
        setPath(item, newpath);
        InitSize++;
    }
    void setSize(int size){
        objSize = size;

    }

    int getID(int item){
        return fileID[item];
    }
    int getPar(int item){
        return filePar[item];
    }
    char *getName(int item){
        char *final;
        final = new char[fileName[item].length()+1];
        strcpy(final, fileName[item].c_str());
        return final;
    }
    char *getPath(int item){
        char *final;
        final = new char[filePath[item].length()+1];
        strcpy(final, filePath[item].c_str());
        return final;
    }

    int getSize(){
        return objSize;
    }
    void setInit(int initItem){
        InitSize = initItem;
    }
    int getInit(){
        return InitSize;
    }



};

char* checkSongObjByID(int id, fileObj& src);   // returns song name based on query by unique ID
int checkSongObjIDByPar(int par, fileObj& src);   // returns song ID based on query by parent ID
int checkSongObjParByID(int id, fileObj& src);   // returns song ParID based on query by ID
char* checkSongObjPathByID(int id, fileObj& src);  // returns song path based on query by ID
#endif // FILEOBJ_H
