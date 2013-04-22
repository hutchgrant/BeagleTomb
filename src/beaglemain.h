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

#ifndef BEAGLEMAIN_H
#define BEAGLEMAIN_H

#include <QMainWindow>
#include "browse.h"
#include "controls.h"
#include "playlist.h"
#include "about.h"
#include <QDesktopServices>
namespace Ui {
class beaglemain;
}

class beaglemain : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit beaglemain(QWidget *parent = 0);
    ~beaglemain();
    void addWidgets();
    void conSignals();
    void closeEvent(QCloseEvent *);

    
private slots:

    void on_actionImport_Video_triggered();

    void on_actionImport_triggered();

    void on_actionQuit_triggered();

    void on_actionPreferences_triggered();

    void on_actionDonate_triggered();

    void on_actionAbout_triggered();

    void on_actionEnable_remote_triggered();

    void on_actionSync_remote_triggered();

private:
    Ui::beaglemain *ui;
     browse *brow;
     controls *cntrl;
     playlist *plList;
     About ab;

     QStringListModel *m_ComboModel;
};
#endif // BEAGLEMAIN_H
