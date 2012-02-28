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


#include "readDB.h"

readDB::readDB(const char *dbLocation) {
    DBlocation2 = new char[strlen(dbLocation) + 1];
    strcpy(DBlocation2, dbLocation);

    Artist = new songObj[MAX];
    for(int i = 0; i<= MAX; i++){
        Artist[i].set("-",0,0);
    }

    Album = new songObj[MAX];
    for(int i = 0; i<= MAX; i++){
        Album[i].set("-",0,0);
    }
    Song = new songObj[MAX];
    for(int i = 0; i<= MAX; i++){
        Song[i].set("-", 0, 0);
    }
    VidDir = new songObj[MAX];
    for(int i = 0; i<= MAX; i++){
        VidDir[i].set("-", 0, 0);
    }
    Video = new songObj[MAX];
    for(int i = 0; i<= MAX; i++){
        Video[i].set("-", 0, 0);
    }
}
songObj* readDB::SongFill(int *songSize){

    int count = 0;
    Database *db;
    db = new Database(DBlocation2);
    vector<vector<string> > result = db->query("SELECT * FROM songs;");
    for(vector<vector<string> >::iterator it = result.begin(); it < result.end() ; ++it)
    {
        vector<string> row = *it;
        string str = "", str2, str3;
        char *cStr = "\0";
        str = row.at(1);
        str2 = row.at(2);
        str3 = row.at(3);
        cStr = new char[str.size()];
        cStr = (char*)str.c_str();

        if(atoi(str2.c_str()) != 0){
            Song[count].set(cStr, atoi(str2.c_str()), atoi(str3.c_str()));
            count++;
        }
    }
    *songSize = count;
    return Song;
}
songObj* readDB::AlbumFill(int *albSize){

    int count = 0;
    Database *db;
    db = new Database(DBlocation2);
    vector<vector<string> > result = db->query("SELECT * FROM albums;");
    for(vector<vector<string> >::iterator it = result.begin(); it < result.end() ; ++it)
    {
        vector<string> row = *it;
        string str = "", str2, str3;
        char *cStr = "\0";
        str = row.at(1);
        str2 = row.at(2);
        str3 = row.at(3);
        cStr = new char[str.size()];
        cStr = (char*)str.c_str();

        if(atoi(str2.c_str()) != 0){
            Album[count].set(cStr, atoi(str2.c_str()), atoi(str3.c_str()));
            count++;
        }
    }
    *albSize = count;
    return Album;
}

songObj* readDB::ArtistFill( int *artSize){

    int count = 0;
    Database *db;
    db = new Database(DBlocation2);
    vector<vector<string> > result = db->query("SELECT * FROM artists;");
    for(vector<vector<string> >::iterator it = result.begin(); it < result.end() ; ++it)
    {
        vector<string> row = *it;
        string str = "", str2, str3;
        char *cStr = "\0";
        str = row.at(1);
        str2 = row.at(2);
        str3 = row.at(3);
        cStr = new char[str.size()];
        cStr = (char*)str.c_str();

        if(atoi(str2.c_str()) != 0){
            Artist[count].set(cStr, atoi(str2.c_str()), atoi(str3.c_str()));
            count++;
        }
    }
    *artSize = count;
    return Artist;
}
songObj* readDB::VidDirFill( int *vidDirSize){

    int count = 0;
    Database *db;
    db = new Database(DBlocation2);
    vector<vector<string> > result = db->query("SELECT * FROM viddirs;");
    for(vector<vector<string> >::iterator it = result.begin(); it < result.end() ; ++it)
    {
        vector<string> row = *it;
        string str = "", str2, str3;
        char *cStr = "\0";
        str = row.at(1);
        str2 = row.at(2);
        str3 = row.at(3);
        cStr = new char[str.size()];
        cStr = (char*)str.c_str();

        if(atoi(str2.c_str()) != 0){
            VidDir[count].set(cStr, atoi(str2.c_str()), atoi(str3.c_str()));
            count++;
        }
    }
    *vidDirSize = count;
    return VidDir;
}
songObj* readDB::VideoFill( int *vidSize){

    int count = 0;
    Database *db;
    db = new Database(DBlocation2);
    vector<vector<string> > result = db->query("SELECT * FROM videos;");
    for(vector<vector<string> >::iterator it = result.begin(); it < result.end() ; ++it)
    {
        vector<string> row = *it;
        string str = "", str2, str3;
        char *cStr = "\0";
        str = row.at(1);
        str2 = row.at(2);
        str3 = row.at(3);
        cStr = new char[str.size()];
        cStr = (char*)str.c_str();

        if(atoi(str2.c_str()) != 0){
            Video[count].set(cStr, atoi(str2.c_str()), atoi(str3.c_str()));
            count++;
        }
    }
    *vidSize = count;
    return Video;
}

radioObj readDB::RadioFill(int *radSize){

    int count = 0;
    Database *db;
    db = new Database(DBlocation2);
    vector<vector<string> > result = db->query("SELECT * FROM radio;");
    for(vector<vector<string> >::iterator it = result.begin(); it < result.end() ; ++it)
    {
        vector<string> row = *it;
        string r_name, r_url;
        r_name = row.at(1);
        r_url = row.at(2);

        if(r_name != "" && r_name != "-"){
            play_list.Add(r_name, r_url);
            count++;
        }
    }
    *radSize = count;
    return play_list;


}

void readDB::display(int artSize, int albSize, int songSize){
    int choice = 0;
    bool Exit = 0;
    while(!Exit){
        cout << endl;
	cout << "Which do you want to display?" << endl;
	cout << "1)Artists 2) Albums 3)Songs 4) exit" << endl;
	cin >> choice;

	if(choice == 1){
            for(int i = 0; i<=artSize; i++){
                cout << Artist[i];
            }
            cout << "total artists: " << artSize;
	}
	if(choice == 2){
            for(int i = 0; i<=albSize; i++){
                cout << Album[i];
            }
            cout << "Total Albums: " << albSize;
	}
	if(choice == 3){
            for(int i = 0; i<=songSize; i++){
                cout << Song[i];
            }
            cout << "Total Songs: " << songSize;
	}
	if(choice == 4){
            Exit = 1;
	}
    }
}
readDB::~readDB() {
    // TODO Auto-generated destructor stub
    delete [] DBlocation2;
}
