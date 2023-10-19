#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QImage>
#include <iostream>
#include <QMouseEvent>
#include <QPainter>
#include <QPaintDevice>
#include <QPoint>
#include <QTimer>
#include <QElapsedTimer>
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <set>
#include <cmath>
#include <unistd.h>
#include <QKeyEvent>
#include <QDebug>
using namespace std;
QImage img=QImage(700,700,QImage::Format_RGB888);
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->x_axis->hide();
    ui->y_axis->hide();
    connect(ui->frame,SIGNAL(Mouse_Pos()),this,SLOT(Mouse_Pressed()));
    connect(ui->frame,SIGNAL(sendMousePosition(QPoint&)),this,SLOT(showMousePosition(QPoint&)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::point(int x,int y)
{

    img.setPixel(x,y,qRgb(255,255,0));
    ui->frame->setPixmap(QPixmap::fromImage(img));
}


void MainWindow::showMousePosition(QPoint &pos)
{
    ui->mouse_movement->setText(" X : "+QString::number(pos.x())+", Y : "+QString::number(pos.y()));
}
void MainWindow::Mouse_Pressed()
{
    ui->mouse_pressed->setText(" X : "+QString::number(ui->frame->x)+", Y : "+QString::number(ui->frame->y));
    point(ui->frame->x,ui->frame->y);
    ui->x_axis->move(0,ui->frame->y);
    ui->y_axis->move(ui->frame->x,0);
}

void MainWindow::on_show_axes_clicked()
{
    if(ui->show_axes->isChecked())
    {
        ui->x_axis->show();
        ui->y_axis->show();
    }
    else{
        ui->x_axis->hide();
        ui->y_axis->hide();
    }
}
void MainWindow::on_set_point1_clicked()
{
    if(ui->draw_line->isChecked()){
        p1.setX(ui->frame->x);
        p1.setY(ui->frame->y);
    }
}

void MainWindow::on_set_point2_clicked()
{
    if(ui->draw_line->isChecked()){
        p2.setX(ui->frame->x);
        p2.setY(ui->frame->y);
    }
}


void MainWindow::on_pushButton_clicked()
{
    for(int j=0;j<img.height();j++)
    {
        for(int i=0;i<img.width();i++)
        {
            img.setPixel(i,j,qRgb(0,0,0));
        }
    }
    ui->frame->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_grid_clicked()
{
    QPainter painter(&img);
    int w = img.width();
    int gs=25;
    //    int gs=10;

    for(int i=0;i<img.height();i+=gs){
        p1.setX(0);
        p1.setY(i);
        p2.setX(w);
        p2.setY(i);
        painter.setPen(Qt::blue);
        painter.drawLine(p1,p2);
    }

    int h = img.height();
    for(int i=0;i<img.width();i+=gs){
        p1.setX(i);
        p1.setY(0);
        p2.setX(i);
        p2.setY(h);
        painter.setPen(Qt::blue);
        painter.drawLine(p1,p2);
    }
    ui->frame->setPixmap(QPixmap::fromImage(img));
}
vector<pair<int,int>> pacPoints;
void MainWindow::setColor(int x,int y,int a,int b,int c){
    pacPoints.push_back({x,y});
    img.setPixel(x,y,qRgb(a,b,c));
    ui->frame->setPixmap(QPixmap::fromImage(img));
}
void MainWindow::fillColor(int x,int y,int a,int b,int c){
    cout<<x<<" "<<y<<endl;
    img.setPixel(x,y,qRgb(a,b,c));
    ui->frame->setPixmap(QPixmap::fromImage(img));
}
void MainWindow::boundaryFill(int x,int y,QColor boundaryColor,QColor fillColor){
    if(x>=0 && x<=700 && y>=0 && y<=700){
        int val=25;
        QColor currColor=img.pixelColor(x,y);
        if(currColor!=boundaryColor && currColor!=fillColor){
            setColor(x,y,255,255,0);
            boundaryFill(x+1,y,boundaryColor,fillColor);
            boundaryFill(x,y+1,boundaryColor,fillColor);
            boundaryFill(x-1,y,boundaryColor,fillColor);
            boundaryFill(x,y-1,boundaryColor,fillColor);
        }
    }
}
void MainWindow::boundaryFill(int x,int y){
    int val=25;
    QColor s=QColor("Yellow");
    QColor c=QColor("Red");
    boundaryFill(x+1,y,s,c);
    boundaryFill(x,y+1,s,c);
    boundaryFill(x-1,y,s,c);
    boundaryFill(x,y-1,s,c);
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    char ch=(char) event->key();
    int val=25;
    if(ch=='S'){
        for(int i=0;i<pacPoints.size();i++){
            fillColor(pacPoints[i].first,pacPoints[i].second,0,0,0);
            fillColor(pacPoints[i].first,pacPoints[i].second+val,255,255,0);
            pacPoints[i].second+=val;
        }
    }
    else if(ch=='W'){
        for(int i=0;i<pacPoints.size();i++){
            fillColor(pacPoints[i].first,pacPoints[i].second,0,0,0);
            fillColor(pacPoints[i].first,pacPoints[i].second-val,255,255,0);
            pacPoints[i].second-=val;
        }
    }
    else if(ch=='A'){
        for(int i=0;i<pacPoints.size();i++){
            fillColor(pacPoints[i].first,pacPoints[i].second,0,0,0);
            fillColor(pacPoints[i].first-val,pacPoints[i].second,255,255,0);
            pacPoints[i].first-=val;
        }
    }
    else if(ch=='D'){
        for(int i=0;i<pacPoints.size();i++){
            fillColor(pacPoints[i].first,pacPoints[i].second,0,0,0);
            fillColor(pacPoints[i].first+val,pacPoints[i].second,255,255,0);
            pacPoints[i].first+=val;
        }
    }
}

void MainWindow::on_pacman_clicked()
{
    int val=25;
    int centerX=val/2;
    int centerY=val/2;
    int radius=8;
    int y=radius;
    int x=0;
    int d=3-2*radius;
    while(x<=y){
        setColor(centerX + x, centerY + y,255,255,0);
        setColor(centerX - x, centerY + y,255,255,0);
        setColor(centerX + x, centerY - y,255,255,0);
        setColor(centerX - x, centerY - y,255,255,0);
        setColor(centerX + y, centerY + x,255,255,0);
        setColor(centerX - y, centerY + x,255,255,0);
        setColor(centerX + y, centerY - x,255,255,0);
        setColor(centerX - y, centerY - x,255,255,0);
        x++;
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }
    }
    boundaryFill(centerX,centerY);
}


