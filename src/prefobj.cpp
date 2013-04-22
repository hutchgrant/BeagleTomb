#include "prefobj.h"

prefObj::prefObj()
{
    USER = "";
    UPASS = "";
    HOSTIP = "";
    HOSTPORT = "";
    HostTable = "";
    localDBPath = "";

}
prefObj::prefObj(const prefObj& src){
    USER = src.USER;
    UPASS = src.UPASS;
    HOSTIP = src.HOSTIP;
    HOSTPORT = src.HOSTPORT;
    HostTable = src.HostTable;
    localDBPath = src.localDBPath;
}



prefObj& prefObj::operator=(const prefObj& src){


    if(this != &src){
        setPref(src.USER, src.UPASS, src.HOSTIP, src.HOSTPORT, src.HostTable, src.localDBPath);
    }

    return *this;

}

void prefObj::setPref(string user, string pass, string host_ip, string host_port, string table, string localdb){
    USER = user;
    UPASS = pass;
    HOSTIP = host_ip;
    HOSTPORT = host_port;
    HostTable = table;
    localDBPath = localdb;
}

prefObj::~prefObj(){

}
