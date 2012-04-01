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

#define LOCALSYNC "/.BeagleTomb/BTlocal.db"
using namespace std;

class localsync
{

   int dirCount;  // counter for directories
   int fileCount; // counter for files

   int dirINIT;   // allocated size for DIR array
   int fileINIT;  // allocated size for FILE array

   string *lclDir;   // local directory path array
   string *lclDirName; // local directory name array
   string *lclFiles;  // local files array
   int *lclDirPar;   // parentID of each DIRECTORY
   int *lclFilePar;  // parentID of each FILE
   int *lclDirID;   //  ID for each directory;
   int *lclFileID; // ID for each file;

   int lastID;   // Last ID in database for next ID
   int parentID;  // ParentID of current DIR
   int folderAddCount; // counter for overal number folder imports

   QSqlDatabase db;
   string home, db_local;

public:
    localsync();
    virtual ~localsync();
    void initAll();
    void initFiles(int beg, int end);
    void initDirs(int beg, int end);
    void scanFiles(int scanType);
    void scanDir(QString dir);

    void Sync(QDir usrDir, int syncType);
    void Remove();

    void openLocalDB();
    void openLocalDB2();

    void createLocalDB();
    void writeDBFiles(char *dbTable);
    void writeDBDirs(char *dbTable);
    void writeMe(string qry);
    void removeDir(int selected);
//  void removeFile(int selected);


    int getMaxPos(int count);
   fileObj& readLocalDB(int type, fileObj &src);
   void setLastID(int last){
       lastID = last;
   }

   void addFile(int count, string name, int par){
       lclFiles[count] = name;
       lclFilePar[count] = par;
       lclFileID[count] = generateID();
       fileCount++;
       if(fileCount >= fileINIT){
           initFiles(fileCount, 100);
       }
   }
   void addFolder(int count, string dir, string name){
       if(dirCount == 0){

           lclDir[count] = dir;     /// full path
           lclDirName[count] = name;  /// folder name
           lclDirID[count] = dirCount;     /// folder ID
           lclDirPar[count] = 0; /// folder parent
           parentID = 0;
       }
       else{
           lclDir[count] = dir;         /// folder path
           lclDirName[count] = name;    /// folder name
           lclDirPar[count] = parentID; /// folder parent
           lclDirID[count] = dirCount;     /// folder ID
       }
       dirCount++;                   /// dir count
       if(dirCount >= dirINIT){
           initDirs(dirCount, 100);
       }

   }

   int generateID(){

       const char alphagen[] = "0123456789";
       int random[10];
       char fin[10];
       int final = 0;
       for(int i=0; i<10; i++){
           random[i] = rand() % 9;
       }

       for(int i =0; i<10; i++){
           fin[i] = alphagen[random[i]];
       }

       final = atoi(fin);
       return final;

   }

private:
    QDir mydir;
};

#endif // LOCALSYNC_H
