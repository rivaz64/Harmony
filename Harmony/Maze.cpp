#include "Maze.h"

namespace Harmony{

inline MAZE_CELL::E 
operator| (MAZE_CELL::E lhs, MAZE_CELL::E rhs)
{
  return static_cast<MAZE_CELL::E>(static_cast<char>(lhs) | static_cast<char>(rhs));
}

inline MAZE_CELL::E 
operator& (MAZE_CELL::E lhs, MAZE_CELL::E rhs)
{
  return static_cast<MAZE_CELL::E>(static_cast<char>(lhs) & static_cast<char>(rhs));
}

void
Maze::init(uint x, uint y)
{
  grid = Grid(x,y);
}

void
Maze::binaryTree(uint seed, uint probabolityX, uint probabolityY)
{
  srand(seed);
  for(uint i = 0; i<grid.sizeX; ++i){
    for(uint o = 0; o<grid.sizeY; ++o){
      MAZE_CELL::E dir;
      if(i==grid.sizeX-1){
        if(o==grid.sizeY-1){
          dir = MAZE_CELL::NONE;
        }
        else{
          dir = MAZE_CELL::UP;
        }
      }
      else{
        if(o==grid.sizeY-1){
          dir = MAZE_CELL::RIGHT;
        }
        else{
          auto random = rand()%(probabolityX+probabolityY);
          if(random < probabolityX){
            dir = MAZE_CELL::RIGHT;
          }
          else{
            dir = MAZE_CELL::UP;
          }
        }
      }

      grid.setValueAt(i,o, dir);
      if(dir == MAZE_CELL::UP){
        grid.setValueAt(i,o+1, MAZE_CELL::DOWN);
      }
      if(dir == MAZE_CELL::RIGHT){
        grid.setValueAt(i+1,o,MAZE_CELL::LEFT);
      }
    }
  }
}

void 
Maze::sidewinder(uint seed, uint hallLength)
{
  srand(seed);
  uint prevWall;
  for(uint i = 0; i<grid.sizeX-1; ++i){
    grid.setValueAt(i,0, MAZE_CELL::RIGHT);
    grid.setValueAt(i+1,0, MAZE_CELL::LEFT);
  }
  for(uint i = 1; i<grid.sizeY-1; ++i){
    prevWall = 0;
    uint o;
    for(o = 0; o<grid.sizeX-1; ++o){
      if(rand()%(hallLength) == 0){
        auto pos = rand()%(o-prevWall+1)+prevWall;
        grid.setValueAt(pos,i, MAZE_CELL::UP);
        grid.setValueAt(pos,i+1, MAZE_CELL::DOWN);
        prevWall = o+1;
      }
      else{
        grid.setValueAt(o,i, MAZE_CELL::RIGHT);
        grid.setValueAt(o+1,i, MAZE_CELL::LEFT);
      }
    }
    if(rand()%(hallLength) == 0){
      auto pos = rand()%(o-prevWall+1)+prevWall;
      grid.setValueAt(pos,i, MAZE_CELL::UP);
      grid.setValueAt(pos,i+1, MAZE_CELL::DOWN);
    }
  }
  
}

void
move(uint& x, uint& y, MAZE_CELL::E dir){
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

MAZE_CELL::E
inverse(MAZE_CELL::E dir){
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

vector<MAZE_CELL::E>
checkMoves(uint x, uint y, uint sizeX, uint sizeY){
  vector<MAZE_CELL::E> ans;
  if(y!=sizeY-1){
    ans.push_back(MAZE_CELL::UP);
  }
  if(x!=sizeX-1){
    ans.push_back(MAZE_CELL::RIGHT);
  }
  if(y!=0){
    ans.push_back(MAZE_CELL::DOWN);
  }
  if(x!=0){
    ans.push_back(MAZE_CELL::LEFT);
  }

  return ans;
}

vector<MAZE_CELL::E>
checkMoves(uint x, uint y, uint sizeX, uint sizeY, Grid& ocupied){
  vector<MAZE_CELL::E> ans;
  if(y!=sizeY-1 && ocupied.getValueAt(x,y+1)==MAZE_CELL::NONE){
    ans.push_back(MAZE_CELL::UP);
  }
  if(x!=sizeX-1 && ocupied.getValueAt(x+1,y)==MAZE_CELL::NONE){
    ans.push_back(MAZE_CELL::RIGHT);
  }
  if(y!=0 && ocupied.getValueAt(x,y-1)==MAZE_CELL::NONE){
    ans.push_back(MAZE_CELL::DOWN);
  }
  if(x!=0 && ocupied.getValueAt(x-1,y)==MAZE_CELL::NONE){
    ans.push_back(MAZE_CELL::LEFT);
  }

  return ans;
}

void 
Maze::backtracker(uint seed)
{
  srand(seed);
  uint x = rand()%grid.sizeX;
  uint y = rand()%grid.sizeY;
  uint area = grid.sizeX*grid.sizeY;
  Grid backGrid(grid.sizeX,grid.sizeY);
  for(uint i=1; i<area; ++i){
    auto dirs = checkMoves(x,y,grid.sizeX,grid.sizeY,grid);
    auto dirsNum = dirs.size();
    while(dirsNum == 0){
      move(x, y, backGrid.getValueAt(x,y));
      dirs = checkMoves(x,y,grid.sizeX,grid.sizeY,grid);
      dirsNum = dirs.size();
    }
    auto random = rand()%dirsNum;
    auto dir = dirs[random];
    grid.setValueAt(x, y, dir);
    move(x,y,dir);
    grid.setValueAt(x,y, inverse(dir));
    backGrid.setValueAt(x, y, inverse(dir));
  }
}


void 
Maze::aldousBroder(uint seed)
{
  srand(seed);
  uint x = rand()%grid.sizeX;
  uint y = rand()%grid.sizeY;
  uint newX = x, newY = y;
  uint area = grid.sizeX*grid.sizeY;
  MAZE_CELL::E dir;
  auto dirs = checkMoves(x,y,grid.sizeX,grid.sizeY);
  dir = dirs[rand()%dirs.size()];
  grid.setValueAt(x, y, dir);
  move(newX, newY, dir);
  grid.setValueAt(newX,newY, inverse(dir));
  x = newX;
  y = newY;
  for(uint i=1; i<area-1; ++i){
    while(grid.getValueAt(newX, newY) != MAZE_CELL::NONE){
      x = newX;
      y = newY;
      dirs = checkMoves(x,y,grid.sizeX,grid.sizeY);
      dir = dirs[rand()%dirs.size()];
      move(newX, newY, dir);
    }
    grid.setValueAt(x, y, dir);
    grid.setValueAt(newX,newY, inverse(dir));

  }
}

}

