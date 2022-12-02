#ifndef DRAGDRAWOBJ_HPP
#define DRAGDRAWOBJ_HPP

#include <QGraphicsItem>
#include <QPainter>

class dragDrawObj : public QGraphicsItem
{
public:
  dragDrawObj();
  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
  void setPath(QString);
private:
    QString mPath;
};

#endif // DRAGDRAWOBJ_HPP
