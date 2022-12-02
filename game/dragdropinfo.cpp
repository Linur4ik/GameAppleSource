#include "dragdropinfo.hpp"

// Класс, который рисует предмет при перемещении.
// При нажатии левой кнопки мыши и движение мышкой.


dragDropInfo::dragDropInfo()
{
}
//------------------------------------------------------------------------------
dragDropInfo::~dragDropInfo()
{
}
//------------------------------------------------------------------------------
dragDropInfo &dragDropInfo::instance()
{
  static dragDropInfo res;
  return res;
}
//------------------------------------------------------------------------------
bool dragDropInfo::isEmpty()
{
  return mObjectInfo.from == eDragInfo::Unknown;
}
//------------------------------------------------------------------------------
void dragDropInfo::push(sDragData aInfo)
{
  mObjectInfo = aInfo;
}
//------------------------------------------------------------------------------
sDragData dragDropInfo::pop()
{
  sDragData res = mObjectInfo;
  reset();
  return res;
}
//------------------------------------------------------------------------------
void dragDropInfo::reset()
{
  mObjectInfo.from = eDragInfo::Unknown;
}
//------------------------------------------------------------------------------
sDragData dragDropInfo::object()const
{
  return mObjectInfo;
}
