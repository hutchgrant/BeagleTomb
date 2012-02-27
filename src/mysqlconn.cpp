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


#include "mysqlconn.h"
using namespace std;

mysqlconn::mysqlconn(const char *server, const char* user, const char *pass, const char *table) {

    mysqlD.server = server;
    mysqlD.user = user;
    mysqlD.password = pass;
    mysqlD.database = table;
    /* Example input
 mysqlD.server = "192.168.1.116"; // the address of mysql DB
 mysqlD.user = "mediatomb"; 		// the user of mysql DB
 mysqlD.password = "mediatomb"; // the password of user of mysql DB
 mysqlD.database = "mediatomb"; // the table of mysql DB
 */
}

songObj* mysqlconn::dynamicArt(songObj* Artist, int sizeArt) {
    size_t newsize = sizeArt;
    songObj* MyCpy;
    MyCpy = new songObj[newsize];

    memcpy(MyCpy, Artist, sizeArt * sizeof(int));

    delete[] Artist;
    Artist = new songObj[newsize];
    Artist = MyCpy;
    return Artist;
}

MYSQL* mysqlconn::mysql_connection_setup(
    struct connection_details mysql_details) {
    // init mysql connection
    MYSQL *connection = mysql_init(NULL);
    // connect to the database with the details attached.
    if (!mysql_real_connect(connection, mysql_details.server,
                            mysql_details.user, mysql_details.password, mysql_details.database,
                            0, NULL, 0)) {
        printf("Conection error : %s\n", mysql_error(connection));
        exit(1);
    }
    return connection;
}

/**
 * Performs the query.
 */
MYSQL_RES* mysqlconn::mysql_perform_query(MYSQL *connection, char *sql_query) {
    // send the query to the database
    if (mysql_query(connection, sql_query)) {
        printf("MySQL query error : %s\n", mysql_error(connection));
        exit(1);
    }

    return mysql_use_result(connection);
}

songObj* mysqlconn::connectAlbum(songObj* Artist, int *artSize, songObj* Album, int *albSize){
    bool Myexit = false;
    int albCount = 0;
    int QryCount = 0;
    char *myQry = NULL;
    int albQryCount = 0;
    int curID;

    *albSize = MAXSONG;
    Album = new songObj[MAXALB];

    for(int i= 0 ; i <= MAXALB; i++){
        Album[i].set("-", 0, 0);
    }

    MYSQL *conn = NULL; // the connection
    MYSQL_RES *res = NULL; // the results
    MYSQL_ROW row = NULL; // the results row (line by line)

    while(Myexit != true){

	if (!myQry) {
            myQry = new char[MAXQRY];
	}
        curID = Artist[QryCount].getFileID();
        if(curID == 0){
            Myexit = 1;
        }
        // connect to the mysql database
        conn = mysql_connection_setup(mysqlD);
        sprintf(myQry, "SELECT * FROM mt_cds_object WHERE parent_id = %d",
                curID );

        res = mysql_perform_query(conn, myQry);

        while ((row = mysql_fetch_row(res)) != NULL) {
            ///////*****  Query for Album rows using artist
            if(strcmp(row[4], "object.container.album.musicAlbum") == 0){
                if (atoi(row[2]) == curID) {
                    albCount++;
                    Album[albCount].set(row[5], atoi(row[0]), atoi(row[2]));
                }
            }

        }
        *albSize = albCount;
        QryCount++;
        if (QryCount == *artSize) {
            Myexit = true;
        }
        mysql_free_result(res);
        mysql_close(conn);
    }
    return Album;

}
songObj* mysqlconn::connectSong(songObj* Album, int *albSize, songObj* Song, int *songSize){


    int songCount = 0;
    int QryCount = 0;
    char *myQry = NULL;
    int curID = 0;
    bool Myexit = false;

    *songSize = MAXSONG;
    Song = new songObj[MAXSONG];

    for(int i= 0 ; i <= MAXSONG; i++){
        Song[i].set("-", 0, 0);
    }

    MYSQL *conn = NULL; // the connection
    MYSQL_RES *res = NULL; // the results
    MYSQL_ROW row = NULL; // the results row (line by line)

    while (Myexit != true){


	if (!myQry) {
            myQry = new char[MAXQRY];
	}

	// connect to the mysql database
	conn = mysql_connection_setup(mysqlD);
	curID = Album[QryCount+1].getFileID();
	if(curID == 0){
            Myexit = true;
        }


        sprintf(myQry, "SELECT * FROM mt_cds_object WHERE parent_id = %d",
                curID);

        res = mysql_perform_query(conn, myQry);

        while ((row = mysql_fetch_row(res)) != NULL) {

            ///////*****  Query for Songs
            if (atoi(row[2]) == curID) {
                songCount++;
                Song[songCount].set(row[5], atoi(row[0]), atoi(row[2]));
            }
        }

        *songSize = songCount;
        QryCount++;
        if (QryCount == *albSize) {
            Myexit = true;
        }

        mysql_free_result(res);
        mysql_close(conn);
    }
    return Song;
}
songObj* mysqlconn::connectArtist(songObj* Artist, int artMenu, int *mySize){


    int artCount = 0;
    *mySize = MAXART;
    Artist = new songObj[MAXART];

    for(int i= 0 ; i <= MAXART; i++){
        Artist[i].set("-", 0, 0);
    }

    MYSQL *conn = NULL; // the connection
    MYSQL_RES *res = NULL; // the results
    MYSQL_ROW row = NULL; // the results row (line by line)

    char *myQry = NULL;

    if (!myQry) {
        myQry = new char[MAXQRY];
    }

    // connect to the mysql database
    conn = mysql_connection_setup(mysqlD);

    /// use artist menu ID  to get artists

    sprintf(myQry, "SELECT * FROM mt_cds_object WHERE parent_id = %d",
            artMenu);
    res = mysql_perform_query(conn, myQry);

    while ((row = mysql_fetch_row(res)) != NULL) {

        ///////*****  Query for MAIN root menu
        if (atoi(row[2]) == artMenu) {

            Artist[artCount].set(row[5], atoi(row[0]), atoi(row[2]));
            artCount++;
        }
    }

    *mySize = artCount;
    mysql_free_result(res);
    mysql_close(conn);

    return Artist;
}

songObj* mysqlconn::connectVideo(songObj* VidDir, int *vidDirSize, songObj* Video, int *vidSize){

    int VidCount = 0;


    int QryCount = 0;
    char *myQry = NULL;
    int curID = 0;
    bool Myexit = false;

    *vidSize = MAXVIDEO;
    Video = new songObj[MAXVIDEO];

    for(int i= 0 ; i <= MAXVIDEO; i++){
        Video[i].set("-", 0, 0);
    }

    MYSQL *conn = NULL; // the connection
    MYSQL_RES *res = NULL; // the results
    MYSQL_ROW row = NULL; // the results row (line by line)

    while (Myexit != true){


        if (!myQry) {
            myQry = new char[MAXQRY];
        }

        // connect to the mysql database
        conn = mysql_connection_setup(mysqlD);
        curID = VidDir[QryCount+1].getFileID();
        if(curID == 0){
            Myexit = true;
        }


        sprintf(myQry, "SELECT * FROM mt_cds_object WHERE parent_id = %d",
                curID);

        res = mysql_perform_query(conn, myQry);

        while ((row = mysql_fetch_row(res)) != NULL) {

            ///////*****  Query for Songs
            if (atoi(row[2]) == curID) {
                VidCount++;
                Video[VidCount].set(row[5], atoi(row[0]), atoi(row[2]));
            }
        }

        *vidSize = VidCount;
        QryCount++;
        if (QryCount == *vidDirSize) {
            Myexit = true;
        }

        mysql_free_result(res);
        mysql_close(conn);
    }
    return Video;
}



songObj* mysqlconn::connectVidDir(songObj* VidDir, int vidMenu, int *vidDirSize){

    int VidDirCount = 0;

    *vidDirSize = MAXVIDEO;
    VidDir = new songObj[MAXVIDEO];

    for(int i= 0 ; i <= MAXVIDEO; i++){
        VidDir[i].set("-", 0, 0);
    }

    MYSQL *conn = NULL; // the connection
    MYSQL_RES *res = NULL; // the results
    MYSQL_ROW row = NULL; // the results row (line by line)

    char *myQry = NULL;

    if (!myQry) {
        myQry = new char[MAXQRY];
    }

    // connect to the mysql database
    conn = mysql_connection_setup(mysqlD);

    /// use video menu ID  to get vid directory

    sprintf(myQry, "SELECT * FROM mt_cds_object WHERE parent_id = %d",
            vidMenu);
    res = mysql_perform_query(conn, myQry);

    while ((row = mysql_fetch_row(res)) != NULL) {

        ///////*****  Query for MAIN root menu
        if (atoi(row[2]) == vidMenu) {

            VidDir[VidDirCount].set(row[5], atoi(row[0]), atoi(row[2]));
            VidDirCount++;
        }
    }

    *vidDirSize = VidDirCount;
    /* clean up the database result set */
    mysql_free_result(res);
    /* clean up the database link */
    mysql_close(conn);

    return VidDir;
}

int mysqlconn::connectVidMenu(){
    int vidMenuID = 0, vidDirMenuID = 0, vidMenu = 0;


    bool Myexit = false; // exit variable
    int QryCount = 0;
    int rowCount = 0;
    char *myQry = NULL;

    MYSQL *conn = NULL; // the connection
    MYSQL_RES *res = NULL; // the results
    MYSQL_ROW row = NULL; // the results row (line by line)

    while (Myexit != true) {

        if (!myQry) {
            myQry = new char[MAXQRY];
        }

        // connect to the mysql database
        conn = mysql_connection_setup(mysqlD);

        /// use root to query for the Main menu's (audio + video)
        if (QryCount == 0) {
            sprintf(myQry, "SELECT * FROM mt_cds_object WHERE parent_id = %d",
                    0);
        }

        else if(QryCount == 1){
            sprintf(myQry, "SELECT * FROM mt_cds_object WHERE parent_id = %d",
                    vidMenuID);
        }

        //	cout << myQry << endl;
        res = mysql_perform_query(conn, myQry);
        rowCount = 0;
        while ((row = mysql_fetch_row(res)) != NULL) {

            if (atoi(row[2]) == 0 && rowCount == 3){
                vidMenuID = atoi(row[0]);
            }

            if(atoi(row[2]) == vidMenuID && rowCount == 1){
                vidDirMenuID = atoi(row[0]);
            }
            rowCount++;

        }
        QryCount++;
        if (QryCount > 2) { // + albCount
            Myexit = true;
        }
        /* clean up the database result set */
        mysql_free_result(res);
        /* clean up the database link */
        mysql_close(conn);
    }
    return vidDirMenuID;
}

int mysqlconn::connectArtMenu() {


    int audMenuID = 0, artMenuID = 0, QryCount = 0, menu = 0, artMenu = 0;
    bool Myexit = false; // exit variable

    char *myQry = NULL;

    MYSQL *conn = NULL; // the connection
    MYSQL_RES *res = NULL; // the results
    MYSQL_ROW row = NULL; // the results row (line by line)

    while (Myexit != true) {

        if (!myQry) {
            myQry = new char[MAXQRY];
        }

        // connect to the mysql database
        conn = mysql_connection_setup(mysqlD);

        /// use root to query for the Main menu's (audio + video)
        if (QryCount == 0) {
            sprintf(myQry, "SELECT * FROM mt_cds_object WHERE parent_id = %d",
                    0);
        }

        /// use audio menu ID to get Artist Menu ID
        else if (QryCount == 1) {
            sprintf(myQry, "SELECT * FROM mt_cds_object WHERE parent_id = %d",
                    audMenuID);
        }
        res = mysql_perform_query(conn, myQry);

        while ((row = mysql_fetch_row(res)) != NULL) {

            ///////*****  Query for MAIN root menu
            if (atoi(row[2]) == 0 && QryCount == 0) {
                menu++;
                if (menu == 1) {
                    audMenuID = atoi(row[0]);
                    //	cout << audMenuID << endl;
                }
            }

            //check for Audio menus
            else if (atoi(row[2]) == audMenuID) {
                artMenu++;
                //set ID of artist sub Menu
                if (artMenu == 4) {
                    artMenuID = atoi(row[0]);
                }
            }

        }
        QryCount++;
        if (QryCount > 3) { // + albCount
            Myexit = true;
        }
        mysql_free_result(res);
        mysql_close(conn);
    }
    return artMenuID;
}

mysqlconn::~mysqlconn() {

}
