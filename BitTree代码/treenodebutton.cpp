#include "treenodebutton.h"
#include <QDebug>
TreeNodeButton::TreeNodeButton(double radius,QString imgPath)
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
}
 void TreeNodeButton::mousePressEvent(QMouseEvent *e)
 {
     if (!active)
         return ;

     return QPushButton::mousePressEvent(e);
 }
