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
  uint side;
  for(uint x=0; x<m_sizeX; ++x){
    for(uint y=0; y<m_sizeY; ++y){
      useFigure(x,y);
      if(m_figure->isPointInside(point,side)){
        nodeId = y*m_sizeX+x;
        return true;
      }
    }
  }
  return false;
}

const 
Figure* Grid::getFigure(const uint id)
{
  uint x = id%m_sizeX;
  uint y = id/m_sizeX;
  useFigure(x,y);
  return m_figure;
}

map<uint, uint> 
Grid::getAdjacentCells(const uint id)
{
  uint x = id%m_sizeX;
  uint y = id/m_sizeX;

  auto dirs = checkPosibleMoves(x,y);
  map<uint, uint> ans;
  for(auto dir : dirs){
    uint nx = x;
    uint ny = y;
    move(nx,ny,dir);
    ans.insert({dir,ny*m_sizeX+nx});
  }
  return ans;
}

}