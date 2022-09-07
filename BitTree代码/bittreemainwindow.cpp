#include "bittreemainwindow.h"
#include "ui_bittreemainwindow.h"
#include "treenodebutton.h"
#include "bittree.h"
#include <windows.h>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>
#include <QPainter>
#include <math.h>
#include <QLabel>
#include <QStack> //这里仅用于绘画，与二叉树本身的数据结构无关
#include <QTimer>
BitTreeMainWindow::BitTreeMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BitTreeMainWindow)
{

    ui->setupUi(this);
    this->setFixedSize(1280,800);
    setWindowIcon(QIcon(":/src/Icon.png"));
    setWindowTitle("二叉树的遍历及其线索化");
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });
    this->resize(800,640);
    QPixmap pix;
    bool ret=pix.load(":/src/Coin0001.png");
    if (!ret)
    {
        qDebug()<<"图片加载失败";
        return;
    }

    /*
    T.addLeftChild(1);
    T.addLeftChild(2);
    T.addRightChild(1);
    T.addRightChild(2);
    T.addLeftChild(3);
    T.addRightChild(3);
    T.addLeftChild(4);
    T.addRightChild(4);*/
    //下面考虑如何画二叉树

    //根据叶子结点来确定radius


    //连接叶子结点计数

    connect(ui->actioncal,&QAction::triggered,[=](){
            //qDebug()<<"叶子结点个数是"<<T.calLeaves();
            //这里需要打开一个message
            QString str=QString("二叉树叶子结点的个数为：%1").arg(T.calLeaves());
            QMessageBox op_box(QMessageBox::Information,"提示",str);
            op_box.exec();
    });


    //下面开始考虑连接信号，如何知道是那一个结点被点呢？

    btn_cnt=0;
    //绘图之前可以根据叶子结点的数量来确定间距，对于每个结点来说，他的左右孩子距其的距离
    cal_parameters();

    paintBitTree(T.root,pow(2,total_depth-2),initial_x,initial_y);


    //下面考虑先前序遍历

    connect(ui->actionpre,&QAction::triggered,[=](){
        if (traverse_state!=1)
        {
        QPixmap pix1;
        bool ret=pix1.load(":/src/Coin0008.png");
        if (!ret)
        {
           // qDebug()<<"图片加载失败";
            return;
        }
        QPixmap pix2;
        ret=pix2.load(":/src/Coin0001.png");
        if (!ret)
        {
           // qDebug()<<"图片加载失败";
            return;
        }
        //其实也就是遍历整个btn，然后把图片换一下，再换回来
        traverse_state=1;
        for (int i=1;i<=btn_cnt;i++)
        {
            tree_node_btn[i]->active=false;
            QTimer::singleShot(1000*i,this,[=](){

                tree_node_btn[i]->setIcon(pix1);
                 QTimer::singleShot(1000,this,[=](){
                     tree_node_btn[i]->setIcon(pix2);

                     if (i==btn_cnt)
                     {
                         for (int i=1;i<=btn_cnt;i++)
                              tree_node_btn[i]->active=true;
                          traverse_state=0;
                     }
                 });
            });
        }
        }


    });

    //接下来考虑中序遍历，其实最主要在于存下来整个遍历的序列
    //使用一个数组来存储下遍历的顺序即可
    connect(ui->actionmid,&QAction::triggered,[=](){
        if (traverse_state!=1)
        {
        int cnt=0;

        T.midOrderTraverse(T.root,mid_order,cnt);
        /*
        for (int i=1;i<=cnt;i++)
        {
           qDebug()<<mid_order[i]<<" ";
        }*/
        QPixmap pix1;
        bool ret=pix1.load(":/src/Coin0008.png");
        if (!ret)
        {
            qDebug()<<"图片加载失败";
            return;
        }
        QPixmap pix2;
        ret=pix2.load(":/src/Coin0001.png");
        if (!ret)
        {
            qDebug()<<"图片加载失败";
            return;
        }
        //其实也就是遍历整个btn，然后把图片换一下，再换回来
        traverse_state=1;
        for (int i=1;i<=cnt;i++)
        {
            tree_node_btn[btn_index[mid_order[i]]]->active=false;
            QTimer::singleShot(1000*i,this,[=](){
                // qDebug()<<mid_order[i];
                tree_node_btn[btn_index[mid_order[i]]]->setIcon(pix1);
                 QTimer::singleShot(1000,this,[=](){
                     tree_node_btn[btn_index[mid_order[i]]]->setIcon(pix2);

                     if (i==cnt)
                     {
                          for (int i=1;i<=cnt;i++)
                          tree_node_btn[btn_index[mid_order[i]]]->active=true;
                          traverse_state=0;
                     }
                 });
            });
        }
        }


    });

    //后序遍历
    connect(ui->actionpro,&QAction::triggered,[=](){
        if (traverse_state!=1)
        {
        int cnt=0;
        T.postOrderTraverse(T.root,post_order,cnt);
        QPixmap pix1;
        bool ret=pix1.load(":/src/Coin0008.png");
        if (!ret)
        {
            qDebug()<<"图片加载失败";
            return;
        }
        QPixmap pix2;
        ret=pix2.load(":/src/Coin0001.png");
        if (!ret)
        {
            qDebug()<<"图片加载失败";
            return;
        }
        //其实也就是遍历整个btn，然后把图片换一下，再换回来
        traverse_state=1;
        for (int i=1;i<=cnt;i++)
        {
            tree_node_btn[btn_index[post_order[i]]]->active=false;

            QTimer::singleShot(1000*i,this,[=](){
                tree_node_btn[btn_index[post_order[i]]]->setIcon(pix1);
                 QTimer::singleShot(1000,this,[=](){
                     tree_node_btn[btn_index[post_order[i]]]->setIcon(pix2);


                     if (i==cnt)
                     {      for (int i=1;i<=cnt;i++)
                         {
                             tree_node_btn[btn_index[post_order[i]]]->active=true;
                         }
                          traverse_state=0;
                      }
                 });
            });
        }

        }
    });

    //清空二叉树
    connect(ui->actionclear,&QAction::triggered,[=](){
        if (traverse_state!=1)
        {
        QMessageBox op_box2(QMessageBox::Question,"提示","该操作会使得删除所有结点(仅留下初始结点)，是否继续？");
        QPushButton * go_op=op_box2.addButton("继续", QMessageBox::AcceptRole);
        QPushButton * quit_op=op_box2.addButton( QMessageBox::Cancel);
        op_box2.exec();
        quit_op->setText("取消");
        if (op_box2.clickedButton()==go_op)
        {
            if (1)
            {

            QMessageBox res_box(QMessageBox::Information,"成功","已清空二叉树！");
            res_box.exec();
            T.deleteNode(T.root);
            cal_parameters();
            close_btn();
            paintBitTree(T.root,pow(2,total_depth-2),initial_x,initial_y);
            }
        }
        }

    });

    //下面考虑二叉树的线索化
    //每次进行新的线索化之前要清空一下
    //清空线索化
    connect(ui->actionclear_2,&QAction::triggered,[=](){
        thread_mode=0;
        //清空之前标记,需要遍历所有结点，并将其中是tag的地方置为-1
        QMessageBox res_box(QMessageBox::Information,"成功","清除二叉树线索化成功！");
        res_box.exec();
        T.clearThreading(T.root);
    });

    //前序线索化
    connect(ui->actionpre_2,&QAction::triggered,[=](){
       // qDebug()<<"用户选择了前序线索化";
        thread_mode=1;
        //清空之前标记
        T.clearThreading(T.root);
        //线索化
        int pre=-1;
        QMessageBox res_box(QMessageBox::Information,"成功","前序线索化二叉树成功！");
        res_box.exec();
        T.preOrderThreading(T.root,pre);

       // qDebug()<<"前序线索化完毕";
    });

    //中序线索化
    connect(ui->actionmid_2,&QAction::triggered,[=](){
        //qDebug()<<"用户选择了中序线索化";
        thread_mode=2;
        //清空之前标记
        T.clearThreading(T.root);
        //线索化
        int pre=-1;
        QMessageBox res_box(QMessageBox::Information,"成功","中序线索化二叉树成功！");
        res_box.exec();
        T.midOrderThreading(T.root,pre);

       // qDebug()<<"中序线索化完毕";
    });

    //后序线索化
    connect(ui->actionpro_2,&QAction::triggered,[=](){
       // qDebug()<<"用户选择了后序线索化";
        thread_mode=4;
        //清空之前标记
        T.clearThreading(T.root);
        //线索化
        int pre=-1;
        QMessageBox res_box(QMessageBox::Information,"成功","后序线索化二叉树成功！");
        res_box.exec();
        T.postOrderThreading(T.root,pre);

        //qDebug()<<"后序线索化完毕";
    });

/*
    int radius=1;
    TreeNodeButton *btn=new TreeNodeButton(radius);
    btn->setParent(this);
    btn->move((this->width()-pix.width()*radius)/2,30);
    //btn->setStyleSheet("QPushButton{border:0px;}");
    btn->show();

    connect(btn,&QPushButton::clicked,[=](){
        //这里需要弹出一个消息框，来选择添加左孩子或者右孩子，或者删除掉这个结点
        QMessageBox op_box(QMessageBox::Question,"提示","请选择对结点进行的操作！");
        QPushButton *add_lchild = op_box.addButton("添加左孩子", QMessageBox::AcceptRole);
        QPushButton *add_rchild = op_box.addButton("添加右孩子", QMessageBox::AcceptRole);
        QPushButton *delete_node = op_box.addButton("删除该结点", QMessageBox::AcceptRole);
        QPushButton *cacel_op= op_box.addButton( QMessageBox::Cancel);
        cacel_op->setText("取消");
        op_box.exec();


        //操作成功之后需要弹出 提示框，成功或者失败
        if (op_box.clickedButton()==add_lchild)
        {
            qDebug()<<"用户选择了添加左孩子！";
            QMessageBox res_box(QMessageBox::Warning,"错误","该结点已存在左孩子，请重新操作！");
            res_box.exec();

        }
        else if (op_box.clickedButton()==add_rchild)
        {
            qDebug()<<"用户选择了添加右孩子!";
            QMessageBox res_box(QMessageBox::Information,"成功","已成功为该结点添加右孩子！");
            res_box.exec();
        }
        else if (op_box.clickedButton()==delete_node)
        {
            qDebug()<<"用户选择了删除结点！";
            QMessageBox op_box2(QMessageBox::Question,"提示","该操作会使得删除掉该结点及其子节点，是否继续？");
            QPushButton * go_op=op_box2.addButton("继续", QMessageBox::AcceptRole);
            QPushButton * quit_op=op_box2.addButton( QMessageBox::Cancel);
            op_box2.exec();
            quit_op->setText("取消");
            if (op_box2.clickedButton()==go_op)
            {
                QMessageBox res_box(QMessageBox::Information,"成功","已删除该结点及其子节点！");
                res_box.exec();
            }
            else
            {
                emit btn->clicked();
            }
        }
        else
        {
            qDebug()<<"用户未进行任何操作！";
        }


        qDebug()<<"点击到了结点！";
    });
*/
}
void BitTreeMainWindow::paintBitTree(int k,int layer,double x,double y)
{
    //递归调用这个函数
    //QPainter painter(this->main_label);
   // QBrush brush;
   // brush.setColor(QColor(255,0,0));
    //painter.setBrush(brush);
    free_paint[k]=true;
    QPixmap pix;
    bool ret=pix.load(":/src/Coin0001.png");
    if (!ret)
    {
        qDebug()<<"图片加载失败";
        return;
    }
    double radius=ratio;
    TreeNodeButton *btn=new TreeNodeButton(radius);
    //qDebug()<<"radius is"<<radius;
    tree_node_btn[++btn_cnt]=btn;//记录下来好释放
    btn_index[k]=btn_cnt;
    btn->setParent(this);
    //btn->setText(QString::number(k));
    btn->move(x,y);
    //btn->setStyleSheet("QPushButton{border:0px;}");
    btn->show();

    connect(btn,&QPushButton::clicked,[=](){
        //这里需要弹出一个消息框，来选择添加左孩子或者右孩子，或者删除掉这个结点
        QMessageBox op_box(QMessageBox::Question,"提示","请选择对结点进行的操作！");
        op_box.setMinimumSize(QSize(640, 480));
        QPushButton *add_lchild = op_box.addButton("添加左孩子", QMessageBox::AcceptRole);

        QPushButton *add_rchild = op_box.addButton("添加右孩子", QMessageBox::AcceptRole);
        QPushButton *delete_node = op_box.addButton("删除该结点", QMessageBox::AcceptRole);
        QPushButton *cacel_op= op_box.addButton( QMessageBox::Cancel);
        cacel_op->setText("取消");
        op_box.exec();


        //操作成功之后需要弹出 提示框，成功或者失败
        if (op_box.clickedButton()==add_lchild)
        {
           // qDebug()<<"用户选择了添加左孩子！";


            if (T.l[k]!=-1&&!T.l_tag[k])
            {
            QMessageBox res_box(QMessageBox::Warning,"错误","该结点已存在左孩子，请重新操作！");
            res_box.exec();

            }
            else
            {
                QMessageBox res_box(QMessageBox::Information,"成功","已成功为该结点添加左孩子！");
                res_box.exec();
                 if (thread_mode!=0)
                     T.clearThreading(T.root);
                T.addLeftChild(k);
                cal_parameters();
                //这里需要把之前打开的都关闭
                close_btn();
                paintBitTree(T.root,pow(2,total_depth-2),initial_x,initial_y);
                //这里要重新绘图
            }


        }
        else if (op_box.clickedButton()==add_rchild)
        {
           // qDebug()<<"用户选择了添加右孩子!";


            if (T.r[k]!=-1&&!T.r_tag[k])
            {
            QMessageBox res_box(QMessageBox::Warning,"错误","该结点已存在右孩子，请重新操作！");
            res_box.exec();

            }
            else
            {
                QMessageBox res_box(QMessageBox::Information,"成功","已成功为该结点添加右孩子！");

                res_box.exec();
                if (thread_mode!=0)
                    T.clearThreading(T.root);
                T.addRightChild(k);
                cal_parameters();
                close_btn();
                paintBitTree(T.root,pow(2,total_depth-2),initial_x,initial_y);
                //这里要重新绘图
            }


        }
        else if (op_box.clickedButton()==delete_node)
        {
           // qDebug()<<"用户选择了删除结点！";
            QMessageBox op_box2(QMessageBox::Question,"提示","该操作会使得删除掉该结点及其子节点，是否继续？");
            QPushButton * go_op=op_box2.addButton("继续", QMessageBox::AcceptRole);
            QPushButton * quit_op=op_box2.addButton( QMessageBox::Cancel);
            op_box2.exec();
            quit_op->setText("取消");
            if (op_box2.clickedButton()==go_op)
            {
                if (1)
                {

                QMessageBox res_box(QMessageBox::Information,"成功","已删除该结点及其子节点！");
                res_box.exec();
                if (thread_mode!=0)
                    T.clearThreading(T.root);
                T.deleteNode(k);
                cal_parameters();
                close_btn();
                paintBitTree(T.root,pow(2,total_depth-2),initial_x,initial_y);
                }
            }
            else
            {
                emit btn->clicked();
            }
        }
        else
        {
            //qDebug()<<"用户未进行任何操作！";
        }

        if (thread_mode==1)
        {
            int pre=-1;
            T.preOrderThreading(T.root,pre);
        }
        else if (thread_mode==2)
        {
            int pre=-1;
            T.midOrderThreading(T.root,pre);
        }
        else if (thread_mode==4)
        {
            int pre=-1;
            T.postOrderThreading(T.root,pre);
        }
        free_paint[T.idx]=true;
       // qDebug()<<"点击到了结点！";
    });




    if (T.l[k]!=-1)
    {
        //painter.drawLine(x,y,x-layer*ratio*pix.width(),y+ratio*pix.width());
        paintBitTree(T.l[k],layer/2,x-layer*ratio*pix.width(),y+ratio*pix.width()*1.5);
    }
    if (T.r[k]!=-1)
    {
       // painter.drawLine(x,y,x+layer*ratio*pix.width(),y+ratio*pix.width());
        paintBitTree(T.r[k],layer/2,x+layer*ratio*pix.width(),y+ratio*pix.width()*1.5);
    }




}

void BitTreeMainWindow::cal_parameters()
{
    QPixmap pix;
    bool ret=pix.load(":/src/Coin0001.png");
    if (!ret)
    {
        qDebug()<<"图片加载失败";
        return;
    }
    //int  total_leaves=T.calLeaves();
    total_depth=T.calDepth(T.root);
    //qDebug()<<"二叉树的深度是"<<total_depth;
    int base_distance=pix.width();//结点图片的宽度
    //那么这里一共就需要

    int cnt_last_layer=0;
    for (int i=1;i<=total_depth-2;i++)
    {
        cnt_last_layer+=pow(2,i);
    }


    int total_width=base_distance*2*cnt_last_layer;
    int total_height=base_distance*total_depth*2;
    initial_y=50;
    if (total_width>this->width()/1.5)
    {
        base_distance=(this->width()/1.5)/(2*cnt_last_layer);
        //qDebug()<<"达到了屏幕最大值";
        //qDebug()<<"图片宽度"<<pix.width()<<"自身宽度"<<base_distance<<"屏幕宽度"<<this->width();
    }
    if (total_height>(this->height()-initial_y))
    {
        base_distance=qMin(base_distance,this->height()/total_depth);
    }

    //base_distance其实就是图像缩放的比例
     ratio=1.0;
    if (base_distance<pix.width())
    {

        ratio=double(base_distance)/pix.width();
       // qDebug()<<"here ratio is"<<ratio;
    }

    //ratio=0.1; 经测试发现改变ratio是有效的，下面需要开始计算每一层的距离，也就是距中心点的位置

    initial_x=(this->width()-pix.width()*ratio)/2;

}
BitTreeMainWindow::~BitTreeMainWindow()
{
    delete ui;
}
void BitTreeMainWindow::paintEvent(QPaintEvent *)
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
    //这里由于不能递归，所以实现用栈遍历来画
    struct node {
        int k;
        double x,y;
        int layer;
    };
    struct node_pos{
        double x,y;
    }pos[N];

    pix.load(":/src/Coin0001.png");
    QStack<node> stack;
    stack.push({T.root,initial_x,initial_y,int(pow(2,total_depth-2))});
    //qDebug()<<"initial_x is"<<initial_x<<"initial_y is"<<initial_y;



    while (!stack.empty())
    {
        auto now=stack.top();
        pos[now.k]={now.x,now.y};
        stack.pop();
        pen.setColor(QColor(55,240,251));
        painter.setPen(pen);
        if (T.l[now.k]!=-1&&T.l_tag[now.k]==0)
        {

            double nx=now.x-now.layer*ratio*pix.width();
            double ny=now.y+ratio*pix.width()*1.5;
            if (free_paint[T.l[now.k]])
            painter.drawLine(now.x+ratio*pix.width()/2,now.y+ratio*pix.width()/2,nx+ratio*pix.width()/2,ny+ratio*pix.width()/2);
            stack.push({T.l[now.k],nx,ny,now.layer/2});


        }
        if (T.r[now.k]!=-1&&T.r_tag[now.k]==0)
        {
            double nx=now.x+now.layer*ratio*pix.width();
            double ny=now.y+ratio*pix.width()*1.5;
            if (free_paint[T.r[now.k]])
            painter.drawLine(now.x+ratio*pix.width()/2,now.y+ratio*pix.width()/2,nx+ratio*pix.width()/2,ny+ratio*pix.width()/2);
            stack.push({T.r[now.k],nx,ny,now.layer/2});
        }
        /*
        if (T.l_tag[now.k]&&T.l[now.k]!=-1)
        {
            qDebug()<<"绘制前驱结点";
            //前驱结点
            pen.setColor(QColor(248,29,12));
            painter.setPen(pen);
            double nx=pos[T.l[now.k]].x;
            double ny=pos[T.l[now.k]].y;
            qDebug()<<"当前结点位置:"<<now.x<<" ,"<<now.y<<"前驱结点位置:"<<nx<<","<<ny<<"当前结点:"<<now.k<<"前驱结点:"<<T.l[now.k];
            painter.drawLine(now.x,now.y,nx,ny);//左边和左边连起来
        }
        if (T.r_tag[now.k]&&T.r[now.k]!=-1)
        {
            qDebug()<<"绘制后继结点";
            //后继结点
            pen.setColor(QColor(242,240,36));
            painter.setPen(pen);
            double nx=pos[T.r[now.k]].x;
            double ny=pos[T.r[now.k]].y;
             qDebug()<<"当前结点位置:"<<now.x<<" ,"<<now.y<<"后继结点位置:"<<nx<<","<<ny<<"当前结点:"<<now.k<<"后继结点:"<<T.r[now.k];
            painter.drawLine(now.x+ratio*pix.width(),now.y,nx+ratio*pix.width(),ny);
        }*/


        //在这里考虑画的过程，之前的颜色是正常色
        //下面红色是前驱，黄色是后继


        //qDebug()<<"there ratio is"<<ratio;
    }
    stack.push({T.root,initial_x,initial_y,int(pow(2,total_depth-2))});
    while (!stack.empty())
    {
        auto now=stack.top();
        stack.pop();
        if (T.l[now.k]!=-1&&T.l_tag[now.k]==0)
        {

            double nx=now.x-now.layer*ratio*pix.width();
            double ny=now.y+ratio*pix.width()*1.5;
            stack.push({T.l[now.k],nx,ny,now.layer/2});


        }
        if (T.r[now.k]!=-1&&T.r_tag[now.k]==0)
        {
            double nx=now.x+now.layer*ratio*pix.width();
            double ny=now.y+ratio*pix.width()*1.5;
            stack.push({T.r[now.k],nx,ny,now.layer/2});
        }
        if (T.l_tag[now.k])
        {
           // qDebug()<<"绘制前驱结点";
            //前驱结点
            pen.setColor(QColor(248,29,12));
            painter.setPen(pen);
            if (T.l[now.k]!=-1)
            {
            double nx=pos[T.l[now.k]].x;
            double ny=pos[T.l[now.k]].y;
            //qDebug()<<"当前结点位置:"<<now.x<<" ,"<<now.y<<"前驱结点位置:"<<nx<<","<<ny<<"当前结点:"<<now.k<<"前驱结点:"<<T.l[now.k];
            //painter.drawLine(now.x,now.y+ratio*pix.width()/2,nx,ny+ratio*pix.width()/2);//左边和左边连起来
            QPainterPath path;
            path.moveTo(now.x+ratio*pix.width()/2,now.y+ratio*pix.width()/2);
            path.cubicTo(QPointF(now.x,now.y+ratio*pix.width()/2),QPointF(now.x+ratio*pix.width()/2,now.y),QPointF(nx+ratio*pix.width()/2,ny+ratio*pix.width()/2));
            painter.drawPath(path);
            }
            else
            {
                //冒出一点线
                painter.drawLine(now.x+ratio*pix.width()/2,now.y+ratio*pix.width()/2,now.x,now.y+ratio*pix.width());//左边和左边连起来
            }

        }
        if (T.r_tag[now.k])
        {
           // qDebug()<<"绘制后继结点";
            //后继结点
            pen.setColor(QColor(242,240,36));
            painter.setPen(pen);
            if (T.r[now.k]!=-1)
            {
            double nx=pos[T.r[now.k]].x;
            double ny=pos[T.r[now.k]].y;
            // qDebug()<<"当前结点位置:"<<now.x<<" ,"<<now.y<<"后继结点位置:"<<nx<<","<<ny<<"当前结点:"<<now.k<<"后继结点:"<<T.r[now.k];
            //painter.drawLine(now.x+ratio*pix.width(),now.y+ratio*pix.width()/2,nx+ratio*pix.width(),ny+ratio*pix.width()/2);
            QPainterPath path;
            path.moveTo(now.x+ratio*pix.width()/2,now.y+ratio*pix.width()/2);
            //path.cubicTo(QPointF(now.x+ratio*pix.width()/2,now.y),QPointF(now.x,now.y+ratio*pix.width()/2),QPointF(nx+ratio*pix.width()/2,ny+ratio*pix.width()/2));
            path.cubicTo(QPointF(now.x+ratio*pix.width()/2,now.y),QPointF(nx,ny+ratio*pix.width()/2),QPointF(nx+ratio*pix.width()/2,ny+ratio*pix.width()/2));
            painter.drawPath(path);
            }
            else
            painter.drawLine(now.x+ratio*pix.width()/2,now.y+ratio*pix.width()/2,now.x+ratio*pix.width(),now.y+ratio*pix.width());//左边和左边连起来
        }
        //这里考虑俩短线

        //在这里考虑画的过程，之前的颜色是正常色
        //下面红色是前驱，黄色是后继


        //qDebug()<<"there ratio is"<<ratio;
    }

}

void BitTreeMainWindow::close_btn()
{
    for (int i=1;i<=btn_cnt;i++)
    {
        tree_node_btn[i]->close();
        delete tree_node_btn[i];
    }
    btn_cnt=0;
}
