#include "showgroupuserwindow.h"
#include <QPainter>
#include "mapbutton.h"
#include <QDebug>
#include <math.h>
ShowGroupUserWindow::ShowGroupUserWindow(QString now_group,QSet<QString> &users)
{
    this->setFixedSize(800,640);
    setWindowIcon(QIcon(":/src/Icon.png"));
    setWindowTitle(QString("组织:%1 成员图").arg(now_group));
    this->users=users;
    MapButton *center_btn=new MapButton(this->width(),this->height()*.1,now_group,1,":/src/Coin0008.png");
    //qDebug()<<"radius is"<<radius;
    center_btn->setParent(this);
    //btn->setText(QString::number(k));
    //btn->setStyleSheet("QPushButton{border:0px;}");
    center_btn->move((this->width()-center_btn->width())*0.5,this->height()*0.1);
    center_btn->show();
    center_btn->info->setParent(this);
    center_btn->info->move(this->width()*0.5+center_btn->width()*0.5,this->height()*0.1);
    center_btn->info->show();
    //qDebug()<<"btn x is"<<center_btn->x()<<"y is"<<center_btn->y();
    //qDebug()<<"btn->info x is"<<center_btn->info->x()<<"y is"<<center_btn->info->y();

    //上方是他的好友
    //点击好友，查看好友的好友

    //下面开始画好友
    const int radius=this->height()*0.3;//半径

    const double pi=3.14159;//pi
    int user_nums=users.size()+1;
    double average=180.0/user_nums;
    base_x=(this->width()-center_btn->width())*0.5;
    base_y=this->height()*0.1;
    btn_size=center_btn->width();
    int paint_idx=1;
    for(auto &f:users)
    {
        //计算出当前坐标
        double nx=base_x+radius*cos(paint_idx*average/180*pi);
        double ny=base_y+radius*sin(paint_idx*average/180*pi);
        MapButton *user_btn=new MapButton(nx,ny,f);
        //qDebug()<<"radius is"<<radius;
        user_btn->setParent(this);
        //btn->setText(QString::number(k));
        //btn->setStyleSheet("QPushButton{border:0px;}");
        user_btn->move(nx,ny);
        user_btn->show();
        user_btn->info->setParent(this);
        user_btn->info->move(nx+user_btn->width(),ny);
        user_btn->info->show();
       // qDebug()<<"btn x is"<<user_btn->x()<<"y is"<<user_btn->y();
        //qDebug()<<"btn->info x is"<<user_btn->info->x()<<"y is"<<user_btn->info->y();
        paint_idx++;
    }



}
void ShowGroupUserWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);
    QPixmap pix;
    pix.load(":/src/bg.jpg");
    //qDebug()<<pix;
    //pix=pix.scaled(pix.width()*0.2,pix.height()*0.2);
     painter.drawPixmap(0,0,this->width(),this->height(),pix);
     QColor color;
     color.setRgb(0,255,255,255);
     QPen pen;
     pen.setColor(QColor(55,240,251));
     pen.setWidth(4);
     painter.setPen(pen);
     const int radius=this->height()*0.3;//半径

     const double pi=3.14159;//pi
     int user_nums=users.size()+1;
     double average=180.0/user_nums;
     base_x=(this->width()-btn_size)*0.5;
     base_y=this->height()*0.1;
     int paint_idx=1;
     for(auto &f:users)
     {
         //计算出当前坐标
         double nx=base_x+radius*cos(paint_idx*average/180*pi);
         double ny=base_y+radius*sin(paint_idx*average/180*pi);
         painter.drawLine(base_x+btn_size*0.5,base_y+btn_size*0.5,nx+btn_size*0.5,ny+btn_size*0.5);
         paint_idx++;
     }

}
