#include "field.hpp"





// Класс является родительским, чтобы можно было создавать несколько инвентарей
// Хранит ширину ячейки, кол-во ячеек по гор-ли и вертикали.


field::field(int aLines, int aColumns, int aCellWidth)
  :mLines(aLines)
  ,mColumns(aColumns)
  ,mCellWidth(aCellWidth)
  ,mFieldWidth(aColumns * aCellWidth)
  ,mFieldHeight(aLines * aCellWidth)
{
  setAcceptHoverEvents(true);
  setAcceptedMouseButtons(Qt::MouseButton::LeftButton);
}
//------------------------------------------------------------------------------
QRectF field::boundingRect() const // Подсчет
{
  return QRectF(0, 0, mFieldWidth, mFieldHeight);
}
//------------------------------------------------------------------------------
void field::boundingRectOnSceneCalc() // Подсчет окна относительно общей сцены.
{
  QPointF pos  = scenePos();
  QRectF  rect = boundingRect();

  QPointF topLeft{pos.x() + rect.x(), pos.y() + rect.y()};
  QPointF bottomRight{topLeft.x() + rect.width(),topLeft.y() + rect.height()};

  mBoundingSceneRect.setTopLeft(topLeft);
  mBoundingSceneRect.setBottomRight(bottomRight);
}
//------------------------------------------------------------------------------
qreal field::xtl() // Выдача координа 4х координат объекта.
{
  return mBoundingSceneRect.topLeft().x();
}
//------------------------------------------------------------------------------
qreal field::ytl()
{
  return mBoundingSceneRect.topLeft().y();
}
//------------------------------------------------------------------------------
qreal field::xbr()
{
  return mBoundingSceneRect.bottomRight().x();
}
//------------------------------------------------------------------------------
qreal field::ybr()
{
  return mBoundingSceneRect.bottomRight().y();
}
//------------------------------------------------------------------------------
void field::hoverMoveEvent(QGraphicsSceneHoverEvent *apEvent) // Мышка на объекте
{
  mMousePos = apEvent->pos();
  mHover = true;
  QGraphicsItem::update();
}
//------------------------------------------------------------------------------
void field::hoverLeaveEvent(QGraphicsSceneHoverEvent*) // Мышка покинула объект
{
  mHover = false;
  QGraphicsItem::update();
}
//------------------------------------------------------------------------------
void field::enableHoverPos(QPointF aPos) // Мышь на объекте сохранить координаты и включить флаг
{
  mHover = true;
  mMousePos = mapFromScene(aPos);
  QGraphicsItem::update();
}
//------------------------------------------------------------------------------
void field::disableHover() // Мышь не на объекте сохранить координаты и выключить флаг
{
  mHover = false;
  QGraphicsItem::update();
}
//------------------------------------------------------------------------------
int field:: GetWidth() // Гетр на возвращение ширины ячейки.
{
    return mCellWidth;
}
//------------------------------------------------------------------------------
