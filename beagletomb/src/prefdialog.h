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


#ifndef PREFDIALOG_H
#define PREFDIALOG_H
#include <QDialog>
#include "Database.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include "preferences.h"
namespace Ui {
    class PrefDialog;
}

class PrefDialog : public QDialog
{
    Q_OBJECT

public:
    preferences pref;
    explicit PrefDialog(QWidget *parent = 0);
    preferences& setPreferences(preferences& pref2);
    void setPref(preferences& my_pref);
    bool exists(const char *str);
    preferences getPref();
    virtual ~PrefDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::PrefDialog *ui;
};

#endif // PREFDIALOG_H
