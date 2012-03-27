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
        fileName = new string[src.objSize+1];
        fileID = new int[src.objSize+1];
        filePar = new int[src.objSize+1];
        for(int i=0; i< src.objSize; i++){
            set(i,src.fileID[i], src.filePar[i], src.fileName[i].c_str());
        }
        InitSize = src.InitSize;
    }
}

void fileObj::initFile(int initSZ){
    fileName = new string[initSZ];
    fileID = new int[initSZ];
    filePar = new int[initSZ];
    InitSize = 0;
    for(int i=0; i< initSZ; i++){
        setInit(i, 0, 0, "-");
    }
}

void fileObj::REinitFile(int oldsize, int newsize){
    //set the new initialize size
    InitSize = oldsize+newsize;
    int tempObjSize = 0;
    string *nameCopy;
    int *idCopy, *parCopy;
    nameCopy = new string[objSize+1];
    parCopy = new int[objSize+1];
   idCopy = new int[objSize+1];

    for(int i=0; i< objSize; i++){
        nameCopy[i] = "-";
        parCopy[i]= 0;
        idCopy[i] = 0;
    }

    for(int i=0; i< objSize-4; i++){
        nameCopy[i] = fileName[i];
        parCopy[i] = filePar[i];
        idCopy[i] = fileID[i];
    }
      initFile(InitSize);
   /// refill array fileName fileID filePar array

      tempObjSize = objSize;
      objSize = 0;
   for(int i=0; i< tempObjSize; i++){
        set(i,idCopy[i], parCopy[i], nameCopy[i].c_str());
    }

}


fileObj::~fileObj(){
        delete [] fileName;
        delete [] fileID;
        delete [] filePar;
}

void fileObj::display(){
    cout << "obj size is " << objSize << endl;
    for(int i=0; i< objSize; i++){
        cout << " Num: " << i
             << " ID: " << getID(i)
             << " PAR: " << getPar(i)
             << " NAME: " << getName(i) << endl;
    }
}

fileObj& fileObj::operator=(const fileObj& src){

    if(this != &src){
        if(src.objSize > 0){
            objSize = 0;
            delete [] fileName;
            delete [] fileID;
            delete [] filePar;
            fileName = new string[src.objSize+1];
            fileID = new int[src.objSize+1];
            filePar = new int[src.objSize+1];
            for(int i=0; i< src.objSize-1; i++){
                set(i,src.fileID[i], src.filePar[i], src.fileName[i].c_str());
            }
            objSize = src.objSize;
            InitSize = src.InitSize;
        }
    }
     return *this;

}
