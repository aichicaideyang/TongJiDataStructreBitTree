#ifndef SHOWUSERFRIENDWINDOW_H
#define SHOWUSERFRIENDWINDOW_H

#include <QMainWindow>
#include <QSet>
class ShowUserFriendWindow:public QMainWindow
{
public:
    ShowUserFriendWindow(QString now_user,QSet<QString> &friends);
    void paintEvent(QPaintEvent *);
    QSet<QString> friends;//只需要存储一个users即可
    double base_x;
    double base_y;
    int btn_size;
};

#endif // SHOWUSERFRIENDWINDOW_H
