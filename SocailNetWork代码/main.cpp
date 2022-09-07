#include "startwindow.h"

#include <QApplication>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartWindow w;

   //· QApplication::setQuitOnLastWindowClosed(false);

    w.show();
    return a.exec();
}
