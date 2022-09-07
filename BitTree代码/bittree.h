#include <QString>
#include "bittreemainwindow.h"
#ifndef BITTREE_H
#define BITTREE_H
/* 一些宏定义 */
#define TRUE 1
#define FALSE 0
#define OK  1
#define ERROR 0
#define OVERFLOW -1
const int N=1000;//由于使用数组模拟二叉树，这里设置最大结点数，可修改
typedef int Status;
typedef QChar ElemType;
/**************/

class BitTree
{
private:
    int l[N],r[N]; //左孩子，右孩子数组
    int l_tag[N],r_tag[N]; //线索化时使用，0表示左右孩子，1表示前驱后继
    int p[N];//父亲数组
    int root=1; //根结点
    int idx=1; //表示当前最大的下标

public:

    BitTree();
    ~BitTree();
    Status addLeftChild(int k);
    Status addRightChild(int k);
    Status deleteNode(int k);
    void deleteNodeSup(int k);
    int calLeaves();
    int calDepth(int k);
    void preOrderTranverse(int k,int &cnt);//先序求叶子结点数
    void midOrderTraverse(int k,int *a,int &cnt);
    void postOrderTraverse(int k,int *a,int &cnt);
    void clearThreading(int k);
    void preOrderThreading(int k,int &pre);
    void midOrderThreading(int k,int &pre);
    void postOrderThreading(int k,int &pre);
    friend class BitTreeMainWindow;
};



#endif // BITTREE_H
