#include "spawn.h"

// Класс спавна предмета.
// Функционал очень схож с классом mainfield

Spawn::Spawn()
{
    mCellWidth = 150;
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::MouseButton::LeftButton);
}
//------------------------------------------------------------------------------
QRectF Spawn::boundingRect() const
{
  return QRectF(0, 0, mCellWidth, mCellWidth);
}
//------------------------------------------------------------------------------
void Spawn::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  for(int l = 0; l <= 1; ++l)
    painter->drawLine(QLineF(0, l*mCellWidth, mCellWidth, l*mCellWidth));

  for(int c = 0; c <= 1; ++c)
    painter->drawLine(QLineF(c*mCellWidth, 0, c*mCellWidth, mCellWidth));

  drow_cells(painter);

  if(!isEnabled())
  {
    painter->setBrush (QBrush (QColor (255, 255, 255, 180)));
    painter->setPen (Qt::NoPen);
    painter->drawRect (0,0,149, 149);
  }
  if(mHover)
  {
    int x = mMousePos.x()/mCellWidth;
    int y = mMousePos.y()/mCellWidth;
    painter->setPen(QColor(255, 0, 0));
    painter->drawRoundedRect(x*mCellWidth,
                             y*mCellWidth,
                             mCellWidth,
                             mCellWidth,
                             2, 2);
  }
}
//------------------------------------------------------------------------------
void Spawn:: drow_cells(QPainter *painter)
{
    QPixmap pixmap1(mPath);
    painter -> drawPixmap(0,0,149,149, pixmap1);
}

//------------------------------------------------------------------------------
qreal Spawn::xtl()
{
  return x();
}
//------------------------------------------------------------------------------
qreal Spawn::ytl()
{
  return y();
}
//------------------------------------------------------------------------------
qreal Spawn::xbr()
{
  return mCellWidth+x();
}
//------------------------------------------------------------------------------
qreal Spawn::ybr()
{
  return mCellWidth+y();
}
//------------------------------------------------------------------------------
void Spawn::hoverMoveEvent(QGraphicsSceneHoverEvent *apEvent)
{
  mMousePos = apEvent->pos();
  mHover = true;
  QGraphicsItem::update();
}
//------------------------------------------------------------------------------
void Spawn::hoverLeaveEvent(QGraphicsSceneHoverEvent*)
{
  mHover = false;
  QGraphicsItem::update();
}
//------------------------------------------------------------------------------
void Spawn::enableHoverPos(QPointF aPos)
{
  mHover = true;
  mMousePos = mapFromScene(aPos);
  QGraphicsItem::update();
}
//------------------------------------------------------------------------------
void Spawn::disableHover()
{
  mHover = false;
  QGraphicsItem::update();
}
//------------------------------------------------------------------------------
void Spawn:: SetPath(QString aPath)
{
    mPath=aPath;
}
//------------------------------------------------------------------------------
