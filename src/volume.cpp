#include "volume.h"
#include "ui_volume.h"
#include <QPainter>
volume::volume(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::volume)
{
    ui->setupUi(this);
    curVol = 50;
}

volume::~volume()
{
    delete ui;
}

void volume::on_volSlider_sliderMoved(int position)
{
    if(position <= 0 ){
        curVol = 0;
    }
    else if(position >= 99){
        curVol = 100;
    }
    else if(curVol == position){
        return;
    }
    else{
        curVol = position;
    }
    update();
    emit volChanged(curVol);
}

void volume::paintEvent(QPaintEvent * /* Event */ ){

    if(curVol > 60){
        QPainter paint2(this);
        paint2.setPen(Qt::NoPen);
        paint2.setBrush(Qt::red);
        paint2.translate(0,rect().height()-20);
        paint2.drawRect(QRect(40, 0, 50, 10));
    }
    if(curVol > 40){
        QPainter paint3(this);
        paint3.setPen(Qt::NoPen);
        paint3.setBrush(QColor(70, 150, 179, 200));
        paint3.translate(0, rect().height()-20);
        paint3.drawRect(QRect(30, 0, 40, 10));
    }
    if(curVol > 20){
        QPainter paint2(this);
        paint2.setPen(Qt::NoPen);
        paint2.setBrush(Qt::blue);
        paint2.translate(0,rect().height()-20);
        paint2.drawRect(QRect(20, 0, 30, 10));
    }
    if(curVol > 10){
        QPainter paint3(this);
        paint3.setPen(Qt::NoPen);
        paint3.setBrush(QColor(70, 150, 179, 200));
        paint3.translate(0, rect().height()-20);
        paint3.drawRect(QRect(10, 0, 20, 10));
    }
}
