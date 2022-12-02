#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsItem>
#include <QPainter>

class button : public QGraphicsItem
{
public:
    button();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setGeometry(int,int);
    void setText(QString);
    void hoverEnterEvent(QGraphicsSceneHoverEvent*) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*) override;
    bool GetHover();
    void SetHover(bool);
    void enableHoverPos(QPointF);
    void disableHover();
    bool GetClicked();
    qreal xtl();
    qreal ytl();
    qreal xbr();
    qreal ybr();
private:
    bool mHover{false};
    int mWidth{0};
    int mHeigth{0};
    QString text{""};
};

#endif // BUTTON_H
