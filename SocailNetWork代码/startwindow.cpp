#include "startwindow.h"
#include "mypushbutton.h"
#include <QPushButton>
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include "socialmap.h"
#include <QTextCodec>
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
    //直接开始按钮
    MyPushButtton * startBtn=new MyPushButtton (":/src/start.png");
    startBtn->setParent(this);
    startBtn->move((this->width()-startBtn->width())*0.2,this->height()*0.4);

    connect(startBtn,&QPushButton::clicked,[=](){
        startBtn->zoom1();
        startBtn->zoom2();
        QTimer::singleShot(500,this,[=](){

            socialnetworkMainWindow=new SocialNetworkMainWindow(this);
            socialnetworkMainWindow->setGeometry(this->geometry());
            this->hide();
            socialnetworkMainWindow->show();

            connect(socialnetworkMainWindow,&SocialNetworkMainWindow::back,[=](){
                this->setGeometry((socialnetworkMainWindow->geometry()));
                 QTimer::singleShot(100,this,[=](){
                socialnetworkMainWindow->hide();
                this->show();
                delete socialnetworkMainWindow;});
            });


        });
    });


    //加载文件后开始按钮
    MyPushButtton * loadBtn=new MyPushButtton (":/src/load.png");
    loadBtn->setParent(this);
    loadBtn->move((this->width()-loadBtn->width())*0.8,this->height()*0.4);

    connect(loadBtn,&QPushButton::clicked,[=](){
            loadBtn->zoom1();
            loadBtn->zoom2();
            QTimer::singleShot(500,this,[=](){
            socialnetworkMainWindow=new SocialNetworkMainWindow(this);



            //这里需要读入文件，也就是操作内部数组
                    QFileDialog *fileDialog = new QFileDialog(this);
                    fileDialog->setWindowTitle(tr("打开文件"));
                    fileDialog->setDirectory(".");
                    fileDialog->setNameFilter(tr("TXT Files(*.txt)"));
                    if(fileDialog->exec() == QDialog::Accepted)
                    {
                            QString path = fileDialog->selectedFiles()[0];
                            //QMessageBox::information(NULL, tr("成功"), tr("载入数据完成！"));
                            // 读入数据并进行处理
                            QFile file(path) ;
                            // 这里就不用判断文件是否存在了，因为是直接选择的
                            if (!file.open(QIODevice::ReadOnly|QIODevice::Text))
                            {
                                qDebug()<<"打开文件失败";
                                return ;
                            }
                            QString str=file.readAll();
                            QStringList data =str.split( "\n");
                            for (auto t:data)
                                qDebug()<<t;

                            QTextStream stream(&file);
                            QVector<int> array;

                            int user_nums=data[0].toInt();

                            QStringList list=data[1].split(" ");
                            for (int i=0;i<user_nums;i++)
                            {
                                socialnetworkMainWindow->socialMap->addUser(list[i]);
                            }
                            int row=1;
                            for (int i=1;i<=user_nums;i++)
                            {
                                int now_friend_nums=data[++row].toInt();
                                if (now_friend_nums==-1)
                                {
                                    continue;
                                }
                                list=data[++row].split(" ");
                                for (int j=0;j<now_friend_nums;j++)
                                {
                                    QString user_name=socialnetworkMainWindow->socialMap->user_name_dict[i];
                                    QString friend_name=socialnetworkMainWindow->socialMap->user_name_dict[list[j].toInt()];
                                    socialnetworkMainWindow->socialMap->addFriend(user_name,friend_name);
                                }

                            }
                            int group_nums=data[++row].toInt();
                            list=data[++row].split(" ");
                            for (int i=0;i<group_nums;i++)
                            {
                                socialnetworkMainWindow->socialMap->addGroup(list[i]);
                                qDebug()<<"group is"<<list[i];
                            }
                            for (int i=1;i<=group_nums;i++)
                            {

                                int now_group_user_nums=data[++row].toInt();
                                if (now_group_user_nums==-1)
                                {
                                    continue;
                                }
                                list=data[++row].split(" ");
                                for (int j=0;j<now_group_user_nums;j++)
                                {
                                    QString group_name=socialnetworkMainWindow->socialMap->group_name_dict[i];
                                    QString user_name=socialnetworkMainWindow->socialMap->user_name_dict[list[j].toInt()];
                                    socialnetworkMainWindow->socialMap->addGroupMember(group_name,user_name);
                                    qDebug()<<"group is "<<group_name<<"user is"<<user_name;
                                }
                            }
                            qDebug()<<"row is "<<row;
                    }
                    else
                    {
                            //QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
                    }
            QMessageBox res_box(QMessageBox::Information,"成功",QString("加载数据完成"));
            res_box.exec();
            socialnetworkMainWindow->setGeometry(this->geometry());
            this->hide();
            socialnetworkMainWindow->paintBtn();
            socialnetworkMainWindow->show();
            connect(socialnetworkMainWindow,&SocialNetworkMainWindow::back,[=](){
                this->setGeometry((socialnetworkMainWindow->geometry()));
                 QTimer::singleShot(100,this,[=](){
                socialnetworkMainWindow->hide();
                this->show();
                delete socialnetworkMainWindow;});
            });
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
