#ifndef MAPBUTTON_H
#define MAPBUTTON_H

#include <QPushButton>
#include <QLabel>
class MapButton: public QPushButton
{
    Q_OBJECT
public:
   QString normalImgPath=":/src/Coin0001.png";
   QString shineImgPath=":/src/Coin0008.png";
  QLabel *info;
  MapButton(int x,int y,QString info_txt="",double radius=1,QString imgPath=":/src/Coin0001.png");
  bool active=1;
  void mousePressEvent(QMouseEvent *e);
  ~MapButton();
};

#endif // MAPBUTTON_H
