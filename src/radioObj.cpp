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

#include "radioObj.h"
#define MAXRADSIZE 10

radioObj::radioObj()
{
    initPL();
    radioCount = 0;
}
void radioObj::setDB(string DBlocate){
    DBlocation = DBlocate;
}

/*
  * Initial allocation Radio Playlist
  */
void radioObj::initPL(){
    r_name = new string[MAXRADSIZE];
    r_url = new string[MAXRADSIZE];
    for(int i=0; i<MAXRADSIZE; i++){
        r_name[i] = "-";
        r_url[i] = "-";
    }
}

/*
  *Dynamic allocate Radio Playlist
  */
void radioObj::ReInitPL(){
    /// re initialize playlist object
    string *file, *fileUrl;
    file = new string[radioCount];
    fileUrl = new string[radioCount];
    for(int i=0; i< radioCount; i++){
        file[i] = r_name[i];
        fileUrl[i] = r_url[i];
    }

    r_name = new string[radioCount+1];
    r_url = new string[radioCount+1];

    for(int i=0; i< radioCount; i++){
        r_name[i] = file[i];
        r_url[i] = fileUrl[i];
    }
}

/*
  * remove playlist item from playlist object at integer pos
  */
void radioObj::Remove(string name, int pos){
    char qryState[200];
        sprintf(qryState, "\"DELETE from radio WHERE name = '%s';\"", name.c_str());
        cout << qryState << endl;
        sendToShell(qryState);
}


void radioObj::Add(string name, string url)
{
    // allocate
    ReInitPL();
     /// Add to our playlist object
    setName(name,radioCount);
    setUrl(url,radioCount);
    cout << "adding radio " << getName(radioCount) << endl;
    radioCount++;
}

/*
  * refill radio list with radio object items
  */
QStringList radioObj::RefillPlaylist(){

    r_ItemCount = 0;
    QStringList RadioItem;
    string str;
        cout << "count is " << radioCount << endl;
        for(int i = 0; i<= radioCount-1; i++){
            str = getName(i);
            if(str.compare("-") != 0)
            cout << "refilling with " << str << endl;
                RadioItem << str.c_str();
                r_ItemCount++;
        }
    return RadioItem;
}

void radioObj::writeDB(){
    char qryState[200];
     int count = radioCount - 1;
        sprintf(qryState, "\"INSERT INTO radio (id, name, url) VALUES (null, '%s', '%s');\"", getName(count).c_str(), getUrl(count).c_str());
        cout << qryState << endl;
        sendToShell(qryState);
}

void radioObj::writeDBFill(){

    char *qryState;
     for(int count = 0; count <= radioCount-1; count++){
         qryState = new char[200];
        sprintf(qryState, "\"INSERT INTO radio (id, name, url) VALUES (null, '%s', '%s');\"", getName(count).c_str(), getUrl(count).c_str());
        cout << qryState << endl;
        sendToShell(qryState);
     }
}
radioObj::radioObj(const radioObj &src){
    if(this != &src){
        radioCount = src.radioCount;
        r_name = new string[radioCount];
        r_url = new string[radioCount];
        for(int i=0; i< radioCount; i++){
            r_name[i] = src.r_name[i];
            r_url[i] = src.r_url[i];
        }
    }
}

radioObj& radioObj::operator=(const radioObj &src){
    if(this != &src){
        radioCount = src.radioCount;
        delete [] r_name;
        delete [] r_url;
        r_name = new string[radioCount];
        r_url = new string[radioCount];
        for(int i=0; i< radioCount; i++){
            r_name[i] = src.r_name[i];
            r_url[i] = src.r_url[i];
        }
    }
}

radioObj::~radioObj(){

}

void radioObj::sendToShell(string qry){
    char FinalLink[550];
    sprintf(FinalLink, "sqlite3 %s %s", DBlocation.c_str(), qry.c_str());
    cout << "final qry : " << FinalLink <<endl;
    system(FinalLink);
}


int radioObj::getMaxPos(int count) {
    int posMax;

    if (count < 400 && count > 100) {
        posMax = 100;
    } else if (count < 100 && count > 20) {
        posMax = 10;
    } else if (count < 20 && count < 10) {
        posMax = 1;
    } else if (count < 20 && count > 10) {
        posMax = 5;
    } else {
        posMax = 200;
    }
    return posMax;
}
