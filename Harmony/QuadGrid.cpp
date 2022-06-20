#include "QuadGrid.h"

namespace Harmony{

void
QuadGrid::setValueAt(uint x, uint y, uint value)
{
  auto oneDimPos = x+y*sizeX;
  cells[oneDimPos/2] = static_cast<MAZE_CELL::E>(cells[oneDimPos/2] | static_cast<MAZE_CELL::E>(value<<((oneDimPos%2)*4)));
}

uint 
QuadGrid::getValueAt(uint x, uint y)
{
  auto oneDimPos = x+y*sizeX;
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
  if(y!=sizeY-1 && getValueAt(x,y+1)!=MAZE_CELL::ALL){
    ans.push_back(MAZE_CELL::UP);
  }
  if(x!=sizeX-1  && getValueAt(x+1,y)!=MAZE_CELL::ALL){
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
  if(y!=sizeY-1 && getValueAt(x,y+1)==MAZE_CELL::NONE && getValueAt(x,y+1)!=MAZE_CELL::ALL){
    ans.push_back(MAZE_CELL::UP);
  }
  if(x!=sizeX-1 && getValueAt(x+1,y)==MAZE_CELL::NONE && getValueAt(x+1,y)!=MAZE_CELL::ALL){
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
  if(y!=sizeY-1){
    dirs = getValueAt(x,y+1);
    if(dirs!=MAZE_CELL::ALL && !(dirs & MAZE_CELL::UP) ){
      ans.push_back(MAZE_CELL::UP);
    }
  }
  if(x!=sizeX-1){
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

SurfaceNode 
QuadGrid::getCellAt(Dimencion point)
{
  
}

}