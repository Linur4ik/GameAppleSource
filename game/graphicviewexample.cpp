#include "graphicviewexample.hpp"


graphicViewExample::graphicViewExample()
{
  // Рисуем окно и создаем сцену.
  setRenderHint(QPainter::Antialiasing);
  setCacheMode(QGraphicsView::CacheNone);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setWindowTitle("Inventory");
  setFrameStyle(0);
  setFixedSize(1000, 1000);
  setSceneRect(0, 0, 1000, 1000);
  setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
  QApplication::setWindowIcon( QIcon( "ap" ) );
  setScene(&mScene);
}


