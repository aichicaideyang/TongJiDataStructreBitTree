#ifndef SHOWGROUPUSERWINDOW_H
#define SHOWGROUPUSERWINDOW_H

#include <QMainWindow>
#include <QSet>
class ShowGroupUserWindow:public QMainWindow
{
public:
    ShowGroupUserWindow(QString now_group,QSet<QString> &users);
    void paintEvent(QPaintEvent *);
    QSet<QString> users;//只需要存储一个users即可
    double base_x;
    double base_y;
    int btn_size;
};

#endif // SHOWGROUPUSERWINDOW_H
