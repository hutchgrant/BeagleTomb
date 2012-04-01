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

#ifndef RADIOOBJ_H
#define RADIOOBJ_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <QMainWindow>

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <fstream>
#include <QDir>
#include <QFileInfo>
#include <QString>
#include <QDebug>
#include "preferences.h"
using namespace std;

class radioObj
{
   // Q_OBJECT
public:

    string *r_name, *r_url;
    string DBlocation;
    int radioCount, r_ItemCount;

    radioObj();
    radioObj(const radioObj &src);
    radioObj& operator=(const radioObj &src);
    virtual ~radioObj();

    void initPL();
    void ReInitPL();
    void setDB(string DBlocate);
    void Add(string name, string url);
    void Remove(string name, int pos);
    void writeDB();
    void writeDBFill();
    int getMaxPos(int count);
    void sendToShell(string qry);
    void setName(string name, int count){
        r_name[count] = name;
    }
    void setUrl( string name, int count){
        r_url[count] = name;
    }
    void setSize(int size){
        radioCount = size;
    }

    int getCount(){
        return radioCount;
    }
    string getName(int count){
        return r_name[count];
    }
    string getUrl(int count){
        return r_url[count];
    }

QStringList RefillPlaylist();

};

#endif // RADIOOBJ_H
