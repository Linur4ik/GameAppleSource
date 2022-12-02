#ifndef SPAWN_H
#define SPAWN_H

#include <QGraphicsItem>
#include <QVector>
#include "common.h"
#include <QtSql>
#include <QPainter>
#include <QGraphicsSceneHoverEvent>

class Spawn : public QGraphicsItem
{
public:
    Spawn();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void hoverMoveEvent(QGraphicsSceneHoverEvent*) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*) override;

    void enableHoverPos(QPointF);
    void disableHover();

    void drow_cells(QPainter*);
    void SetPath(QString);

    qreal xtl();
    qreal ytl();
    qreal xbr();
    qreal ybr();

protected:
    int     mCellWidth{0};
    int     mFieldWidth{0};
    int     mFieldHeight{0};
    QString mPath;
    bool    mHover{false};
    QPointF mMousePos;
};

#endif // SPAWN_H
