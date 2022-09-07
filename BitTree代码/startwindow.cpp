#include "startwindow.h"
#include "mypushbutton.h"
#include <QPushButton>
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QLabel>
StartWindow::StartWindow()
{
    this->setFixedSize(1280,800);
    QPixmap icon;
    icon.load(":/src/Icon.png");
    this->setWindowIcon(icon);
    this->setWindowTitle("欢迎界面");
    QLabel *label=new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(30);
    QString strr=QString("欢迎使用本软件");
    label->setFont(font);
    label->setText(strr);
    //label->setAlignment(Qt::AlignHCenter);
    label->setGeometry((this->width()-strr.size())/3,120,this->width(),50);
    QString strr1=QString("请按START键进入主程序");
    QLabel *label1=new QLabel;
    label1->setParent(this);
    QFont font1;
    font1.setFamily("华文新魏");
    font1.setPointSize(30);
    label1->setFont(font);
    label1->setText(strr1);
    label1->setGeometry((this->width()-strr1.size())/3-100,200,this->width(),50);
    //label1->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    //bitTreeMainWindow->show();
    MyPushButtton * startBtn=new MyPushButtton (":/src/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);

    connect(startBtn,&QPushButton::clicked,[=](){
        startBtn->zoom1();
        startBtn->zoom2();
        QTimer::singleShot(500,this,[=](){

            bitTreeMainWindow=new BitTreeMainWindow();
            bitTreeMainWindow->setGeometry(this->geometry());
            this->hide();
            bitTreeMainWindow->show();

        });
    });
    /*
    connect(bitTreeMainWindow,&BitTreeMainWindow::reStart,[=]()
    {
            qDebug()<<"here it is";
            bitTreeMainWindow->hide();
            BitTreeMainWindow *next=new BitTreeMainWindow();
            BitTreeMainWindow::update(next,bitTreeMainWindow);
            //next->T=bitTreeMainWindow->T;
            delete bitTreeMainWindow;
            bitTreeMainWindow=next;

            bitTreeMainWindow->setGeometry(this->geometry());

            bitTreeMainWindow->show();

    });*/

}
void StartWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/src/bg.jpg");
    //qDebug()<<pix;
    //pix=pix.scaled(pix.width()*0.2,pix.height()*0.2);
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
