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
Maze::generate(uint x, uint y, uint seed)
{
  srand(seed);
  sizeX = x;
  sizeY = y;
  grid.resize((x*y)/2);

  for(uint i = 0; i<x; ++i){
    for(uint o = 0; o<y; ++o){
      MAZE_CELL::E dir;
      if(i==x-1){
        if(o==y-1){
          dir = MAZE_CELL::NONE;
        }
        else{
          dir = MAZE_CELL::UP;
        }
      }
      else{
        if(o==y-1){
          dir = MAZE_CELL::RIGHT;
        }
        else{
          dir = static_cast<MAZE_CELL::E>(rand()%2+1);
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

}
