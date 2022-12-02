#include "button.h"


// Класс кнопки.



button::button()
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::MouseButton::LeftButton);
}
//------------------------------------------------------------------------------
QRectF button:: boundingRect() const
{
    return QRectF(0,0,mWidth,mHeigth);
}
//------------------------------------------------------------------------------
void button:: paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) // Рисуем кнопку
{
    if(mHover)
    {
      painter->setPen(QColor(255, 0, 50));
    }
    painter->drawRoundedRect(0,0,mWidth,mHeigth,5,5);
    painter->drawText(mWidth -110 ,mHeigth -8 ,text);
    if(!isEnabled()) // Обводим кнопку красным, если навелись на нее.
    {
      painter->setBrush (QBrush (QColor (255, 255, 255, 180)));
      painter->setPen (Qt::NoPen);
      painter->drawRect (0,0,mWidth, mHeigth);
    }
}
//------------------------------------------------------------------------------
void button:: setGeometry(int aWid,int aHeig) // Установка геометрии кнопки.
{
    mWidth = aWid;
    mHeigth = aHeig;
}
//------------------------------------------------------------------------------
void button:: setText(QString aStr) // Установка текста кнопки.
{
    text=aStr;
}
//------------------------------------------------------------------------------
void button:: hoverEnterEvent(QGraphicsSceneHoverEvent* apEvent)
{
    mHover = true;
    QGraphicsItem::update();
}
//------------------------------------------------------------------------------
void button:: hoverLeaveEvent(QGraphicsSceneHoverEvent* apEvent)
{
    mHover = false;
    QGraphicsItem::update();
}
//------------------------------------------------------------------------------
bool button:: GetHover()
{
    return mHover;
}
//------------------------------------------------------------------------------
void button:: SetHover(bool aBool)
{
    mHover=aBool;
}
//------------------------------------------------------------------------------
void button::enableHoverPos(QPointF aPos)
{
  mHover = true;
  QGraphicsItem::update();
}
//------------------------------------------------------------------------------
void button::disableHover()
{
  mHover = false;
  QGraphicsItem::update();
}
//------------------------------------------------------------------------------
qreal button::xtl()
{
  return x();
}
//------------------------------------------------------------------------------
qreal button::ytl()
{
  return y();
}
//------------------------------------------------------------------------------
qreal button::xbr()
{
  return mWidth+x();
}
//------------------------------------------------------------------------------
qreal button::ybr()
{
  return mWidth+y();
}
