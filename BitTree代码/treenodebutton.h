#ifndef TREENODEBUTTON_H
#define TREENODEBUTTON_H

#include <QPushButton>

class TreeNodeButton : public QPushButton
{
    Q_OBJECT
public:
   // explicit TreeNodeButton(QWidget *parent = nullptr);

     QString normalImgPath=":/src/Coin0001.png";
     QString shineImgPath=":/src/Coin0008.png";
   TreeNodeButton(double radius,QString imgPath=":/src/Coin0001.png");
   bool active=1;
   void mousePressEvent(QMouseEvent *e);
signals:

};

#endif // TREENODEBUTTON_H
