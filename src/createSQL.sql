create table Artists(key INTEGER PRIMARY KEY,Artist TEXT,ArtistID integer, ArtistPar integer);
create table Albums(key INTEGER PRIMARY KEY,Album TEXT,AlbumID integer, AlbumPar integer);
create table Songs(key INTEGER PRIMARY KEY,Song TEXT,SongID integer, SongPar integer);
create table Videos(key INTEGER PRIMARY KEY,Video TEXT,VideoID integer, VideoPar integer);
create table VidDirs(key INTEGER PRIMARY KEY,VidDir TEXT,VidDirID integer, VidDirPar integer);
create table pref(key INTEGER PRIMARY KEY,usr TEXT,PASS TEXT,SERVER TEXT,PRT TEXT,SQLTABLE TEXT,SQL TEXT,PLAYLISTDIR TEXT);
CREATE TABLE "radio" ("id" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL DEFAULT (0),"name" TEXT NOT NULL,"url" TEXT NOT NULL);
