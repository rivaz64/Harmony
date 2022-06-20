#include "Grid.h"
#include "Figure.h"

namespace Harmony{

void
Grid::getRandomCoords(uint& x, uint& y)
{
  x = rand()%m_sizeX;
  y = rand()%m_sizeY;
  while(getValueAt( x,  y) != 0){
    x = rand()%m_sizeX;
    y = rand()%m_sizeY;
  }
}

bool 
Grid::getCellAt(const Dimencion& point, uint& nodeId)
{
  for(uint x=0; x<m_sizeX; ++x){
    for(uint y=0; y<m_sizeY; ++y){
      figure.se
    }
  }
}

}