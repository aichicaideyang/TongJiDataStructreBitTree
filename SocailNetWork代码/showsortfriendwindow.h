#ifndef SHOWSORTFRIENDWINDOW_H
#define SHOWSORTFRIENDWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QPair>
class ShowSortFriendWindow : public QMainWindow
{
    Q_OBJECT
public:
    //explicit ShowSortFriendWindow(QWidget *parent = nullptr);
    ShowSortFriendWindow(QString now_user,QVector<QPair< QString,int>> &friends);
    void paintEvent(QPaintEvent *);
    QVector<QPair< QString,int>> friends;
    QVector<QString> rank_friends[6];//这里分5级
    int rank_cnt;//总共有多少级
    double base_x;
    double base_y;
    int btn_size;

signals:

};

#endif // SHOWSORTFRIENDWINDOW_H
