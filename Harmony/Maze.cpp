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
  sizeX = x;
  sizeY = y;
  grid.clear();
  grid.resize((x*y)/2);
}

void
Maze::binaryTree(uint seed, uint probabolityX, uint probabolityY)
{
  srand(seed);
  for(uint i = 0; i<sizeX; ++i){
    for(uint o = 0; o<sizeY; ++o){
      MAZE_CELL::E dir;
      if(i==sizeX-1){
        if(o==sizeY-1){
          dir = MAZE_CELL::NONE;
        }
        else{
          dir = MAZE_CELL::UP;
        }
      }
      else{
        if(o==sizeY-1){
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

      setValueAt(i,o, dir);
      if(dir == MAZE_CELL::UP){
        setValueAt(i,o+1, MAZE_CELL::DOWN);
      }
      if(dir == MAZE_CELL::RIGHT){
        setValueAt(i+1,o,MAZE_CELL::LEFT);
      }
    }
  }
}

void 
Maze::sidewinder(uint seed, uint hallLength)
{
  srand(seed);
  uint prevWall;
  for(uint i = 0; i<sizeX-1; ++i){
    setValueAt(i,0, MAZE_CELL::RIGHT);
    setValueAt(i+1,0, MAZE_CELL::LEFT);
  }
  for(uint i = 1; i<sizeY-1; ++i){
    prevWall = 0;
    uint o;
    for(o = 0; o<sizeX-1; ++o){
      if(rand()%(hallLength) == 0){
        auto pos = rand()%(o-prevWall+1)+prevWall;
        setValueAt(pos,i, MAZE_CELL::UP);
        setValueAt(pos,i+1, MAZE_CELL::DOWN);
        prevWall = o+1;
      }
      else{
        setValueAt(o,i, MAZE_CELL::RIGHT);
        setValueAt(o+1,i, MAZE_CELL::LEFT);
      }
    }
    if(rand()%(hallLength) == 0){
      auto pos = rand()%(o-prevWall+1)+prevWall;
      setValueAt(pos,i, MAZE_CELL::UP);
      setValueAt(pos,i+1, MAZE_CELL::DOWN);
    }
  }
  
}

}
