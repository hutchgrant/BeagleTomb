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
