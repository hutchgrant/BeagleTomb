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

#include "newplaylist.h"
#include "ui_newplaylist.h"

newplaylist::newplaylist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newplaylist)
{

    ui->setupUi(this);
     pref.readDB();
    ui->PLNAME_entry->setText(pref.getPlaylistDir().c_str());
}

/*
 *  CLEANUP
*/
newplaylist::~newplaylist()
{
    delete ui;
}

/*
 *  When save button in dialog is clicked
*/
void newplaylist::on_buttonBox_accepted()
{

}

bool newplaylist::plExists(){
    string p_locate, p_file;
    size_t lastSlash;
    string fullLocate;
    fullLocate = ui->PLNAME_entry->text().toStdString();
    /// strip playlist for location and file name
   lastSlash = fullLocate.find_last_of("/\\");
   p_locate = fullLocate.substr(0, lastSlash);
   p_file = fullLocate.substr(lastSlash+1);
  if(locationExists(p_locate)){

    PL_LOCATE = p_locate;
    //  if(!fileExists(p_file, p_locate)){
          PL_FILE = p_file;

        return true;
 //      }
  }
  return false;
}

bool newplaylist::locationExists(string p_locate){

    if(QDir(p_locate.c_str()).exists()){
        return true;
    }
    return true;
}

bool newplaylist::fileExists(string file, string location){
FILE* fp;
fp = NULL;
char *FinalFile;
FinalFile = new char[200];
sprintf(FinalFile,"%c%c", location.c_str(),file.c_str());
fp = fopen(FinalFile, "r");
if(fp){
    fclose(fp);
    return true;
}
return false;


}
