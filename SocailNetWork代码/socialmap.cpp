#include "socialmap.h"
#include <QDebug>
SocialMap::SocialMap()
{
     user_counts=0;//人数总标号，用于分配人的下标
     group_counts=0;//组织总标号，用于分配组织的下标
     user_index_dict.clear(); //用户下标字典
     user_name_dict.clear();// 用户姓名字典
     group_index_dict.clear();//组织下标字典
     group_name_dict.clear();//组织名称字典
     for (int i=0;i<N;i++)
         user_friend[i].clear();
     for (int i=0;i<N;i++)
         user_group[i].clear();
     for (int i=0;i<N;i++)
         group_user[i].clear();
}
SocialMap::~SocialMap()
{

}
//添加成员
Status SocialMap::addUser( QString user_name)
{
    if (user_index_dict.count(user_name)!=0)
    {

        qDebug()<<"当前用户已存在！"<<user_name;
        return ERROR;
    }
    //建立姓名-下标映射
    user_index_dict[user_name]=++user_counts;
    //建立下标-姓名映射
    user_name_dict[user_counts]=user_name;
    return OK;
}
//添加组织
Status SocialMap::addGroup( QString group_name)
{
    if (group_index_dict.count(group_name)!=0)
    {
        qDebug()<<"当前组织已存在！";
        return ERROR;
    }
    //建立姓名-下标映射
    group_index_dict[group_name]=++group_counts;
    //建立下标-姓名映射
    group_name_dict[group_counts]=group_name;
    return OK;
}
//添加好友
Status SocialMap::addFriend( QString user_name, QString friend_name )
{
    //添加好友主要是对应于下标而言
    int user_idx=get_user_index(user_name);
    int friend_idx=get_user_index(friend_name);
    //判断一下是否存在
    if (user_idx==-1 || friend_idx==-1)
    {
        qDebug()<<"用户或好友不存在！";
        return ERROR;
    }
    user_friend[user_idx].insert(friend_idx);
    user_friend[friend_idx].insert(user_idx);
    return OK;
}
//添加组织成员
Status SocialMap::addGroupMember( QString group_name, QString user_name)
{

    int group_idx=get_group_index(group_name);
    int user_idx=get_user_index(user_name);
    if (group_idx==-1 || user_idx==-1)
    {
        qDebug()<<"组织或用户不存在！";
        return ERROR;
    }
    group_user[group_idx].insert(user_idx);
    user_group[user_idx].insert(group_idx);
    return OK;
}

//一些外部接口
//根据姓名获取用户下标
int SocialMap::get_user_index( QString user_name)
{
    if (user_index_dict.count(user_name)!=0)
    {
        //存在
        return user_index_dict[user_name];
    }
    //不存在
    return -1;
}
//根据名称获取组织下标
int SocialMap::get_group_index( QString group_name)
{
    if (group_index_dict.count(group_name)!=0)
    {
        //存在
        return group_index_dict[group_name];
    }
    //不存在
    return -1;
}
//根据下标获取用户好友set
QSet<int> SocialMap::get_user_friend(int user_index)
{
    if (user_name_dict.count(user_index)!=0)
    {
        return user_friend[user_index];
    }

    qDebug()<<"当前用户不存在";
    return user_friend[0];

}
//根据下标获取用户组织set
QSet<int> SocialMap::get_user_group(int user_index)
{
    if (user_name_dict.count(user_index)!=0)
    {
        return user_group[user_index];
    }

    qDebug()<<"当前用户不存在";
    return user_group[0];

}
//根据下标获取组织用户set
QSet<int> SocialMap::get_group_user(int group_index)
{
    if (group_name_dict.count(group_index)!=0)
    {
        return group_user[group_index];
    }
    qDebug()<<"当前组织不存在";
    return group_user[0];

}
//辅助排序函数
 bool SocialMap::cmp(QPair< QString,int> &user_1,QPair< QString,int>&user_2)
{
    return user_1.second>user_2.second;
}

//对一个用户的所有好友进行排序，并返回权值和姓名
QVector<QPair< QString,int>> SocialMap::get_user_weighted_friend(int user_index)
{
    QVector<QPair<QString,int>>  res;//用来存放结果
    //这里定义出好友的分级
    //首先是一级好友，这些好友不属于可能认识的人
    //接下来就是可能认识的人，评分=共同好友数+共同组织数
    //这里评分本来是打算取小数，但是这样的话分级太多了，不好画。。
    //遍历该用户的所有好友和组织
    QMap<int,int> temp;//判断某个人是否已经计算过了
    if (user_name_dict.count(user_index)==-1)
    {
        return res;//直接返回，在外部设置了判断，应该不会运行到这个位置
    }

    //下面先遍历这个人的所有好友
    for (auto &f:user_friend[user_index])
    {
        //遍历其所有的二级好友
        for (auto &ff:user_friend[f])
        {
            if (temp.count(ff)==0)
            {
                //不存在
                temp[ff]=1;
            }
            else
                temp[ff]++;
        }
    }
    //下面遍历这个人的所有组织
    for (auto &g:user_group[user_index])
    {
        //遍历这个组织内的所有人
        for (auto &gu:group_user[g])
        {
            if (gu==user_index)
            {
                continue;
            }
            if (temp.count(gu)==0)
            {
                temp[gu]=1;
            }
            else
                temp[gu]+=1;
        }
    }

    //遍历完毕，将其排序

    //结果转换名称，输出进答案
    for(auto ans=temp.begin();ans!=temp.end();ans++)
    {
        const QString friend_name=user_name_dict[ans.key()];
        if (friend_name!=user_name_dict[user_index]&&!(user_friend[user_index].contains(ans.key())))
        res.push_back({friend_name,ans.value()});
    }
    qSort(res.begin(),res.end(),cmp);
    return res;

}
