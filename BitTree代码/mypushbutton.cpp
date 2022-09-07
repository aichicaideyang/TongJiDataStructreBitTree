#include "mypushbutton.h"
#include <QDebug>
#include <qpropertyanimation.h>
MyPushButtton::MyPushButtton(QString normalImg,QString pressImg)
{
    this->normalImgPath=normalImg;
    this->pressImgPath=pressImg;

    QPixmap pix;
    bool ret=pix.load(normalImg);
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
    this->setIconSize(QSize(pix.width(),pix.height()));

}
void MyPushButtton::zoom1()
{
    QPropertyAnimation *animation= new QPropertyAnimation(this,"geometry");
    //设置时间间隔
    animation->setDuration(200);


    //设置起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置结束位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();

}
void MyPushButtton::zoom2()
{
    QPropertyAnimation *animation= new QPropertyAnimation(this,"geometry");
    //设置时间间隔
    animation->setDuration(200);


    //设置起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //设置结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();

}
void MyPushButtton::mousePressEvent(QMouseEvent *e)
{
    if(this->pressImgPath !="")
    {

        QPixmap pix;
        bool ret=pix.load(pressImgPath);
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
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    return QPushButton::mousePressEvent(e);
}
void MyPushButtton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->pressImgPath !="")
    {

        QPixmap pix;
        bool ret=pix.load(normalImgPath);
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
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    return QPushButton::mouseReleaseEvent(e);


}
