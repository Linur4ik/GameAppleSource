#include "mainscene.hpp"

bool distanceIsMoving(QPointF aPoint) // Функция, которая проверяет двинулся курсор или нет.
{
  return aPoint.manhattanLength() > QApplication::startDragDistance();
}
//------------------------------------------------------------------------------
mainScene::mainScene() // Иннициализируем сцену
{
  setItemIndexMethod(QGraphicsScene::NoIndex);
  _init_main_field(); // Иннициализируем поле Инвентаря
  _init_spawn(mMainField.GetPath(mItemId)); // Иннициализируем поле Спавна предмета
  init_button(); // Иннициализируем Кнопки: Старт,Выход,главное меню
  mMainField.setEnabled(false); // Делаем неактивными инвентарь,спавн и кнопку меню.
  mSpawn.setEnabled(false);
  buttonMenu.setEnabled(false);
  mDragDrawObj.hide(); // Прячем картинку возникающую при переносе.
  mDragDrawObj.setPath(mMainField.GetPath(mItemId)); // Указываем путь для картинки во время переноса.
  addItem(&mDragDrawObj); // Добавляем предмет на сцену.
}
//------------------------------------------------------------------------------
// Иннициализация инвентаря. Задаются координаты и добавляется на сцену.
void mainScene::_init_main_field()
{
  mMainField.setPos(xMain,yMain);
  mMainField.setItemId(mItemId);
  mMainField.boundingRectOnSceneCalc();
  addItem(&mMainField);
}
//------------------------------------------------------------------------------
// Обрабатывание нажатия кнопок.
void mainScene::mousePressEvent(QGraphicsSceneMouseEvent *apEvent)
{
  if(apEvent->button() == Qt::LeftButton) // Нажатие левой кнопки мыши
  {
    const QPointF &pos  = apEvent->scenePos();
    dragDropInfo &ddi = dragDropInfo::instance();

    if(buttonExit.GetHover() && !enabled) // Нажали на выход
    {
        exit(0);
    }
    if(buttonStart.GetHover() && !enabled) // Нажали на Старт
    {
       enabled=true;
       mMainField.setEnabled(true);
       mSpawn.setEnabled(true);
       buttonMenu.setEnabled(true);
       buttonStart.SetHover(false);
       buttonStart.setEnabled(false);
       buttonExit.setEnabled(false);
       buttonStart.hide();
       buttonExit.hide();
       mMainField.restartGame();
    }

    if(!enabled) return;
    if(buttonMenu.GetHover()) // Нажали на меню
    {
       mMainField.setEnabled(false);
       mSpawn.setEnabled(false);
       buttonMenu.setEnabled(false);
       buttonMenu.SetHover(false);
       buttonStart.setEnabled(true);
       buttonExit.setEnabled(true);
       enabled=false;
       buttonStart.show();
       buttonExit.show();
    }

    if(_is_moving_hover_main_field(pos)) // Нажали на инвентарь
    {
      if(!mMainField.fieldIsEmpty(pos))
        ddi.push({eDragInfo::MainField, mMainField.getFieldType(pos), pos});
    }
    else if(_is_moving_hover_spawn(pos)) // Нажали на спавн предмета
    {
        ddi.push({eDragInfo::Spawn, 1, pos});
    }
    if(!ddi.isEmpty()) // Рисуем картинку при клике
    {
      if(_is_moving_hover_spawn(pos))  // Клик на спавне
      {
        mMouseLeftClickPos = apEvent->scenePos();
        QPointF q(xPrim,yPrim);
        mDragDrawObj.setPos(q);
        mDragDrawObj.show();
      }
      if(_is_moving_hover_main_field(pos)) // Клик на инвентаре
      {
        mMouseLeftClickPos = apEvent->scenePos();
        int x = (mMouseLeftClickPos.x()-xMain)/mMainField.GetWidth();
        int y = (mMouseLeftClickPos.y()-yMain)/mMainField.GetWidth();
        x=x*mMainField.GetWidth()+xMain;
        y=y*mMainField.GetWidth()+yMain;
        x1=mMouseLeftClickPos.x()-x;
        y1=mMouseLeftClickPos.y()-y;
        QPointF q(x,y);
        mDragDrawObj.setPos(q);
        mDragDrawObj.show();
      }

      mLeftBtnPressed = true;
    }
    QGraphicsScene::mousePressEvent(apEvent);
  }
  if(apEvent->button() == Qt::RightButton) // Правая кнопка мыши.
  {
      if(!enabled) return;
      const QPointF &pos  = apEvent->scenePos();
      if(_is_moving_hover_main_field(pos)) // Правая кнопка мыши на поле инвентаря.
      {
        RightClick(pos);
      }
  QGraphicsScene::mousePressEvent(apEvent);
  }
}
//------------------------------------------------------------------------------
void mainScene::mouseMoveEvent(QGraphicsSceneMouseEvent *apEvent) // Процесс переноса мышки.
{
  bool mainHover    = _is_moving_hover_main_field(apEvent->scenePos());
  bool spawnHover = _is_moving_hover_spawn(apEvent->scenePos());

  dragDropInfo &ddi = dragDropInfo::instance();

  if(mLeftBtnPressed) // Левая кнопка зажата
  {
    if(!ddi.isEmpty())
    {
      if(distanceIsMoving(apEvent->pos() - mMouseLeftClickPos))
      {
        if(_is_moving_hover_spawn(mMouseLeftClickPos)) // Мышь движется со спавна
        {
            QPointF q(xPrim,yPrim);
            mDragDrawObj.setPos(apEvent->scenePos()+ q - mMouseLeftClickPos);
        }
        if(_is_moving_hover_main_field(mMouseLeftClickPos)) // Мышь движется с инвентаря
        {
            QPointF q(x1,y1);
            mDragDrawObj.setPos(apEvent->scenePos()- q);
        }

        if(mainHover)
          mMainField.enableHoverPos(apEvent->scenePos());
        if(spawnHover)
          mSpawn.enableHoverPos(apEvent->scenePos());
      }
    }
  }
    QGraphicsScene::mouseMoveEvent(apEvent);
}
//------------------------------------------------------------------------------
bool mainScene::_is_moving_hover_main_field(const QPointF &aPos) // В функцию передается позиция, возвращает находится ли данная позиция в объекте инвентаря
{
  return (aPos.x() >= mMainField.xtl())
      && (aPos.x() <= mMainField.xbr())
      && (aPos.y() >= mMainField.ytl())
      && (aPos.y() <= mMainField.ybr());
}
//------------------------------------------------------------------------------
void mainScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *apEvent) // Мышь отпустили.
{
  if(!enabled) return;

  const QPointF &pos = apEvent->scenePos();

  dragDropInfo &ddi = dragDropInfo::instance();
  if(!ddi.isEmpty())
  {
    if(_is_moving_hover_main_field(pos)) // Мышь на инвентаре
    {
      if(ddi.object().from == eDragInfo::Spawn)
      {
          _move_from_spawn_to_main(ddi.object(), pos); // Перенос со спавна в инвентарь
          mSpawn.disableHover();
      }
      if(ddi.object().from == eDragInfo::MainField)
      {
          move_from_main_to_main(ddi.object(), pos); // Перенос с инвентаря в инвентарь
          mMainField.disableHover();
      }
    } 
    ddi.reset();
  }

  mDragDrawObj.hide();
  mLeftBtnPressed = false;
  QGraphicsScene::mouseReleaseEvent(apEvent);

  update();
}
//------------------------------------------------------------------------------
void mainScene::_move_from_spawn_to_main(sDragData aFrom, QPointF aPos) // Перенос со спавна в инвентарь
{
  mMainField.set_field(aPos, 1); // Переносится один элемент
  mMainField.setFieldItemId(aPos,mItemId);
}
//------------------------------------------------------------------------------
void mainScene:: move_from_main_to_main(sDragData aFrom, QPointF aPos) // Перенос в инвентаре
{
  int k = mMainField.getFieldItemId(aFrom.drag_pos);
  mMainField.setFieldItemId(aPos,k); // Перенос ItemId в новую ячейку
  mMainField.setFieldItemId(aFrom.drag_pos,-1); // Прошлая ячейка ItemId = NULL
  int t = mMainField.take_field(aFrom.drag_pos);
  mMainField.set_field(aPos, t); // Переносим все элементы из прошлой в новую
}
//------------------------------------------------------------------------------
void mainScene:: RightClick(QPointF aPos) // Нажатие правой кнопки мыши
{
    mMainField.decField(aPos); // Съедаем яблоко
    PlayApple(); // Запускаем звук
}
//------------------------------------------------------------------------------
void mainScene:: init_button() // Создаем кнопки
{
    buttonMenu.setPos(710,400);
    buttonMenu.setGeometry(150,24);
    buttonMenu.setText("Главное меню");
    addItem(&buttonMenu);

    buttonStart.setPos(300,10);
    buttonStart.setGeometry(180,24);
    buttonStart.setText("Старт");
    addItem(&buttonStart);

    buttonExit.setPos(500,10);
    buttonExit.setGeometry(180,24);
    buttonExit.setText("Выход");
    addItem(&buttonExit);
}
//------------------------------------------------------------------------------
void mainScene:: PlayApple() // Запуск звука
{
    QMediaPlayer *player = new QMediaPlayer;
    QAudioOutput *audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl::fromLocalFile("ukus.mp3"));
    audioOutput->setVolume(50);
    player->play();
}
//------------------------------------------------------------------------------
void mainScene::_init_spawn(QString aPath) // Создание спавна
{
    mSpawn.setPos(xPrim, yPrim);\
    mSpawn.SetPath(aPath);
    addItem(&mSpawn);
}
//------------------------------------------------------------------------------
bool mainScene::_is_moving_hover_spawn(const QPointF &aPos) // Мышь находится на спавне или нет.
{
    return (aPos.x() >= mSpawn.xtl())
        && (aPos.x() <= mSpawn.xbr())
        && (aPos.y() >= mSpawn.ytl())
        && (aPos.y() <= mSpawn.ybr());
}
