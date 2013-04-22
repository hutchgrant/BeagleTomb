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
