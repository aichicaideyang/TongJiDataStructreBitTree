#include "showsortfriendwindow.h"
#include <QPainter>
#include <QDebug>
#include "mapbutton.h"
#include "math.h"
ShowSortFriendWindow::ShowSortFriendWindow(QString now_user,QVector<QPair< QString,int>> &friends)
{
    this->setFixedSize(1280,800);
    setWindowIcon(QIcon(":/src/Icon.png"));
    setWindowTitle(QString("用户:%1 潜在好友分布图").arg(now_user));
    this->friends=friends;
    MapButton *center_btn=new MapButton(this->width(),this->height()*.1,now_user);
    //qDebug()<<"radius is"<<radius;
    center_btn->setParent(this);
    //btn->setText(QString::number(k));
    //btn->setStyleSheet("QPushButton{border:0px;}");
    center_btn->move((this->width()-center_btn->width())*0.5,this->height()*0.5);
    center_btn->show();
    center_btn->info->setParent(this);
    center_btn->info->move(this->width()*0.5+center_btn->width()*0.5,this->height()*0.5);
    center_btn->info->show();
    //qDebug()<<"btn x is"<<center_btn->x()<<"y is"<<center_btn->y();
    //qDebug()<<"btn->info x is"<<center_btn->info->x()<<"y is"<<center_btn->info->y();
    base_x=(this->width()-center_btn->width())*0.5;
    base_y=this->height()*0.5;
    btn_size=center_btn->width();
    //分级画圆，超过5级的直接扔最后

    if (!friends.empty())
    {
        //开始分级
        rank_cnt=0;
        int pre_score=-1;
        for (auto &f:friends)
        {
            if (rank_cnt<5)
            {
            if (f.second!=pre_score)
            {
                pre_score=f.second;
                rank_cnt++;
                rank_friends[rank_cnt].push_back(f.first);
            }
            else
                rank_friends[rank_cnt].push_back(f.first);
            }
            else
            {
                //超过5级
                rank_friends[rank_cnt].push_back(f.first);
            }
        }
        //按每层分级画结点
        const int radius=this->height()*0.1;//半径
        const double pi=3.14159;//pi
        for (int i=1;i<=rank_cnt;i++)
        {
            //从内往外画

            double average=180.0/(rank_friends[i].size()+1);
            int paint_idx=1;
            for(auto &f:rank_friends[i])
            {
                //计算出当前坐标
                double nx=base_x+radius*cos(paint_idx*average/180*pi)*i;
                double ny=base_y-radius*sin(paint_idx*average/180*pi)*i;
                QString friend_user_name=f;
                MapButton *friend_btn=new MapButton(nx,ny,friend_user_name);
                //qDebug()<<"radius is"<<radius;
                friend_btn->setParent(this);
                //btn->setText(QString::number(k));
                //btn->setStyleSheet("QPushButton{border:0px;}");
                friend_btn->move(nx,ny);
                friend_btn->show();
                friend_btn->info->setParent(this);
                friend_btn->info->move(nx+friend_btn->width(),ny);
                friend_btn->info->show();
               // qDebug()<<"btn x is"<<friend_btn->x()<<"y is"<<friend_btn->y();
                 //qDebug()<<"btn->info x is"<<friend_btn->info->x()<<"y is"<<friend_btn->info->y();
                paint_idx++;
            }
        }




    }


}

void ShowSortFriendWindow::paintEvent(QPaintEvent *)
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

     //下面画线

     if (!friends.empty())
     {
         //开始分级
         const int radius=this->height()*0.1;//半径
         const double pi=3.14159;//pi
         for (int i=1;i<=rank_cnt;i++)
         {
             //从内往外画
             double average=180.0/(rank_friends[i].size()+1);
             int paint_idx=1;
             for(auto &f:rank_friends[i])
             {
                 //计算出当前坐标
                 double nx=base_x+radius*cos(paint_idx*average/180*pi)*i;
                 double ny=base_y-radius*sin(paint_idx*average/180*pi)*i;
                 painter.drawLine(base_x+btn_size*0.5,base_y+btn_size*0.5,nx+btn_size*0.5,ny+btn_size*0.5);
                 paint_idx++;
             }
         }

         QColor colors[6];
         colors[1].setRgb(249,24,7);
         colors[2].setRgb(227,235,21);
         colors[3].setRgb(146,229,27);
         colors[4].setRgb(32,59,224);
         colors[5].setRgb(131,32,224);
         for (int i=1;i<=rank_cnt;i++)
        {
           pen.setColor(colors[i]);
           pen.setStyle(Qt::DashDotDotLine);
           painter.setPen(pen);

           painter.drawEllipse(base_x+btn_size*0.5-radius*i,base_y+btn_size*0.5-radius*i,radius*i*2,radius*i*2);


        }
         //下面画圆


     }

}

