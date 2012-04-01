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

#ifndef OPENPLAYLIST_H
#define OPENPLAYLIST_H

#include <QDialog>
#include <sys/stat.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <QDir>
#include <fstream>
#include "preferences.h"
using namespace std;
namespace Ui {
    class openplaylist;
}

class openplaylist : public QDialog
{
    Q_OBJECT

public:
    string PL_FILE;
    string PL_LOCATE;

    preferences pref;

    explicit openplaylist(QWidget *parent = 0);
    virtual ~openplaylist();
    void checkPLlocation(string p_locate);
    void checkPLexists(string p_locate);
    bool plExists();
    bool locationExists(string p_locate);
    bool fileExists(string p_locate, string p_file);
    string getFile(){
        return PL_FILE;
    }
    string getLocate(){
        return PL_LOCATE;
    }

private:
    Ui::openplaylist *ui;
};

#endif // OPENPLAYLIST_H
