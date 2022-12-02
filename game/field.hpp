#ifndef FIELD_HPP
#define FIELD_HPP

#include <QGraphicsItem>
#include <QVector>
#include "common.h"
#include <QtSql>
#include <QPainter>
#include <QGraphicsSceneHoverEvent>

class field : public QGraphicsItem
{
public:
  field(int, int, int);
  QRectF boundingRect() const override;
  void hoverMoveEvent(QGraphicsSceneHoverEvent*) override;
  void hoverLeaveEvent(QGraphicsSceneHoverEvent*) override;
  void enableHoverPos(QPointF);
  void disableHover();
  bool fieldIsEmpty(const QPointF&);
  int getFieldType(const QPointF&);
  void boundingRectOnSceneCalc();
  qreal xtl();
  qreal ytl();
  qreal xbr();
  qreal ybr();
  int GetWidth();
protected:
  int     mLines{0};
  int     mColumns{0};
  int     mCellWidth{0};
  int     mFieldWidth{0};
  int     mFieldHeight{0};
  bool    mHover{false};
  bool    Numbers{true};
  QPointF mMousePos;
  QRectF  mBoundingSceneRect;
};

#endif // FIELD_HPP
