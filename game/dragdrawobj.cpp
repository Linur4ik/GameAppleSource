#include "dragdrawobj.hpp"

// Класс, который рисует предмет при перемещении.
// При нажатии левой кнопки мыши и движение мышкой.


dragDrawObj::dragDrawObj()
{
}
//------------------------------------------------------------------------------
QRectF dragDrawObj::boundingRect() const
{
  return QRectF(0, 0, 150, 150);
}
//------------------------------------------------------------------------------
void dragDrawObj::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) // Рисования предмета
{
  QPixmap pixmap1(mPath);
  painter -> drawPixmap(0,0,150,150, pixmap1);
}
//------------------------------------------------------------------------------
void dragDrawObj::setPath(QString aPath)  // Установка пути для изображения
{
    mPath=aPath;
}
//------------------------------------------------------------------------------
