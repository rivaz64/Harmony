#include "Grid.h"

namespace Harmony{

void
Grid::getRandomCoords(uint& x, uint& y)
{
  x = rand()%sizeX;
  y = rand()%sizeY;
  while(getValueAt( x,  y) != 0){
    x = rand()%sizeX;
    y = rand()%sizeY;
  }
}

}