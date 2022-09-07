#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include "bittreemainwindow.h"
class StartWindow : public QMainWindow
{
    Q_OBJECT
public:
   // explicit StartWindow(QWidget *parent = nullptr);
     StartWindow();
    BitTreeMainWindow * bitTreeMainWindow=NULL;
    void paintEvent(QPaintEvent *);
signals:

};

#endif // STARTWINDOW_H
