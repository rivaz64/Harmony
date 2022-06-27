#include "Maze.h"
#include "Grid.h"


namespace Harmony{
void
Maze::init(Grid* grid, uint area)
{
  m_grid = grid;
  m_area = area;
}

void
Maze::binaryTree(uint seed)
{
  //srand(seed);
  //for(uint i = 0; i<m_grid->sizeX; ++i){
  //  for(uint o = 0; o<m_grid->sizeY; ++o){
  //    MAZE_CELL::E dir;
  //    if(i==m_grid->sizeX-1){
  //      if(o==m_grid->sizeY-1){
  //        dir = MAZE_CELL::NONE;
  //      }
  //      else{
  //        dir = MAZE_CELL::UP;
  //      }
  //    }
  //    else{
  //      if(o==m_grid->sizeY-1){
  //        dir = MAZE_CELL::RIGHT;
  //      }
  //      else{
  //        auto random = rand()%2;
  //        if(random < probabolityX){
  //          dir = MAZE_CELL::RIGHT;
  //        }
  //        else{
  //          dir = MAZE_CELL::UP;
  //        }
  //      }
  //    }
  //
  //    m_grid->setValueAt(i,o, dir);
  //    if(dir == MAZE_CELL::UP){
  //      m_grid->setValueAt(i,o+1, MAZE_CELL::DOWN);
  //    }
  //    if(dir == MAZE_CELL::RIGHT){
  //      m_grid->setValueAt(i+1,o,MAZE_CELL::LEFT);
  //    }
  //  }
  //}
}

void 
Maze::sidewinder(uint seed, uint hallLength)
{
  //srand(seed);
  //uint prevWall;
  //for(uint i = 0; i<m_grid->sizeX-1; ++i){
  //  m_grid->setValueAt(i,0, MAZE_CELL::RIGHT);
  //  m_grid->setValueAt(i+1,0, MAZE_CELL::LEFT);
  //}
  //for(uint i = 1; i<m_grid->sizeY-1; ++i){
  //  prevWall = 0;
  //  uint o;
  //  for(o = 0; o<m_grid->sizeX-1; ++o){
  //    if(rand()%(hallLength) == 0){
  //      auto pos = rand()%(o-prevWall+1)+prevWall;
  //      m_grid->setValueAt(pos,i, MAZE_CELL::UP);
  //      m_grid->setValueAt(pos,i+1, MAZE_CELL::DOWN);
  //      prevWall = o+1;
  //    }
  //    else{
  //      m_grid->setValueAt(o,i, MAZE_CELL::RIGHT);
  //      m_grid->setValueAt(o+1,i, MAZE_CELL::LEFT);
  //    }
  //  }
  //  if(rand()%(hallLength) == 0){
  //    auto pos = rand()%(o-prevWall+1)+prevWall;
  //    m_grid->setValueAt(pos,i, MAZE_CELL::UP);
  //    m_grid->setValueAt(pos,i+1, MAZE_CELL::DOWN);
  //  }
  //}
  
}

//void
//move(uint& x, uint& y, MAZE_CELL::E dir){
//  switch (dir)
//  {
//  case MAZE_CELL::UP:
//    ++y;
//    break;
//
//  case MAZE_CELL::RIGHT:
//    ++x;
//    break;
//
//  case MAZE_CELL::DOWN:
//    --y;
//    break;
//
//  case MAZE_CELL::LEFT:
//    --x;
//    break;
//  }
//}

//MAZE_CELL::E
//inverse(MAZE_CELL::E dir){
//  switch (dir)
//  {
//  case MAZE_CELL::UP:
//    return MAZE_CELL::DOWN;
//    break;
//
//  case MAZE_CELL::RIGHT:
//    return MAZE_CELL::LEFT;
//    break;
//
//  case MAZE_CELL::DOWN:
//    return MAZE_CELL::UP;
//    break;
//
//  case MAZE_CELL::LEFT:
//    return MAZE_CELL::RIGHT;
//    break;
//  }
//}

//vector<MAZE_CELL::E>
//checkMoves(uint x, uint y, uint sizeX, uint sizeY){
//  vector<MAZE_CELL::E> ans;
//  if(y!=sizeY-1){
//    ans.push_back(MAZE_CELL::UP);
//  }
//  if(x!=sizeX-1){
//    ans.push_back(MAZE_CELL::RIGHT);
//  }
//  if(y!=0){
//    ans.push_back(MAZE_CELL::DOWN);
//  }
//  if(x!=0){
//    ans.push_back(MAZE_CELL::LEFT);
//  }
//
//  return ans;
//}
//
//vector<MAZE_CELL::E>
//checkMoves(uint x, uint y, uint sizeX, uint sizeY, Grid& ocupied){
//  vector<MAZE_CELL::E> ans;
//  if(y!=sizeY-1 && ocupied.getValueAt(x,y+1)==MAZE_CELL::NONE){
//    ans.push_back(MAZE_CELL::UP);
//  }
//  if(x!=sizeX-1 && ocupied.getValueAt(x+1,y)==MAZE_CELL::NONE){
//    ans.push_back(MAZE_CELL::RIGHT);
//  }
//  if(y!=0 && ocupied.getValueAt(x,y-1)==MAZE_CELL::NONE){
//    ans.push_back(MAZE_CELL::DOWN);
//  }
//  if(x!=0 && ocupied.getValueAt(x-1,y)==MAZE_CELL::NONE){
//    ans.push_back(MAZE_CELL::LEFT);
//  }
//
//  return ans;
//}

void 
Maze::backtracker(uint seed)
{
  srand(seed);
  uint x = rand()%m_grid->getSizeX();
  uint y = rand()%m_grid->getSizeY();
  list<uint> backTrack;
  for(uint i=1; i<m_area; ++i){
    auto dirs = m_grid->checkMarkedMoves(x,y);
    auto dirsNum = dirs.size();
    if(dirsNum == 0){
      deadPoints.push_back({x,y});
    }
    while(dirsNum == 0){
      m_grid->move(x, y, backTrack.back());
      backTrack.pop_back();
      dirs = m_grid->checkMarkedMoves(x,y);
      dirsNum = dirs.size();
    }
    auto random = rand()%dirsNum;
    auto dir = dirs[random];
    m_grid->setValueAt(x, y, dir);
    m_grid->move(x,y,dir);
    m_grid->setValueAt(x,y, m_grid->inverse(dir));
    backTrack.push_back(m_grid->inverse(dir));
  }
}

void 
Maze::aldousBroder(uint seed)
{
  srand(seed);
  uint x;
  uint y;
  m_grid->getRandomCoords(x,y);
  uint newX = x, newY = y;
  //uint area = m_grid->sizeX*m_grid->sizeY;
  uint dir;
  auto dirs = m_grid->checkMoves(x,y);
  dir = dirs[rand()%dirs.size()];
  m_grid->setValueAt(newX, newY, dir);
  m_grid->move(newX, newY, dir);
  m_grid->setValueAt(newX,newY, m_grid->inverse(dir));
  x = newX;
  y = newY;
  for(uint i=1; i<m_area-1; ++i){
    while(m_grid->getValueAt(newX, newY) != 0){
      x = newX;
      y = newY;
      dirs = m_grid->checkMoves(x,y);
      dir = dirs[rand()%dirs.size()];
      m_grid->move(newX, newY, dir);
    }
    m_grid->setValueAt(x, y, dir);
    m_grid->setValueAt(newX,newY, m_grid->inverse(dir));
  }
}


struct WilsonNode{

  WilsonNode() = default;

  WilsonNode(uint _x, uint _y, uint _dir):
    x(_x), y(_y), dir(_dir){}

  const bool& 
  operator==(const WilsonNode& other) const
  {
    return x == other.x && y == other.y;
  }

  uint x;
  uint y;
  uint dir;
};

void 
Maze::wilson(uint seed)
{
  srand(seed);
  uint x = rand()%m_grid->getSizeX();
  uint y = rand()%m_grid->getSizeY();
  uint newX = 0, newY = 0;
  auto dirs = m_grid->checkMoves(x,y);
  auto dir = dirs[rand()%dirs.size()];
  m_grid->setValueAt(x, y, dir);
  m_grid->move(x, y, dir);
  m_grid->setValueAt(x,y, m_grid->inverse(dir));
  uint cellsFilled = 2;
  uint area = m_grid->getSizeX()*m_grid->getSizeY();
  while(cellsFilled<area){

    list<WilsonNode> actualWalk;

    while(m_grid->getValueAt(x,y) != 0){
      x = rand()%m_grid->getSizeX();
      y = rand()%m_grid->getSizeY();
    }

    newX = x;
    newY = y;
    dirs = m_grid->checkMoves(x,y);
    dir = dirs[rand()%dirs.size()];
    actualWalk.push_back({newX,newY,dir});
    m_grid->move(newX, newY, dir);
    while(m_grid->getValueAt(newX,newY) == 0){

      dirs = m_grid->checkMoves(newX,newY);
      dir = dirs[rand()%dirs.size()];
      actualWalk.push_back({newX,newY,dir});
      m_grid->move(newX, newY, dir);
      auto finded = find(actualWalk.begin(),actualWalk.end(),WilsonNode(newX,newY,dir));
      if(finded != actualWalk.end()){
        newX = finded->x;
        newY = finded->y;
        actualWalk.assign(actualWalk.begin(),finded);
        continue;
      }
    }

    for(auto& node : actualWalk){
      m_grid->setValueAt(x,y,node.dir);
      m_grid->move(x,y,node.dir);
      m_grid->setValueAt(x,y,m_grid->inverse(node.dir));
      ++cellsFilled;
    }
  }
}

void
Maze::clearDeadPoints(float p)
{
  uint totalPoints = static_cast<float>(deadPoints.size())*p;
  for(uint i = 0; i< totalPoints; ++i){
    uint toQuit = rand()%deadPoints.size();
    auto at = deadPoints.begin();
    advance(at,toQuit);
    auto dirs = m_grid->checkNewMoves(at->x,at->y);
    auto dir = dirs[rand()%dirs.size()];
    m_grid->setValueAt(at->x,at->y,dir);
    m_grid->move(at->x,at->y,dir);
    m_grid->setValueAt(at->x,at->y,m_grid->inverse(dir));
    deadPoints.erase(at);
  }
}

}

