#include "fileobj.h"

fileObj::fileObj()
{
    objSize = 0;
    InitSize = 0;
    initFile(INITSIZE);
}


fileObj::fileObj(const fileObj &src){

    if(src.objSize > 0){
        objSize = 0;
        delete [] fileName;
        delete [] fileID;
        delete [] filePar;
        delete [] filePath;
        initFile(src.objSize);
        for(int i=0; i< src.objSize; i++){
            set(i,src.fileID[i], src.filePar[i], src.fileName[i].c_str(), src.filePath[i].c_str());
        }
        objSize = src.objSize;
        InitSize = src.InitSize;
    }
}

void fileObj::initFile(int initSZ){
    fileName = new string[initSZ];
    fileID = new int[initSZ];
    filePar = new int[initSZ];
    filePath = new string[initSZ];
    InitSize = 0;
    for(int i=0; i< initSZ; i++){
        setInit(i, 0, 0, "-", "-");
    }
}

void fileObj::REinitFile(int oldsize, int newsize){
    //set the new initialize size
    InitSize = oldsize+newsize;
    int tempObjSize = 0;
    string *nameCopy, *pathCopy;
    int *idCopy, *parCopy;
    nameCopy = new string[objSize+1];
    parCopy = new int[objSize+1];
   idCopy = new int[objSize+1];
    pathCopy = new string[objSize+1];

    for(int i=0; i< objSize; i++){
        nameCopy[i] = "-";
        pathCopy[i] = "-";
        parCopy[i]= 0;
        idCopy[i] = 0;
    }

    for(int i=0; i< objSize; i++){
        nameCopy[i] = fileName[i];
        parCopy[i] = filePar[i];
        idCopy[i] = fileID[i];
        pathCopy[i] = filePath[i];
    }
    delete [] fileName;
    delete [] fileID;
    delete [] filePar;
   delete [] filePath;
      initFile(InitSize);
   /// refill array fileName fileID filePar array

      tempObjSize = objSize;
      objSize = 0;
   for(int i=0; i< tempObjSize; i++){
        set(i,idCopy[i], parCopy[i], nameCopy[i].c_str(), pathCopy[i].c_str());
    }

}


fileObj::~fileObj(){
        delete [] fileName;
        delete [] fileID;
        delete [] filePar;
        delete [] filePath;
}

void fileObj::display(){
    cout << "obj size is " << objSize << endl;
    for(int i=0; i< objSize; i++){
        cout << " Num: " << i
             << " ID: " << getID(i)
             << " PAR: " << getPar(i)
             << " NAME: " << getName(i)
             <<  " PATH: " << getPath(i) << endl;
    }
}

fileObj& fileObj::operator=(const fileObj& src){

    if(this != &src){
        if(src.objSize > 0){
            objSize = 0;
            delete [] fileName;
            delete [] fileID;
            delete [] filePar;
            delete [] filePath;
            initFile(src.objSize+1);

            for(int i=0; i< src.objSize-1; i++){
                set(i,src.fileID[i], src.filePar[i], src.fileName[i].c_str(), src.filePath[i].c_str());
            }
            objSize = src.objSize;
            InitSize = src.InitSize;
        }
    }
     return *this;

}

/*
  *  Search any Object for a track name by the using the ID
  */
char* checkSongObjByID(int id, fileObj& src){
    char *FinSong;
    if(src.getSize() > 0){
        for(int i = 0; i< src.getSize(); i++){
            if(src.getID(i) == id){

                FinSong = new char[strlen(src.getName(i))+1];
                strcpy(FinSong,src.getName(i));
            }
        }
    }
    return FinSong;
}

/*
  *  Search any Object for a track ID by the using the parent
  */
int checkSongObjIDbyPar(int par, fileObj& src){
    int FinID = 0;
    if(src.getSize() > 0){
        for(int i = 0; i< src.getSize(); i++){
            if(src.getPar(i) == par){

                FinID = src.getID(i);
            }
        }
    }
    return FinID;
}

/*
  *  Search any Object for a track Par by the using the ID
  */
int checkSongObjParByID(int id, fileObj& src){
    int FinPar;
    if(src.getSize() > 0){
        for(int i = 0; i< src.getSize(); i++){
            if(src.getID(i) == id){

                FinPar = src.getPar(i);
            }
        }
    }
    return FinPar;
}

/*
  *
  * Search any Object for a track Path by using the ID
  */
char *checkSongObjPathByID(int id, fileObj& src){
    char *finPath;
    if(src.getSize() > 0){
        for(int i =0; i< src.getSize(); i++){
            if(src.getID(i) == id){
                finPath = new char[strlen(src.getPath(i))+1];
                finPath = src.getPath(i);
            }
        }
    }
    return finPath;
}
