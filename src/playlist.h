#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QWidget>
#include <QStringListModel>
#include "fileobj.h"
#include "dbconnect.h"
#include "newplaylist.h"
namespace Ui {
class playlist;
}

class playlist : public QWidget
{
    Q_OBJECT
    
public:

    dbconnect dbCon;
    fileObj playlists, playlistItems, newPList;
    newplaylist newplDg;
    int *curPLlist;
    int plSelected, playlistSelected;     /// items and playlists index selected
    int PLMODE;         /// current playlist mode: 0) playlists 1) playlist items
    string newPLName;   ///  name for new playlist
    int newItemCount;   /// counter for items in new playlist
    string tempPLName, tempPLPath;
    int tempPLID, tempPLPar;
    int lastPlaylistID;

    explicit playlist(QWidget *parent = 0);
    ~playlist();
    void initCueID(int initial, int newsize);
    void createPLTable();
    void writeNew(int type);
    void removePL(int type);
    void createNewPL();
    void fillPL();
    bool readPL();
    void AddToPL(){
        if(newItemCount == 0){
            newPList.initFile(100);
        }
        dbCon.getLastIDs(&lastPlaylistID);
        newPList.set(newItemCount, tempPLID, lastPlaylistID, tempPLName.c_str(), tempPLPath.c_str());
        newItemCount++;
    }

public slots:

    void AddToTempPL(string tempName, string tempPath, int tempID, int tempPar){
        tempPLName = tempName;
        tempPLPath = tempPath;
        tempPLID = tempID;
        tempPLPar = tempPar;
    }


signals:
    void playlistChanged(fileObj &plItem, int * plItemList);
    void playlistSelection(int selected);
    void playlistFullSelection(int selected);
private slots:

    void on_PLAYLIST_doubleClicked(const QModelIndex &index);

    void on_PLAYLIST_clicked(const QModelIndex &index);

    void on_open_tool_clicked();

    void on_add_tool_clicked();

    void on_remove_tool_clicked();

private:
    Ui::playlist *ui;
    QStringListModel *pl_model;

};

#endif // PLAYLIST_H
