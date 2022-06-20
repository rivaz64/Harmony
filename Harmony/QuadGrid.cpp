#include "QuadGrid.h"
#include "Quad.h"
namespace Harmony{
QuadGrid::QuadGrid(uint x, uint y, float cellSize, const Dimencion& ofset)
{
  m_sizeX = x;
  m_sizeY = y;
  cells.clear();
  cells.resize((x*y)/2);
  m_figure = new Quad();
  m_offset = ofset;
  reinterpret_cast<Quad*>(m_figure)->setSize(cellSize);
}
void
QuadGrid::setValueAt(uint x, uint y, uint value)
{
  auto oneDimPos = x+y*m_sizeX;
  cells[oneDimPos/2] = static_cast<MAZE_CELL::E>(cells[oneDimPos/2] | static_cast<MAZE_CELL::E>(value<<((oneDimPos%2)*4)));
}

uint 
QuadGrid::getValueAt(uint x, uint y)
{
  auto oneDimPos = x+y*m_sizeX;
  return static_cast<unsigned char>((cells[oneDimPos/2]>>((oneDimPos%2)*4))%16);
}

void 
QuadGrid::move(uint& x, uint& y, const uint dir)
{
  switch (dir)
  {
  case MAZE_CELL::UP:
    ++y;
    break;

  case MAZE_CELL::RIGHT:
    ++x;
    break;

  case MAZE_CELL::DOWN:
    --y;
    break;

  case MAZE_CELL::LEFT:
    --x;
    break;
  }
}

uint
QuadGrid::inverse(uint dir)
{
  switch (dir)
  {
  case MAZE_CELL::UP:
    return MAZE_CELL::DOWN;
    break;

  case MAZE_CELL::RIGHT:
    return MAZE_CELL::LEFT;
    break;

  case MAZE_CELL::DOWN:
    return MAZE_CELL::UP;
    break;

  case MAZE_CELL::LEFT:
    return MAZE_CELL::RIGHT;
    break;
  }
}

vector<uint> 
QuadGrid::checkMoves(const uint x, const uint y)
{
  vector<uint> ans;
  if(y!=m_sizeY-1 && getValueAt(x,y+1)!=MAZE_CELL::ALL){
    ans.push_back(MAZE_CELL::UP);
  }
  if(x!=m_sizeX-1  && getValueAt(x+1,y)!=MAZE_CELL::ALL){
    ans.push_back(MAZE_CELL::RIGHT);
  }
  if(y!=0 && getValueAt(x,y-1)!=MAZE_CELL::ALL){
    ans.push_back(MAZE_CELL::DOWN);
  }
  if(x!=0 && getValueAt(x-1,y)!=MAZE_CELL::ALL){
    ans.push_back(MAZE_CELL::LEFT);
  }

  return ans;
}

vector<uint> 
QuadGrid::checkMarkedMoves(const uint x, const uint y)
{
  vector<uint> ans;
  if(y!=m_sizeY-1 && getValueAt(x,y+1)==MAZE_CELL::NONE && getValueAt(x,y+1)!=MAZE_CELL::ALL){
    ans.push_back(MAZE_CELL::UP);
  }
  if(x!=m_sizeX-1 && getValueAt(x+1,y)==MAZE_CELL::NONE && getValueAt(x+1,y)!=MAZE_CELL::ALL){
    ans.push_back(MAZE_CELL::RIGHT);
  }
  if(y!=0 && getValueAt(x,y-1)==MAZE_CELL::NONE&& getValueAt(x,y-1)!=MAZE_CELL::ALL){
    ans.push_back(MAZE_CELL::DOWN);
  }
  if(x!=0 && getValueAt(x-1,y)==MAZE_CELL::NONE&& getValueAt(x-1,y)!=MAZE_CELL::ALL){
    ans.push_back(MAZE_CELL::LEFT);
  }

  return ans;
}

vector<uint> 
QuadGrid::checknewMoves(const uint x, const uint y)
{
  vector<uint> ans;
  uint dirs;
  if(y!=m_sizeY-1){
    dirs = getValueAt(x,y+1);
    if(dirs!=MAZE_CELL::ALL && !(dirs & MAZE_CELL::UP) ){
      ans.push_back(MAZE_CELL::UP);
    }
  }
  if(x!=m_sizeX-1){
    dirs = getValueAt(x+1,y);
    if(dirs!=MAZE_CELL::ALL && !(dirs & MAZE_CELL::RIGHT)){
      ans.push_back(MAZE_CELL::RIGHT);
    }
  }
  
  if(y!=0){
    dirs = getValueAt(x,y-1);
    if(dirs!=MAZE_CELL::ALL && !(dirs & MAZE_CELL::DOWN)){
      ans.push_back(MAZE_CELL::DOWN);
    }
  }

  if(x!=0){
    dirs = getValueAt(x-1,y);
    if(dirs!=MAZE_CELL::ALL && !(dirs & MAZE_CELL::LEFT)){
      ans.push_back(MAZE_CELL::LEFT);
    }
  }
  
  return ans;
}

void
QuadGrid::useFigure(const uint x, const uint y)
{
  auto cellSize = reinterpret_cast<Quad*>(m_figure)->getSize();
  m_figure->setCenter({static_cast<float>(x)*cellSize+cellSize*.5f+m_offset.x,
                       static_cast<float>(y)*cellSize+cellSize*.5f+m_offset.y});
}

}