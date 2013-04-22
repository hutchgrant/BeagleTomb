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


#ifndef VOLUME_H
#define VOLUME_H

#include <QWidget>
#include <QPainter>
namespace Ui {
class volume;
}

class volume : public QWidget
{
    Q_OBJECT
    
public:
    explicit volume(QWidget *parent = 0);
    ~volume();
    
private slots:
    void on_volSlider_sliderMoved(int position);

signals:
    void volChanged(int);
protected:
    void paintEvent(QPaintEvent * /* Event */ );

private:
    Ui::volume *ui;

    int curVol;

};

#endif // VOLUME_H
