#include "bittree.h"

BitTree::BitTree()
{
   //初始化一个结点，所有结点的左右孩子均为-1，下标从1开始
    for (int i=0;i<N;i++)
    {
        l[i]=-1;
        r[i]=-1;
        p[i]=-1;
        l_tag[i]=0;
        r_tag[i]=0;
    }
    root=1;
    idx=1;
}

//添加左孩子

Status BitTree::addLeftChild(int k)
{
    if (l[k]!=-1)
    {
        return ERROR;
    }

    l[k]=++idx;
    p[l[k]]=k;
    return OK;
}

//添加右孩子
Status BitTree::addRightChild(int k)
{
    if (r[k]!=-1)
    {
        return ERROR;
    }
    r[k]=++idx;
    p[r[k]]=k;
    return OK;
}

void BitTree::deleteNodeSup(int k)
{
    if (l_tag[k]==1)
    {
        l[k]=-1;
        l_tag[k]=0;
    }
    if (r_tag[k]==1)
    {
        r[k]=-1;
        r_tag[k]=0;
    }




    if (l[k]!=-1)
    {
        deleteNodeSup(l[k]);
    }
    if (r[k]!=-1)
    {
        deleteNodeSup(r[k]);
    }

    if (l[p[k]]==k)
    {
        l[p[k]]=-1;
    }
    else
    {
        r[p[k]]=-1;
    }
    p[k]=-1;
}
//删除该结点
Status BitTree::deleteNode(int k)
{
    deleteNodeSup(k);
    return OK;
}
void BitTree::preOrderTranverse(int k,int &cnt)
{
    if ((l[k]==-1&&r[k]==-1)||(l_tag[k]&&r_tag[k]))
    {
        cnt++;
        return;
    }
    if (l[k]!=-1&&!l_tag[k])
    {
        preOrderTranverse(l[k],cnt);
    }
    if (r[k]!=-1&&!r_tag[k])
    {
        preOrderTranverse(r[k],cnt);
    }


}
//统计叶子结点个数
int BitTree::calLeaves()
{
    int cnt=0;
    preOrderTranverse(root,cnt);
    return cnt;
}
int BitTree::calDepth(int k)
{
    if ((l[k]==-1&&r[k]==-1)||(l_tag[k]&&r_tag[k]))
    {
        return 1;
    }
    int depth=1;
    if (l[k]!=-1&&!l_tag[k])
    {
        depth=1+calDepth(l[k]);
    }
    if (r[k]!=-1&&!r_tag[k])
    {
        depth=qMax(depth,1+calDepth(r[k]));
    }
    return depth;

}
BitTree::~BitTree()
{

}

//中序遍历的顺序赋值
void BitTree::midOrderTraverse(int k,int *a,int &cnt)
{
    if (l[k]!=-1&&!l_tag[k])
    {
        midOrderTraverse(l[k],a,cnt);
    }

    a[++cnt]=k;

    if (r[k]!=-1&&!r_tag[k])
    {
        midOrderTraverse(r[k],a,cnt);
    }
}

//后序遍历的顺序赋值
void BitTree::postOrderTraverse(int k,int *a,int &cnt)
{
    if (l[k]!=-1&&!l_tag[k])
    {
        postOrderTraverse(l[k],a,cnt);
    }



    if (r[k]!=-1&&!r_tag[k])
    {
        postOrderTraverse(r[k],a,cnt);
    }

    a[++cnt]=k;
}


//前序线索化
void BitTree::preOrderThreading(int k,int &pre)
{
    if (l[k]==-1)
    {
        //没有左孩子
        l_tag[k]=1;//线索
        l[k]=pre;//左孩子指向前驱
    }
    if (r[k]==-1)
    {
        r_tag[k]=1;
    }
    if (pre!=-1&&r_tag[pre])
        r[pre]=k;
    pre=k;
    if (l_tag[k]==0&&l[k]!=-1)
    {
        preOrderThreading(l[k],pre);
    }
    if (r_tag[k]==0&&r[k]!=-1)
    {
        preOrderThreading(r[k],pre);
    }

}

//中序线索化
void BitTree::midOrderThreading(int k,int &pre)
{
    if (l_tag[k]==0&&l[k]!=-1)
    {
        midOrderThreading(l[k],pre);
    }
    if (l[k]==-1)
    {
        //没有左孩子
        l_tag[k]=1;//线索
        l[k]=pre;//左孩子指向前驱
    }
    if (r[k]==-1)
    {
        r_tag[k]=1;
    }
    if (pre!=-1&&r_tag[pre])
        r[pre]=k;
    pre=k;

    if (r_tag[k]==0&&r[k]!=-1)
    {
        midOrderThreading(r[k],pre);
    }

}

//后序线索化
void BitTree::postOrderThreading(int k,int &pre)
{
    if (l_tag[k]==0&&l[k]!=-1)
    {
        postOrderThreading(l[k],pre);
    }
    if (r_tag[k]==0&&r[k]!=-1)
    {
        postOrderThreading(r[k],pre);
    }
    if (l[k]==-1)
    {
        //没有左孩子
        l_tag[k]=1;//线索
        l[k]=pre;//左孩子指向前驱
    }
    if (r[k]==-1)
    {
        r_tag[k]=1;
    }
    if (pre!=-1&&r_tag[pre])
        r[pre]=k;
    pre=k;
}
//利用前序遍历清空线索化
void BitTree::clearThreading(int k)
{
    if (l_tag[k]==1)
    {
        l[k]=-1;
        l_tag[k]=0;
    }
    if (r_tag[k]==1)
    {
        r[k]=-1;
        r_tag[k]=0;
    }

    if (l[k]!=-1)
    {
        clearThreading(l[k]);
    }
    if (r[k]!=-1)
    {
        clearThreading(r[k]);
    }

}
