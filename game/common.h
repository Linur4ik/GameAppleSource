#ifndef COMMON_H
#define COMMON_H

#include <QPointF>

enum class eDragInfo
{
  Unknown
 ,MainField
 ,Spawn
};

struct sDragData
{
  eDragInfo from;
  int type;
  QPointF   drag_pos;
};

#endif // COMMON_H
