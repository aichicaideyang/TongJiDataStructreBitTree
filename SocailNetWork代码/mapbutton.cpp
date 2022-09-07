#include "mapbutton.h"
#include <QDebug>
MapButton::MapButton(int x,int y,QString info_txt,double radius,QString imgPath)
{

    QPixmap pix;
    bool ret=pix.load(imgPath);
    if (!ret)
    {
        qDebug()<<"图片加载失败";
        return;
    }
    this->setFixedSize(pix.width()*radius,pix.height()*radius);
    this->setStyleSheet("QPushButton{border:0px}");

    //设置图标
    this->setIcon(pix);
    //设置图标大小
    this->setIconSize(QSize(pix.width()*radius,pix.height()*radius));
   // qDebug()<<"x is "<<x<<"y is"<<y;
    x=(x-this->width())*0.5;
   // qDebug()<<"x is "<<x<<"y is"<<y;
    info=new QLabel();
    info->setText(info_txt);
    info->resize(150,50);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(12);
    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::blue);
    info->setFont(font);
    info->setPalette(pe);
    info->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    /*this->normalImgPath=imgPath;
    QPixmap pix;
    bool ret=pix.load(imgPath);
    if (!ret)
    {
        qDebug()<<"图片加载失败";
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px}");

    //设置图标
    this->setIcon(pix);
    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));*/

}
 void MapButton::mousePressEvent(QMouseEvent *e)
 {
     if (!active)
         return ;

     return QPushButton::mousePressEvent(e);
 }

 MapButton::~MapButton()
 {
     if (info!=NULL)
         delete info;

 }
