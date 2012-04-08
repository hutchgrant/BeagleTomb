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

#define LOCALSYNC "/.beagletomb/BTlocal.db"
using namespace std;

class localsync
{

    int AudItemINIT; // allocated size for Audio Item Array
    int VidItemINIT; // allocated size for Video Item Array
    int AudDirINIT;  // allocated size for Audio Directory Array
    int VidDirINIT;  // allocated size for Video Directory Array

    int AudItemCount; // counter for local Audio Files
    int VidItemCount; // counter for local Video Files
    int AudDirCount;  // counter for local Audio directories
    int VidDirCount; // counter for local Video directories

    string *lclDir;   // local directory path array
    string *lclDirName; // local directory name array
    string *lclFiles;  // local files array
    string *lclFileNames;
    int *lclDirPar;   // parentID of each DIRECTORY
    int *lclFilePar;  // parentID of each FILE
    int *lclDirID;   //  ID for each directory;
    int *lclFileID; // ID for each file;

    int lastID;   // Last ID in database for next ID
    int parentID;  // ParentID of current DIR
    int AudFolderCount; // counter for overal audio folder imports i.e. last folder ID
    int VidFolderCount;  // counter for overall video folder imports i.e. last folder ID
    int AudioCount;      // counter for overall audio file imports i.e. last file ID
    int VideoCount;      // counter for overall video file imports i.e. last file ID

    QSqlDatabase db;
    string home, db_local;

public:
    localsync();
    virtual ~localsync();
    void initAll();
    void initFiles(int beg, int end, int count);
    void initDirs(int beg, int end, int count);
    void initLocalObj();
    void scanFiles(int scanType);
    void scanDir(QString dir, int scanType);

    string getDirectoryByPar(int parID, int count);

    void getLastIDs(int type);
    void Sync(QDir usrDir, int syncType);
    void Remove();

    void openLocalDB();
    void openLocalDB2();

    void createLocalDB();
    void writeDBFiles(char *dbTable, int init, int type);
    void writeDBDirs(char *dbTable, int init, int type);
    void writeMe(string qry);
    void removeDir(int selected, int mode);
    //  void removeFile(int selected);


    int getMaxPos(int count);
    fileObj& readLocalDB(int type, fileObj &src);
    void setLastID(int last){
        lastID = last;
    }

    void addFile(int count, string direc, string name, int par, int type){
        lclFileNames[count] = name;
        lclFiles[count] = direc;
        lclFilePar[count] = par;
        if(type == 0){
            lclFileID[count] = AudItemCount+AudioCount;
            AudItemCount++;
            if(AudItemCount >= AudItemINIT){
                initFiles(AudItemCount, 100, AudItemCount);
                AudItemINIT = AudItemCount + 100;
            }
        }
        else{
            lclFileID[count] = VidItemCount+VideoCount;
            VidItemCount++;
            if(VidItemCount >= VidItemINIT){
                initFiles(VidItemCount, 100, VidItemCount);
                VidItemINIT = VidItemCount + 100;
            }
        }
    }

    /*
     * Import Audio + Video Folder.  Types: 0) Audio. 1) Video.
     */
    void addFolder(int count, string dir, string name, int type){
        lclDir[count] = dir;       /// full path
        lclDirName[count] = name;  /// folder name
        if(type == 0){
            if(AudDirCount == 0){          /// initial import folder
                lclDirPar[count] = 0;      /// parent to root
                lclDirID[count] = AudDirCount+AudFolderCount+5;
                parentID = AudDirCount+AudFolderCount+1;
                AudDirCount++;
            }
            else{
                lclDirPar[count] = parentID;
                lclDirID[count] = AudDirCount+AudFolderCount+1;

                AudDirCount++;
                if(AudDirCount >= AudDirINIT){
                    initDirs(AudDirCount, 100, AudDirCount);
                    AudDirINIT = AudDirCount + 100;
                }
            }
        }
        else{
            if(VidDirCount == 0){
                lclDirPar[count] = 0;      /// parent to root
                lclDirID[count] = VidDirCount+VidFolderCount+1;

                parentID = VidDirCount+VidFolderCount+1;
                VidDirCount++;
            }
            else{
                lclDirPar[count] = parentID;
                lclDirID[count] = VidDirCount+VidFolderCount+1;

                VidDirCount++;
                if(VidDirCount >= VidDirINIT){
                    initDirs(VidDirCount, 100, VidDirCount);
                    VidDirINIT = VidDirCount + 100;
                }

            }
        }
    }

private:
    QDir mydir;

};

#endif // LOCALSYNC_H
