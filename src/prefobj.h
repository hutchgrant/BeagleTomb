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
#ifndef PREFOBJ_H
#define PREFOBJ_H
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <string>
#include <QString>
using namespace std;
class prefObj
{
public:

    string USER, UPASS, HOSTIP, HOSTPORT, HostTable, localDBPath;

    prefObj();
    prefObj(const prefObj& src);
    prefObj& operator=(const prefObj& src);

    void setPref(string user, string upass, string host_ip, string host_port, string table, string dblocal);

    virtual ~prefObj();



    QString getQHOSTIP(){
        QString q_HOSTIP = HOSTIP.c_str();
        return q_HOSTIP;
    }
    QString getQHOSTPORT(){
        QString q_HOSTPORT = HOSTPORT.c_str();
        return q_HOSTPORT;
    }
    QString getQUser(){
        QString q_user = USER.c_str();
        return q_user;
    }
    QString getQPass(){
        QString q_pass = UPASS.c_str();
        return q_pass;
    }
    QString getQTable(){
        QString q_table =  HostTable.c_str();
        return q_table;
    }
    QString getQLocalDB(){
        QString q_lclDB = localDBPath.c_str();
        return q_lclDB;
    }

    string getHostIP(){
        return HOSTIP;
    }
    string getHostPort(){
        return HOSTPORT;
    }
    string getHostTable(){
        return HostTable;
    }
    string getUser(){
        return USER;
    }
    string getUPass(){
        return UPASS;
    }
    string getDBPath(){
        return localDBPath;
    }
};

#endif // PREFOBJ_H
