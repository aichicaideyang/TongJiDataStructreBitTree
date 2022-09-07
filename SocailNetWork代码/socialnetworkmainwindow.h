#ifndef SOCIALNETWORKMAINWINDOW_H
#define SOCIALNETWORKMAINWINDOW_H

#include <QMainWindow>
#include "socialmap.h"
#include "mapbutton.h"
namespace Ui {
class SocialNetworkMainWindow;
}
class StartWindow;
class SocialNetworkMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SocialNetworkMainWindow(QWidget *parent = nullptr);
    //SocialNetworkMainWindow();
    ~SocialNetworkMainWindow();
    void paintEvent(QPaintEvent *);
    void paintBtn();
    void close_btn();
private:
    int now_user_idx;//当前用户下标
    Ui::SocialNetworkMainWindow *ui;
    SocialMap *socialMap;
    MapButton * map_btn[N];
    int map_btn_cnt;//记录结点数量，方便分配 以及关闭
    double base_x;
    double base_y;
    int map_btn_size;
    friend StartWindow;
signals:
    void back();
};

#endif // SOCIALNETWORKMAINWINDOW_H
