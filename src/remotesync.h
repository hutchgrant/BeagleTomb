#ifndef REMOTESYNC_H
#define REMOTESYNC_H

#include "prefobj.h"
#include "fileobj.h"
#include <QtSql>

class remotesync
{
#define MAXQRY 100


public:
    prefObj pref;
    QSqlDatabase db;

    remotesync();

    void setPref(prefObj &src);

    void openDB();

    void closeDB();
    void Fill(fileObj &Artist, fileObj &Album, fileObj &Song, fileObj &VidDir, fileObj &Video);

    int getAudioMenu();

    int getVideoMenu();

    void connectTracks(fileObj &folder, fileObj &src, int lookID, int mode);

    virtual ~remotesync();

};

#endif // REMOTESYNC_H
