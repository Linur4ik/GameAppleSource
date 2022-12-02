#include "mainfield.hpp"

// Класс инвентарь унаследован от field
// Хранит базу данных db.
// В базе данных две таблица Invetory, Item.
// Inventory Хранит ID - номер ячейки, Amounts - кол-во элементов в ячейке
// ItemId - внешний ключ от таблицы Item, хранит какой именно предмет хранится в таблице.
// ItemId - NULL, если там нет предметов.
// Item: ItemId - номер предмета, Path - путь для картинки предмета.

mainField::mainField()
  :field(3, 3, 150)
{
    open_database(); // Открываем базу данных
    restartGame(); // Обновляем таблицу
}
//------------------------------------------------------------------------------
bool mainField:: open_database() // Открытие
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("mydatabase.sqlite");
    if(db.open()) return true;
    else return false;
}
//------------------------------------------------------------------------------
bool  mainField:: create_database_inv() // Заполняем таблицу Инвентаря
{
    for(int i = 0; i < mLines*mColumns; ++i)
    {
        QSqlQuery query;

        query.prepare("INSERT INTO Inventory (ID, Amounts, ItemId) "
                       "VALUES (?, ?, ?)");
         query.addBindValue(i);
         query.addBindValue(0);
         query.addBindValue("NULL");
        if(!query.exec()) {return false;}
    }
}
//------------------------------------------------------------------------------
void  mainField::delete_database_inv() // Чистим таблицу Инвентаря
{
    QSqlQuery query;
    query.exec(QString("DELETE FROM Inventory;"));
}
//------------------------------------------------------------------------------
bool  mainField::check_database() // Проверка базы данных на корректность
{
    int c=0;
    QSqlQuery query;
    if(query.exec("SELECT ID FROM Inventory"))
    while (query.next())
    {
        int id = query.value(0).toInt();
        qDebug() << id;
        c++;
    }
    else
    {
        qDebug() << query.lastError().text();
        return false;
    }
    if(c==(mLines*mColumns))
    return true;
    return false;
}
//------------------------------------------------------------------------------
int mainField:: getAmount(int aId) // Возвращает кол-во элементов в ячейке aId
{
    QSqlQuery query;
    query.prepare("SELECT Amounts FROM Inventory where ID = ?");
    query.bindValue(0, aId);
    if(query.exec())
    {
       query.next();
       return query.value(0).toInt();
    }
    return 0;
}
//------------------------------------------------------------------------------
bool mainField:: setAmount(int aId,int aAmount) // Устанавливает кол-во элементов в ячейке aId
{
    QSqlQuery query;
    query.prepare("UPDATE Inventory SET Amounts = ? WHERE ID = ?");
    query.bindValue(0, aAmount);
    query.bindValue(1, aId);
    if(query.exec())
    {
       return true;
    }
    return false;
}
//------------------------------------------------------------------------------
void mainField::set_field(QPointF aPos, int aType) // Определяет в какой ячейке мышь, устанавливает значение в нужную ячейку
{
  QPointF pos = mapFromScene(aPos);
  int c = pos.x()/mCellWidth;
  int l = pos.y()/mCellWidth;
  setAmount(l*mColumns+c,getAmount(l*mColumns+c)+aType);
}
//------------------------------------------------------------------------------
int mainField::getFieldType(const QPointF &aPos) // Определяет в какой ячейке мышь, возвращает значение из нужной ячейки
{
  QPointF pos = mapFromScene(aPos);
  int c = pos.x()/mCellWidth;
  int l = pos.y()/mCellWidth;
  return getAmount(l*mColumns+c);
}
//------------------------------------------------------------------------------
int mainField::take_field(QPointF aPos) // Определяет в какой ячейке мышь, возвращает значение из нужной ячейки, значение из нужной ячейки обнуляется.
{
  QPointF pos = mapFromScene(aPos);
  int c = pos.x()/mCellWidth;
  int l = pos.y()/mCellWidth;
  int res = getAmount(l*mColumns+c);
  setAmount(l*mColumns+c,0);
  return res;
}
//------------------------------------------------------------------------------
void  mainField::decField(QPointF aPos) // Опередяет в какой ячейке съели яблоко, уменьшает кол-во яблок.
{
  QPointF pos = mapFromScene(aPos);
  int c = pos.x()/mCellWidth;
  int l = pos.y()/mCellWidth;
  int res= getAmount(l*mColumns+c);
  if(res>0) setAmount(l*mColumns+c,res-1);
}
//------------------------------------------------------------------------------
bool mainField::fieldIsEmpty(const QPointF &aPos) // Проверка на пустоту ячейки
{
  return getFieldType(aPos) == 0;
}
//------------------------------------------------------------------------------
void mainField::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) // Функция рисования.
{
  // Рисуем таблицу.
  for(int l = 0; l <= mLines; ++l)
    painter->drawLine(QLineF(0, l*mCellWidth, mFieldWidth, l*mCellWidth));

  for(int c = 0; c <= mColumns; ++c)
    painter->drawLine(QLineF(c*mCellWidth, 0, c*mCellWidth, mFieldHeight));

  _draw_cells(painter); // Рисуем картинку

  if(!isEnabled()) // Если объект выключен, закрашиваем серым квадратом.
  {
    for(int l = 0; l < mLines; ++l)
    {
        for(int c = 0; c < mColumns; ++c)
        {
            painter->setBrush (QBrush (QColor (255, 255, 255, 180)));
            painter->setPen (Qt::NoPen);
            painter->drawRect (c*mCellWidth,l*mCellWidth,149, 149);
        }
    }
  }

  if(mHover) // Если мышь на ячейке, подсвечиваем красным цветом.
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
void mainField::_draw_cells(QPainter *painter) // Рисуем картинку и цифры.
{
  for(int l = 0; l < mLines; ++l)
  {
    for(int c = 0; c < mColumns; ++c)
    {
        if(getAmount(l*mColumns + c)>0)
        {
            QPixmap pixmap1(GetPath(getItemID((l*mColumns+c))));
            painter -> drawPixmap(c*mCellWidth,l*mCellWidth,149,149, pixmap1);
        }
        if(Numbers) painter->drawText(c*mCellWidth + mCellWidth - 15, l*mCellWidth + mCellWidth - 5,QString :: number (getAmount(l*mColumns + c)));
    }
  }
}
//------------------------------------------------------------------------------
int mainField:: getItemID(int aId) // Возвращает ItemId из ячейки aId
{
    QSqlQuery query;
    query.prepare("SELECT ItemId FROM Inventory where ID = ?");
    query.bindValue(0, aId);
    if(query.exec())
    {
       query.next();
       return query.value(0).toInt();
    }
    return 0;
}
//------------------------------------------------------------------------------
bool mainField:: setItemID(int aId,int aItem) // Устанавливает ItemId = aItem из ячейки aId
{
    QSqlQuery query;
    query.prepare("UPDATE Inventory SET ItemId = ? WHERE ID = ?");
    if(aItem==-1) query.bindValue(0, "NULL");
        else
    query.bindValue(0, aItem);
    query.bindValue(1, aId);
    if(query.exec())
    {
       return true;
    }
    return false;
}
//------------------------------------------------------------------------------
int mainField::getFieldItemId(const QPointF &aPos) // Возвращает ItemId, по координатам.
{
  QPointF pos = mapFromScene(aPos);
  int c = pos.x()/mCellWidth;
  int l = pos.y()/mCellWidth;
  return getItemID(l*mColumns+c);
}
//------------------------------------------------------------------------------
void mainField::setFieldItemId(QPointF aPos, int aType) // Устанавливает ItemId, по координатам.
{
  QPointF pos = mapFromScene(aPos);
  int c = pos.x()/mCellWidth;
  int l = pos.y()/mCellWidth;
  setItemID(l*mColumns+c,aType);
}
//------------------------------------------------------------------------------
QString mainField:: GetPath(int aItemId) // Возвращает путь картинки для предмета aItemId.
{
    QSqlQuery query;
    query.prepare("SELECT Path FROM Item where ItemId = ?");
    query.bindValue(0, aItemId);
    if(query.exec())
    {
       query.next();
       return query.value(0).toString();
    }
    return 0;
}
//------------------------------------------------------------------------------
void mainField:: restartGame() // Перезапуск игры.
{
    delete_database_inv();
    create_database_inv();
    delete_database_Item();
    create_database_Item();
}
//------------------------------------------------------------------------------
void mainField:: setItemId(int aId) // Сетр на ИтемИд
{
    mItemId=aId;
}
//------------------------------------------------------------------------------
bool mainField:: create_database_Item() // Заполнение таблицы Итем
{
    QSqlQuery query;
    query.prepare("INSERT INTO Item (ItemId, Path) "
                       "VALUES (?, ?)");
    query.addBindValue(mItemId);
    query.addBindValue("ap.png");
    if(!query.exec()) { qDebug() <<  db.lastError();return false;}
}
//------------------------------------------------------------------------------
void mainField:: delete_database_Item() // Чистка Итем
{
    QSqlQuery query;
    if(!query.exec(QString("DELETE FROM Item;"))) qDebug() <<  db.lastError();
}
//------------------------------------------------------------------------------
mainField:: ~mainField() // Деструктор на закрытие базы данных
{
    db.close();
}
