#ifndef MAINSCENE_HPP
#define MAINSCENE_HPP

#include <QGraphicsScene>
#include "button.h"
#include "dragdrawobj.hpp"
#include "mainfield.hpp"
#include <QSqlDatabase>
#include "spawn.h"
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <QDebug>
#include <QGraphicsTransform>
#include "dragdropinfo.hpp"
#include <QMediaPlayer>
#include <QAudioOutput>
#include <stdlib.h>


class mainScene : public QGraphicsScene
{
public:
  mainScene();

  void mousePressEvent(QGraphicsSceneMouseEvent *)  override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent *)   override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *)override;

private:
  void _init_main_field();
  void _init_spawn(QString);
  void init_button();

  bool _is_moving_hover_main_field(const QPointF&);
  bool _is_moving_hover_button(const QPointF&);
  bool _is_moving_hover_spawn(const QPointF &aPos);

  void _move_from_spawn_to_main(sDragData, QPointF);
  void  move_from_main_to_main(sDragData, QPointF);
  void RightClick(QPointF);
  void PlayApple();

private:
  bool  mLeftBtnPressed{false};
  int x1,y1;
  int xMain = 50,yMain = 225,xPrim = 710,yPrim = 225;
  QPointF       mMouseLeftClickPos;
  mainField     mMainField;
  Spawn mSpawn;
  dragDrawObj   mDragDrawObj;
  int mItemId{0};
  button buttonExit;
  button buttonMenu;
  button buttonStart;
  bool enabled{false};
};

#endif // MAINSCENE_HPP
