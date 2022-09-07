#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include "socialnetworkmainwindow.h"
//#include "socialnetworkmainwindow.h"
class StartWindow : public QMainWindow
{
    Q_OBJECT
public:
   // explicit StartWindow(QWidget *parent = nullptr);
     StartWindow();
    SocialNetworkMainWindow * socialnetworkMainWindow=NULL;
    void paintEvent(QPaintEvent *);
signals:

};

#endif // STARTWINDOW_H
