#include "ExelGrid.h"

namespace Harmony{


void
ExelGrid::setValueAt(uint x, uint y, uint value)
{
  //auto coord3D = reinterpret_cast<Coord3D*>(coord);
  auto oneDimPos = x+y*sizeX;
  cells[oneDimPos] = static_cast<EXEL_CELL::E>(cells[oneDimPos] | static_cast<MAZE_CELL::E>(value));
}

uint
ExelGrid::getValueAt(uint x, uint y)
{
  auto oneDimPos = x+y*sizeX;
  return static_cast<unsigned char>(cells[oneDimPos]);
}
void 
ExelGrid::move(uint& x, uint& y, const uint dir)
{
  switch (dir)
  {
  case EXEL_CELL::UP:
    ++y;
    break;

  case EXEL_CELL::DOWN_RIGHT:
    ++x;
    break;

  case EXEL_CELL::UP_RIGHT:
    ++x;
    ++y;
    break;

  case EXEL_CELL::DOWN:
    --y;
    break;

  case EXEL_CELL::UP_LEFT:
    --x;
    break;

  case EXEL_CELL::DOWN_LEFT:
    --x;
    --y;
    break;
  }
}

uint 
ExelGrid::inverse(uint dir)
{
  switch (dir)
  {
  case EXEL_CELL::UP:
    return EXEL_CELL::DOWN;
    break;

  case EXEL_CELL::UP_RIGHT:
    return EXEL_CELL::DOWN_LEFT;
    break;
  case EXEL_CELL::UP_LEFT:
    return EXEL_CELL::DOWN_RIGHT;
    break;

  case EXEL_CELL::DOWN:
    return EXEL_CELL::UP;
    break;

  case EXEL_CELL::DOWN_LEFT:
    return EXEL_CELL::UP_RIGHT;
    break;

  case EXEL_CELL::DOWN_RIGHT:
    return EXEL_CELL::UP_LEFT;
    break;
  }
}

vector<uint> 
ExelGrid::checkMoves(const uint x, const uint y)
{
  vector<uint> ans;
  if(y!=sizeY-1 && getValueAt(x,y+1)!=EXEL_CELL::ALL){
    ans.push_back(EXEL_CELL::UP);
  }
  if(x!=sizeX-1&& getValueAt(x+1,y)!=EXEL_CELL::ALL){
    ans.push_back(EXEL_CELL::DOWN_RIGHT);
  }
  if(x!=sizeX-1 && y!=sizeY-1&& getValueAt(x+1,y+1)!=EXEL_CELL::ALL){
    ans.push_back(EXEL_CELL::UP_RIGHT);
  }
  if(y!=0&& getValueAt(x,y-1)!=EXEL_CELL::ALL){
    ans.push_back(EXEL_CELL::DOWN);
  }
  if(x!=0&& getValueAt(x-1,y)!=EXEL_CELL::ALL){
    ans.push_back(EXEL_CELL::UP_LEFT);
  }
  if(x!=0 && y!=0&& getValueAt(x-1,y-1)!=EXEL_CELL::ALL){
    ans.push_back(EXEL_CELL::DOWN_LEFT);
  }
  return ans;
}

vector<uint> 
ExelGrid::checkMarkedMoves(const uint x, const uint y)
{
  vector<uint> ans;
  if(y!=sizeY-1 && getValueAt(x,y+1)==EXEL_CELL::NONE&& getValueAt(x,y+1)!=EXEL_CELL::ALL){
    ans.push_back(EXEL_CELL::UP);
  }
  if(x!=sizeX-1 && getValueAt(x+1,y)==EXEL_CELL::NONE&& getValueAt(x+1,y)!=EXEL_CELL::ALL){
    ans.push_back(EXEL_CELL::DOWN_RIGHT);
  }
  if(x!=sizeX-1 && y!=sizeY-1 && getValueAt(x+1,y+1)==EXEL_CELL::NONE&& getValueAt(x+1,y+1)!=EXEL_CELL::ALL){
    ans.push_back(EXEL_CELL::UP_RIGHT);
  }
  if(y!=0 && getValueAt(x,y-1)==EXEL_CELL::NONE&& getValueAt(x,y-1)!=EXEL_CELL::ALL){
    ans.push_back(EXEL_CELL::DOWN);
  }
  if(x!=0 && getValueAt(x-1,y)==EXEL_CELL::NONE&& getValueAt(x-1,y)!=EXEL_CELL::ALL){
    ans.push_back(EXEL_CELL::UP_LEFT);
  }
  if(x!=0 && y!=0 && getValueAt(x-1,y-1)==EXEL_CELL::NONE&& getValueAt(x-1,y-1)!=EXEL_CELL::ALL){
    ans.push_back(EXEL_CELL::DOWN_LEFT);
  }
  return ans;
}

vector<uint> 
ExelGrid::checknewMoves(const uint x, const uint y)
{
  vector<uint> ans;
  uint dirs;
  if(y!=sizeY-1){
    dirs = getValueAt(x,y+1);
    if(dirs!=EXEL_CELL::ALL && !(dirs & EXEL_CELL::UP)){
      ans.push_back(EXEL_CELL::UP);
    }
  }
  if(x!=sizeX-1){
    dirs = getValueAt(x+1,y);
    if(dirs!=EXEL_CELL::ALL && !(dirs & EXEL_CELL::DOWN_RIGHT)){
      ans.push_back(EXEL_CELL::DOWN_RIGHT);
    }
  }
  if(x!=sizeX-1 && y!=sizeY-1){
    dirs = getValueAt(x+1,y+1);
    if(dirs!=EXEL_CELL::ALL && !(dirs & EXEL_CELL::UP_RIGHT)){
      ans.push_back(EXEL_CELL::UP_RIGHT);
    }
  }
  if(y!=0){
    dirs = getValueAt(x,y-1); 
    if(getValueAt(x,y-1)!=EXEL_CELL::ALL && !(dirs & EXEL_CELL::DOWN)){
      ans.push_back(EXEL_CELL::DOWN);
    }
  }
  if(x!=0){
    dirs = getValueAt(x-1,y); 
    if(getValueAt(x-1,y)!=EXEL_CELL::ALL && !(dirs & EXEL_CELL::UP_LEFT)){
      ans.push_back(EXEL_CELL::UP_LEFT);
    }
  }
  if(x!=0 && y!=0){
    dirs = getValueAt(x-1,y-1);
    if(getValueAt(x-1,y-1)!=EXEL_CELL::ALL && !(dirs & EXEL_CELL::DOWN_LEFT)){
      ans.push_back(EXEL_CELL::DOWN_LEFT);
    }
  }
  
  return ans;
}


}