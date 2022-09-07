#ifndef SOCIALMAP_H
#define SOCIALMAP_H

#include <QWidget>



/* 一些宏定义 */
#define TRUE 1
#define FALSE 0
#define OK  1
#define ERROR 0
#define OVERFLOW -1
typedef int Status;
#include <QMap>
#include <QSet>
#include <QVector>
#include <QPair>
#include <algorithm>
//常量定义

#define N 1000 //最大操作100个人
#define M 100 //最大操作100个组织

class SocialNetworkMainWindow;

class StartWindow;
//存储整张网络的所有信息

class SocialMap
{
private:
    int user_counts=0;//人数总标号，用于分配人的下标
    int group_counts=0;//组织总标号，用于分配组织的下标
    QMap< QString,int> user_index_dict; //用户下标字典
    QMap<int, QString> user_name_dict;// 用户姓名字典
    QMap< QString,int> group_index_dict;//组织下标字典
    QMap<int, QString> group_name_dict;//组织名称字典
    QSet<int> user_friend[N]; //用户好友集合
    QSet<int> user_group[N]; //用户组织集合
    QSet<int> group_user[N];// 组织用户集合

public:
    SocialMap();
    ~SocialMap();
    //添加成员
    Status addUser( QString user_name);
    //添加组织
    Status addGroup( QString group_name);
    //添加好友
    Status addFriend( QString user_name, QString friend_name );
    //添加组织成员
    Status addGroupMember( QString group_name, QString user_name);

    //一些外部接口
    //根据姓名获取用户下标
    int get_user_index( QString user_name);
    //根据名称获取组织下标
    int get_group_index( QString group_name);
    //根据下标获取用户好友set
    QSet<int> get_user_friend(int user_index);
    //根据下标获取用户组织set
    QSet<int> get_user_group(int user_index);
    //根据下标获取组织用户set
    QSet<int> get_group_user(int group_index);
    //对一个用户的所有好友进行排序，并返回权值和姓名
    QVector<QPair< QString,int>> get_user_weighted_friend(int user_index);
    //辅助好友排序函数
    static bool cmp(QPair< QString,int> &user_1,QPair< QString,int>&user_2);
    friend  SocialNetworkMainWindow;
    friend  StartWindow;
};

#endif // SOCIALMAP_H
