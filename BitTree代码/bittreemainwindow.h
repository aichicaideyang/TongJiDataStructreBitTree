#ifndef BITTREEMAINWINDOW_H
#define BITTREEMAINWINDOW_H

#include <QMainWindow>
#include "treenodebutton.h"
#include "bittree.h"
#include <QLabel>
QT_BEGIN_NAMESPACE
namespace Ui { class BitTreeMainWindow; }
QT_END_NAMESPACE

class BitTreeMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    BitTreeMainWindow(QWidget *parent = nullptr);
    ~BitTreeMainWindow();
    void paintEvent(QPaintEvent *);
    void paintBitTree(int k,int layer,double x,double y);
    void cal_parameters();//需要根据T数组的情况来算出一些绘图参数
    void close_btn();


    //static void update(BitTreeMainWindow *b1,BitTreeMainWindow *b2);
    //bool eventFilter(QObject *watched, QEvent *event);
    //friend class StartWindow;
private:
    Ui::BitTreeMainWindow *ui;
    BitTree T;//这个是初始二叉树
    double initial_x;
    double initial_y;
    double ratio;
    int total_depth;
    bool free_paint[N]; //这里是用来设定某个点是否已经打印出来，要在显示之后再给true
    TreeNodeButton * tree_node_btn[N]; //用来记录下已有的btn 需要对其关闭
    int btn_cnt;//按钮计数
    int mid_order[N];//存储中序遍历顺序
    int post_order[N];//存储后序遍历顺序
    int btn_index[N];//存储该下标的按钮对应的k
    int thread_mode=0;//线索化模式  0.非线索化 1.前序线索化 2.中序线索化 4.后序线索化

    //这里需要判断一下是否处于遍历状态，如果在遍历，那么其他操作禁止
    bool traverse_state=0;//这里禁止其他按钮的工作

signals:
    void reStart();
};
#endif // BITTREEMAINWINDOW_H
