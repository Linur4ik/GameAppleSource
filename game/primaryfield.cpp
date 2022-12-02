#include "primaryfield.hpp"

primaryField::primaryField()
  : field(1, 1, 150)
{
  init_cells();
}
//------------------------------------------------------------------------------
void primaryField::init_cells()
{
  mvFields.resize(mLines*mColumns);
  mvFields[0].setAmount(1);
}
