#ifndef FILEOBJ_H
#define FILEOBJ_H

#define INITSIZE 100
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
using namespace std;
class fileObj
{
public:

    string *fileName;    // Item name
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
    ~fileObj();

    void setName(int item, const char *name){
        if(item >= 0 && item <= objSize){
            fileName[item] = name;
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
    void set(int item, int newid, int newpar, const char *newname){
        if (objSize >= InitSize-1){
            REinitFile(InitSize, 1000);
        }
        setID(item, newid);
        setPar(item, newpar);
        setName(item, newname);
        objSize++;
    }
    void setInit(int item, int newid, int newpar, const char *newname){
        setID(item, newid);
        setPar(item, newpar);
        setName(item, newname);
        InitSize++;
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
    int getSize(){
        return objSize;
    }
    void setInit(int initItem){
        InitSize = initItem;
    }
    int getInit(){
        return InitSize;
    }


    void delFileName(){
        objSize = 0;
        delete [] fileName;
    }
};

#endif // FILEOBJ_H
