#include "socialnetworkmainwindow.h"
#include "ui_socialnetworkmainwindow.h"
#include <QDebug>
#include <QPainter>
#include <QInputDialog>
#include <math.h>
#include <QMessageBox>
#include "showgroupuserwindow.h"
#include "showuserfriendwindow.h"
#include "showsortfriendwindow.h"
SocialNetworkMainWindow::SocialNetworkMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SocialNetworkMainWindow)
{

    QApplication::setQuitOnLastWindowClosed(false);
    ui->setupUi(this);
    this->setFixedSize(1280,800);
    setWindowIcon(QIcon(":/src/Icon.png"));
    setWindowTitle("社会关系网络图");
    qDebug()<<"judge:"<<(socialMap==NULL);
    socialMap=new SocialMap();
    map_btn_size=0;
    map_btn_cnt=0;
    now_user_idx=1;

    /*
    if (socialMap==NULL)
    {
    socialMap=new SocialMap();
    //下面开始考虑如何画一个人的社会关系图
    socialMap->addUser("杨杨杨");
    socialMap->addUser("杨杨杨2号");
    socialMap->addUser("杨杨杨3号");
    socialMap->addUser("LALAL");
    socialMap->addFriend("杨杨杨2号","LALAL");
    socialMap->addFriend("杨杨杨","杨杨杨2号");
    socialMap->addFriend("杨杨杨","杨杨杨3号");
    socialMap->addGroup("同济大学");
    socialMap->addGroupMember("同济大学","杨杨杨");
    }*/
    if (socialMap->user_counts==0)
    {
        qDebug()<<"当前关系网络中无用户，请手动添加或导入文件";
    }
    else
    {
        now_user_idx=1;//第一个人
        paintBtn();
        /*
        QString now_user_name=socialMap->user_name_dict[now_user_idx];

        //中心是这个用户
        //点击用户查看用户可能认识的人
        //先画出这个结点
        MapButton *center_btn=new MapButton(this->width(),this->height()*0.5,now_user_name);
        //qDebug()<<"radius is"<<radius;
        map_btn[++map_btn_cnt]=center_btn;//记录下来好释放
        center_btn->setParent(this);
        //btn->setText(QString::number(k));
        //btn->setStyleSheet("QPushButton{border:0px;}");
        center_btn->move((this->width()-center_btn->width())*0.5,this->height()*0.5);
        center_btn->show();
        center_btn->info->setParent(this);
        center_btn->info->move(this->width()*0.5+center_btn->width()*0.5,this->height()*0.5);
        center_btn->info->show();
        qDebug()<<"btn x is"<<center_btn->x()<<"y is"<<center_btn->y();
         qDebug()<<"btn->info x is"<<center_btn->info->x()<<"y is"<<center_btn->info->y();
        connect(center_btn,&QPushButton::clicked,[=](){
            qDebug()<<"用户选择了查看当前用户可能认识的朋友";
            //this->close();
        });




        //上方是他的好友
        //点击好友，查看好友的好友

        //下面开始画好友
        const int radius=this->height()*0.3;//半径

        const double pi=3.14159;//pi

        int friend_nums=socialMap->user_friend[now_user_idx].size()+1;
        double average=180.0/friend_nums;
        base_x=(this->width()-center_btn->width())*0.5;
        base_y=this->height()*0.5;
        map_btn_size=center_btn->width();
        int paint_idx=1;
        for(auto &f:socialMap->user_friend[now_user_idx])
        {
            //计算出当前坐标
            double nx=base_x+radius*cos(paint_idx*average/180*pi);
            double ny=base_y-radius*sin(paint_idx*average/180*pi);
            QString friend_user_name=socialMap->user_name_dict[f];
            MapButton *friend_btn=new MapButton(nx,ny,friend_user_name);
            //qDebug()<<"radius is"<<radius;
            map_btn[++map_btn_cnt]=friend_btn;//记录下来好释放
            friend_btn->setParent(this);
            //btn->setText(QString::number(k));
            //btn->setStyleSheet("QPushButton{border:0px;}");
            friend_btn->move(nx,ny);
            friend_btn->show();
            friend_btn->info->setParent(this);
            friend_btn->info->move(nx+friend_btn->width(),ny);
            friend_btn->info->show();
            qDebug()<<"btn x is"<<friend_btn->x()<<"y is"<<friend_btn->y();
             qDebug()<<"btn->info x is"<<friend_btn->info->x()<<"y is"<<friend_btn->info->y();
            connect(friend_btn,&QPushButton::clicked,[=](){
                qDebug()<<QString("用户选择了当前的朋友%1").arg(f);
                //这里面要开一个新窗口，展示这个好友的所有的好友
                //this->close();
            });
            paint_idx++;
        }






        //下面是他的组织
        //点击组织，查看组织内的成员
        //下面开始画他的组织

        int group_nums=socialMap->user_group[now_user_idx].size()+1;
        average=180.0/group_nums;
        paint_idx=1;
        for(auto &f:socialMap->user_group[now_user_idx])
        {
            //计算出当前坐标
            double nx=base_x+radius*cos(paint_idx*average/180*pi);
            double ny=base_y+radius*sin(paint_idx*average/180*pi);
            QString group_user_name=socialMap->group_name_dict[f];
            MapButton *group_btn=new MapButton(nx,ny,group_user_name,1,":/src/Coin0008.png");
            //qDebug()<<"radius is"<<radius;
            map_btn[++map_btn_cnt]=group_btn;//记录下来好释放
            group_btn->setParent(this);
            //btn->setText(QString::number(k));
            //btn->setStyleSheet("QPushButton{border:0px;}");
            group_btn->move(nx,ny);
            group_btn->show();
            group_btn->info->setParent(this);
            group_btn->info->move(nx+group_btn->width(),ny);
            group_btn->info->show();
            qDebug()<<"btn x is"<<group_btn->x()<<"y is"<<group_btn->y();
             qDebug()<<"btn->info x is"<<group_btn->info->x()<<"y is"<<group_btn->info->y();
            connect(group_btn,&QPushButton::clicked,[=](){
                qDebug()<<QString("用户选择了当前的组织%1").arg(f);
                //这里面要开一个新窗口，展示这个组织的所有的成员
                //this->close();
            });
            paint_idx++;
        }*/
    }

    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });
    //返回初始页面


    //切换人员查看关系网络，一开始进入自动显示第一个人，如果没有人直接输出当前数据库为空！

    connect(ui->actionselectPerson,&QAction::triggered,[=](){
        qDebug()<<"点击了查看关系网络按钮";
        //这里是切换用户，需要重绘
        QStringList items;
         bool bRet = false;
        //这里需要先把所有人的信息存进去
        for (auto &u:socialMap->user_name_dict)
        {
            if (socialMap->get_user_index(u)!=now_user_idx)
                items<<u;
        }
        if (items.empty())
        {
            QMessageBox res_box(QMessageBox::Information,"提示",QString("请先添加一些用户再进行切换！"));
            res_box.exec();
        }
        else
        {
        QString item1 =  QInputDialog:: getItem(this, "切换用户",
                                      "请选择用户姓名", items, 0, true, &bRet, Qt::WindowFlags(), Qt::ImhHiddenText);
        if (bRet && !item1.isEmpty())
        {
            qDebug()<<"切换成功啦！";
            QMessageBox res_box(QMessageBox::Information,"成功",QString("切换至用户:%1").arg(item1));
            res_box.exec();
            now_user_idx=socialMap->get_user_index(item1);
            close_btn();
            paintBtn();

        }
        else
        {
            qDebug()<<"用户选择了取消";
        }
        }
    });

    connect(ui->actionaddPerson,&QAction::triggered,[=](){
        qDebug()<<"点击了添加人员按钮";
        bool bRet = false;
        QString add_user_name= QInputDialog:: getText(this, "添加用户",
                                                     "请输入用户姓名", QLineEdit::Normal, "", &bRet);
        if (bRet && !add_user_name.isEmpty())
        {
            qDebug()<<"输入的用户名为:"<<add_user_name;
            //这里要对用户是否已存在进行一下判断

            bool ok=(socialMap->user_index_dict.count(add_user_name)==0);
            if (ok)
            {
                qDebug()<<"添加用户成功";
                QMessageBox res_box(QMessageBox::Information,"成功",QString("已成功添加用户:%1！").arg(add_user_name));
                res_box.exec();
                socialMap->addUser(add_user_name);
            }
            else
            {
                qDebug()<<"添加用户失败";
                QMessageBox res_box(QMessageBox::Information,"失败",QString("用户:%1 已存在！").arg(add_user_name));
                res_box.exec();
            }
        }
    });

    connect(ui->actionaddFriend,&QAction::triggered,[=](){
        qDebug()<<"点击了添加好友按钮";
        bool bRet = false;

        //获取列表选择数据
        QStringList items;

        //这里需要先把所有人的信息存进去
        for (auto &u:socialMap->user_name_dict)
        {
            items<<u;
        }

        QString item1 =  QInputDialog:: getItem(this, "添加好友",
                                      "请选择用户姓名", items, 0, true, &bRet, Qt::WindowFlags(), Qt::ImhHiddenText);
        if (bRet && !item1.isEmpty())
        {
            int user1_index=socialMap->user_index_dict[item1];
            QStringList items;
            for(auto &u:socialMap->user_index_dict)
            {
                if (u!=user1_index&&!socialMap->user_friend[user1_index].contains(u))
                {
                    items<<socialMap->user_name_dict[u];
                }
            }
            if (items.empty())
            {
                QMessageBox res_box(QMessageBox::Information,"失败",QString("当前所有用户已是用户:%1 的好友！").arg(item1));
                 res_box.exec();
            }
            else
            {
            QString item2 =  QInputDialog::getItem(this, "添加好友",
                                          "请选择好友姓名", items, 0, true, &bRet, Qt::WindowFlags(), Qt::ImhHiddenText);

            qDebug() << "press ok item1 = " << item1;
             if (bRet && !item2.isEmpty())
             {

                 qDebug() << "press ok item2 = " << item1<<" "<<item2;

                 qDebug()<<"添加成功!";
                 QMessageBox res_box(QMessageBox::Information,"成功",QString("已成功为用户:%1 添加好友 用户:%2！").arg(item1,item2));
                 res_box.exec();
                 socialMap->addFriend(item1,item2);
                 close_btn();
                 paintBtn();
                 //这里还需要绘制button
             }
            }
        }
        else
        {
            qDebug() << "press Cancel item1 = " << item1;
        }
    });

    connect(ui->actionaddGroup,&QAction::triggered,[=](){
        qDebug()<<"点击了添加组织按钮";
        bool bRet = false;
        QString add_group_name= QInputDialog:: getText(this, "添加组织",
                                                     "请输入组织名称", QLineEdit::Normal, "", &bRet);
        if (bRet && !add_group_name.isEmpty())
        {
            qDebug()<<"输入的组织名为:"<<add_group_name;
            //这里要对组织是否已存在进行一下判断

            bool ok=(socialMap->group_index_dict.count(add_group_name)==0);
            if (ok)
            {
                qDebug()<<"添加组织成功";
                QMessageBox res_box(QMessageBox::Information,"成功",QString("已成功添加组织:%1！").arg(add_group_name));
                res_box.exec();
                socialMap->addGroup(add_group_name);
            }
            else
            {
                qDebug()<<"添加组织失败";
                QMessageBox res_box(QMessageBox::Information,"失败",QString("组织:%1 已存在！").arg(add_group_name));
                res_box.exec();
            }
        }

    });

    connect(ui->actionaddGroupMember,&QAction::triggered,[=](){
        qDebug()<<"点击了添加组织成员按钮";
        bool bRet = false;
        //获取列表选择数据
        QStringList items;
        //这里需要先把所有组织的信息存进去
        for (auto &u:socialMap->group_name_dict)
        {
            items<<u;
        }
        QString item1 =  QInputDialog:: getItem(this, "添加组织成员",
                                      "请选择组织", items, 0, true, &bRet, Qt::WindowFlags(), Qt::ImhHiddenText);
        if (bRet && !item1.isEmpty())
        {
            QStringList items;
            int group_index=socialMap->get_group_index(item1);
            //这里需要先把不在组织内的所有人员的信息存进去
            for (auto &u:socialMap->user_name_dict)
            {

                int user_index=socialMap->get_user_index(u);
                if (!socialMap->group_user[group_index].contains(user_index))
                    items<<u;
            }
            if(items.empty())
            {
                QMessageBox res_box(QMessageBox::Information,"失败",QString("当前所有用户已在组织:%1中！").arg(item1));
                res_box.exec();
            }
            else
            {
            QString item2 =  QInputDialog::getItem(this, "添加组织成员",
                                          "请选择用户", items, 0, true, &bRet, Qt::WindowFlags(), Qt::ImhHiddenText);

            qDebug() << "press ok item1 = " << item1;
             if (bRet && !item2.isEmpty())
             {

                 qDebug() << "press ok item2 = " << item1<<" "<<item2;
                 qDebug()<<"添加成功!";
                 QMessageBox res_box(QMessageBox::Information,"成功",QString("已成功在组织:%1 中添加用户:%2！").arg(item1,item2));
                 res_box.exec();
                 socialMap->addGroupMember(item1,item2);
                 close_btn();
                 paintBtn();
                 //这里还需要绘制button
             }
            }
        }
        else
        {
            qDebug() << "press Cancel item1 = " << item1;
        }
    });

}

SocialNetworkMainWindow::~SocialNetworkMainWindow()
{
    close_btn();
    delete socialMap;
    delete ui;
}
void SocialNetworkMainWindow::paintBtn()
{
    //中心是这个用户
    //点击用户查看用户可能认识的人
    //先画出这个结点
    QString now_user_name=socialMap->user_name_dict[now_user_idx];
    MapButton *center_btn=new MapButton(this->width(),this->height()*0.5,now_user_name);
    //qDebug()<<"radius is"<<radius;
    map_btn[++map_btn_cnt]=center_btn;//记录下来好释放
    center_btn->setParent(this);
    //btn->setText(QString::number(k));
    //btn->setStyleSheet("QPushButton{border:0px;}");
    center_btn->move((this->width()-center_btn->width())*0.5,this->height()*0.5);
    center_btn->show();
    center_btn->info->setParent(this);
    center_btn->info->move(this->width()*0.5+center_btn->width()*0.5,this->height()*0.5);
    center_btn->info->show();
    //qDebug()<<"btn x is"<<center_btn->x()<<"y is"<<center_btn->y();
    // qDebug()<<"btn->info x is"<<center_btn->info->x()<<"y is"<<center_btn->info->y();
    connect(center_btn,&QPushButton::clicked,[=](){
        qDebug()<<"用户选择了查看当前用户可能认识的朋友";
        QVector<QPair< QString,int>>  temp=socialMap->get_user_weighted_friend(now_user_idx);
        for (auto t:temp)
        {
            qDebug()<<t.first<<" "<<t.second;
        }
        ShowSortFriendWindow *showSortFriendWindow=new ShowSortFriendWindow(now_user_name,temp);
        showSortFriendWindow->show();


        //this->close();
    });




    //上方是他的好友
    //点击好友，查看好友的好友

    //下面开始画好友
    const int radius=this->height()*0.3;//半径

    const double pi=3.14159;//pi

    int friend_nums=socialMap->user_friend[now_user_idx].size()+1;
    double average=180.0/friend_nums;
    base_x=(this->width()-center_btn->width())*0.5;
    base_y=this->height()*0.5;
    map_btn_size=center_btn->width();
    int paint_idx=1;
    for(auto &f:socialMap->user_friend[now_user_idx])
    {
        //计算出当前坐标
        double nx=base_x+radius*cos(paint_idx*average/180*pi);
        double ny=base_y-radius*sin(paint_idx*average/180*pi);
        QString friend_user_name=socialMap->user_name_dict[f];
        MapButton *friend_btn=new MapButton(nx,ny,friend_user_name);
        //qDebug()<<"radius is"<<radius;
        map_btn[++map_btn_cnt]=friend_btn;//记录下来好释放
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
        connect(friend_btn,&QPushButton::clicked,[=](){
            qDebug()<<QString("用户选择了当前的朋友%1").arg(f);
            //这里面要开一个新窗口，展示这个好友的所有的好友
            //this->close();
            QSet<QString> temp;
            for (auto t:socialMap->user_friend[f])
            {
                temp.insert(socialMap->user_name_dict[t]);
            }
            ShowUserFriendWindow *showUserFriendWindow= new ShowUserFriendWindow(socialMap->user_name_dict[f],temp);
            showUserFriendWindow->show();
        });
        paint_idx++;
    }






    //下面是他的组织
    //点击组织，查看组织内的成员
    //下面开始画他的组织

    int group_nums=socialMap->user_group[now_user_idx].size()+1;
    average=180.0/group_nums;
    paint_idx=1;
    for(auto &f:socialMap->user_group[now_user_idx])
    {
        //计算出当前坐标
        double nx=base_x+radius*cos(paint_idx*average/180*pi);
        double ny=base_y+radius*sin(paint_idx*average/180*pi);
        QString group_user_name=socialMap->group_name_dict[f];
        qDebug()<<"组织:"<<group_user_name<<"建立完成";
        MapButton *group_btn=new MapButton(nx,ny,group_user_name,1,":/src/Coin0008.png");
        //qDebug()<<"radius is"<<radius;
        map_btn[++map_btn_cnt]=group_btn;//记录下来好释放
        group_btn->setParent(this);
        //btn->setText(QString::number(k));
        //btn->setStyleSheet("QPushButton{border:0px;}");
        group_btn->move(nx,ny);
        group_btn->show();
        group_btn->info->setParent(this);
        group_btn->info->move(nx+group_btn->width(),ny);
        group_btn->info->show();
        //group_btn->info->setAttribute(Qt::WA_TransparentForMouseEvents, true);
       // qDebug()<<"btn x is"<<group_btn->x()<<"y is"<<group_btn->y();
        // qDebug()<<"btn->info x is"<<group_btn->info->x()<<"y is"<<group_btn->info->y();
        connect(group_btn,&QPushButton::clicked,[=](){
            qDebug()<<QString("用户选择了当前的组织%1").arg(f);
            //这里面要开一个新窗口，展示这个组织的所有的成员
            //this->close();
            QSet<QString> temp;
            for (auto t:socialMap->group_user[f])
            {
                temp.insert(socialMap->user_name_dict[t]);
            }
            ShowGroupUserWindow *showGroupUserWindow= new ShowGroupUserWindow(socialMap->group_name_dict[f],temp);
            showGroupUserWindow->show();

        });
        paint_idx++;
    }
}
void  SocialNetworkMainWindow::paintEvent(QPaintEvent *)
{
    //这里需要加一个拦截器，使得我在进行操作的时候不要画
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
     if (socialMap->user_counts!=0)
     {
     const int radius=this->height()*0.3;//半径

     const double pi=3.14159;//pi

     int friend_nums=socialMap->user_friend[now_user_idx].size()+1;
     double average=180.0/friend_nums;
     int paint_idx=1;
     for(auto &f:socialMap->user_friend[now_user_idx])
     {
         //计算出当前坐标
         //qDebug()<<"当前用户为:"<<f;
         double nx=base_x+radius*cos(paint_idx*average/180*pi);
         double ny=base_y-radius*sin(paint_idx*average/180*pi);
         painter.drawLine(base_x+map_btn_size*0.5,base_y+map_btn_size*0.5,nx+map_btn_size*0.5,ny+map_btn_size*0.5);
         paint_idx++;
     }






     //下面是他的组织
     //点击组织，查看组织内的成员
     //下面开始画他的组织

     int group_nums=socialMap->user_group[now_user_idx].size()+1;
     average=180.0/group_nums;
     paint_idx=1;
     for(auto &f:socialMap->user_group[now_user_idx])
     {
         //计算出当前坐标
         //qDebug()<<"当前组织为:"<<f;
         double nx=base_x+radius*cos(paint_idx*average/180*pi);
         double ny=base_y+radius*sin(paint_idx*average/180*pi);
         painter.drawLine(base_x+map_btn_size*0.5,base_y+map_btn_size*0.5,nx+map_btn_size*0.5,ny+map_btn_size*0.5);
         paint_idx++;
     }
     }

}
void  SocialNetworkMainWindow::close_btn()
{
    for (int i=1;i<=map_btn_cnt;i++)
    {
        map_btn[i]->close();
        delete map_btn[i];
    }
    map_btn_cnt=0;
}

