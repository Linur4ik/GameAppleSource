#ifndef MAINFIELD_HPP
#define MAINFIELD_HPP

#include "field.hpp"
#include <QPainter>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsItem>
#include <QSqlDatabase>
#include <QtSql>

class mainField : public field
{
public:
  mainField();
  ~mainField();
  bool open_database();
  bool create_database_inv();
  void delete_database_inv();
  bool create_database_Item();
  void delete_database_Item();
  bool check_database();
  int getAmount(int);
  bool setAmount(int,int);
  int take_field(QPointF);
  void set_field(QPointF, int);
  void decField(QPointF);
  int getFieldType(const QPointF&);
  bool fieldIsEmpty(const QPointF &aPos);
  void _draw_cells(QPainter *painter);
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
  bool setItemID(int,int);
  int getItemID(int);
  int getFieldItemId(const QPointF &);
  void setFieldItemId(QPointF,int);
  QString GetPath(int);
  void restartGame();
  void setItemId(int);
private:
  QSqlDatabase db;
  int mItemId{0};
};

#endif // MAINFIELD_HPP
