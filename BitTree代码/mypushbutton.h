#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButtton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButtton(QWidget *parent = nullptr);
    MyPushButtton(QString normalImg,QString pressImg="");
    QString normalImgPath;
    QString pressImgPath;

    void zoom1();
    void zoom2();

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);


signals:

};

#endif // MYPUSHBUTTON_H
