#ifndef NEWPLAYLIST_H
#define NEWPLAYLIST_H

#include <QDialog>

using namespace std;
namespace Ui{
    class newplaylist;
}
class newplaylist : public QDialog
{
    Q_OBJECT

public:


    string plName;

    explicit newplaylist(QWidget *parent = 0);
    virtual ~newplaylist();


    string getName(){
        return plName;
    }

private slots:
    void on_playlist_accept_accepted();

private:
    Ui::newplaylist *ui;
};

#endif // NEWPLAYLIST_H
