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

//void
//Maze::init(uint x, uint y)
//{
//  grid = Grid(x,y);
//}

void
Maze::init(Grid* grid)
{
  m_grid = grid;
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
  srand(seed);
  uint prevWall;
  for(uint i = 0; i<m_grid->sizeX-1; ++i){
    m_grid->setValueAt(i,0, MAZE_CELL::RIGHT);
    m_grid->setValueAt(i+1,0, MAZE_CELL::LEFT);
  }
  for(uint i = 1; i<m_grid->sizeY-1; ++i){
    prevWall = 0;
    uint o;
    for(o = 0; o<m_grid->sizeX-1; ++o){
      if(rand()%(hallLength) == 0){
        auto pos = rand()%(o-prevWall+1)+prevWall;
        m_grid->setValueAt(pos,i, MAZE_CELL::UP);
        m_grid->setValueAt(pos,i+1, MAZE_CELL::DOWN);
        prevWall = o+1;
      }
      else{
        m_grid->setValueAt(o,i, MAZE_CELL::RIGHT);
        m_grid->setValueAt(o+1,i, MAZE_CELL::LEFT);
      }
    }
    if(rand()%(hallLength) == 0){
      auto pos = rand()%(o-prevWall+1)+prevWall;
      m_grid->setValueAt(pos,i, MAZE_CELL::UP);
      m_grid->setValueAt(pos,i+1, MAZE_CELL::DOWN);
    }
  }
  
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
  //srand(seed);
  //uint x = rand()%m_grid->sizeX;
  //uint y = rand()%m_grid->sizeY;
  //uint area = m_grid->sizeX*m_grid->sizeY;
  //Grid* backGrid = new Grid(m_grid->sizeX,m_grid->sizeY);
  //for(uint i=1; i<area; ++i){
  //  auto dirs = m_grid->checkMarkedMoves(x,y);
  //  auto dirsNum = dirs.size();
  //  while(dirsNum == 0){
  //    m_grid->move(x, y, backgrid->getValueAt(x,y));
  //    dirs = checkMoves(x,y,m_grid->sizeX,m_grid->sizeY,grid);
  //    dirsNum = dirs.size();
  //  }
  //  auto random = rand()%dirsNum;
  //  auto dir = dirs[random];
  //  m_grid->setValueAt(x, y, dir);
  //  m_grid->move(x,y,dir);
  //  m_grid->setValueAt(x,y, inverse(dir));
  //  backm_grid->setValueAt(x, y, inverse(dir));
  //}
}


void 
Maze::aldousBroder(uint seed)
{
  srand(seed);
  uint x = rand()%m_grid->sizeX;
  uint y = rand()%m_grid->sizeY;
  uint newX = x, newY = y;
  uint area = m_grid->sizeX*m_grid->sizeY;
  uint dir;
  auto dirs = m_grid->checkMoves(x,y);
  dir = dirs[rand()%dirs.size()];
  m_grid->setValueAt(newX, newY, dir);
  m_grid->move(newX, newY, dir);
  m_grid->setValueAt(newX,newY, m_grid->inverse(dir));
  x = newX;
  y = newY;
  for(uint i=1; i<area-1; ++i){
    while(m_grid->getValueAt(newX, newY) != MAZE_CELL::NONE){
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
  uint x = rand()%m_grid->sizeX;
  uint y = rand()%m_grid->sizeY;
  uint newX = 0, newY = 0;
  auto dirs = m_grid->checkMoves(x,y);
  auto dir = dirs[rand()%dirs.size()];
  m_grid->setValueAt(x, y, dir);
  m_grid->move(x, y, dir);
  m_grid->setValueAt(x,y, m_grid->inverse(dir));
  uint cellsFilled = 2;
  uint area = m_grid->sizeX*m_grid->sizeY;
  while(cellsFilled<area){

    list<WilsonNode> actualWalk;

    while(m_grid->getValueAt(x,y) != MAZE_CELL::NONE){
      x = rand()%m_grid->sizeX;
      y = rand()%m_grid->sizeY;
    }

    newX = x;
    newY = y;
    dirs = m_grid->checkMoves(x,y);
    dir = dirs[rand()%dirs.size()];
    actualWalk.push_back({newX,newY,dir});
    m_grid->move(newX, newY, dir);
    while(m_grid->getValueAt(newX,newY) == MAZE_CELL::NONE){

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
  if(y!=sizeY-1){
    ans.push_back(EXEL_CELL::UP);
  }
  if(x!=sizeX-1){
    ans.push_back(EXEL_CELL::DOWN_RIGHT);
  }
  if(x!=sizeX-1 && y!=sizeY-1){
    ans.push_back(EXEL_CELL::UP_RIGHT);
  }
  if(y!=0){
    ans.push_back(EXEL_CELL::DOWN);
  }
  if(x!=0){
    ans.push_back(EXEL_CELL::UP_LEFT);
  }
  if(x!=0 && y!=0){
    ans.push_back(EXEL_CELL::DOWN_LEFT);
  }
  return ans;
}

vector<uint> 
ExelGrid::checkMarkedMoves(const uint x, const uint y)
{
  vector<uint> ans;
  if(y!=sizeY-1 && getValueAt(x,y+1)==EXEL_CELL::NONE){
    ans.push_back(EXEL_CELL::UP);
  }
  if(x!=sizeX-1 && getValueAt(x+1,y)==EXEL_CELL::NONE){
    ans.push_back(EXEL_CELL::DOWN_RIGHT);
  }
  if(x!=sizeX-1 && y!=sizeY-1 && getValueAt(x+1,y+1)==EXEL_CELL::NONE){
    ans.push_back(EXEL_CELL::UP_RIGHT);
  }
  if(y!=0 && getValueAt(x,y-1)==EXEL_CELL::NONE){
    ans.push_back(EXEL_CELL::DOWN);
  }
  if(x!=0 && getValueAt(x-1,y)==EXEL_CELL::NONE){
    ans.push_back(EXEL_CELL::UP_LEFT);
  }
  if(x!=0 && y!=0 && getValueAt(x-1,y-1)==EXEL_CELL::NONE){
    ans.push_back(EXEL_CELL::DOWN_LEFT);
  }
  return ans;
}


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

vector<uint> 
QuadGrid::checkMarkedMoves(const uint x, const uint y)
{
  vector<uint> ans;
  if(y!=sizeY-1 && getValueAt(x,y+1)==MAZE_CELL::NONE){
    ans.push_back(MAZE_CELL::UP);
  }
  if(x!=sizeX-1 && getValueAt(x+1,y)==MAZE_CELL::NONE){
    ans.push_back(MAZE_CELL::RIGHT);
  }
  if(y!=0 && getValueAt(x,y-1)==MAZE_CELL::NONE){
    ans.push_back(MAZE_CELL::DOWN);
  }
  if(x!=0 && getValueAt(x-1,y)==MAZE_CELL::NONE){
    ans.push_back(MAZE_CELL::LEFT);
  }

  return ans;
}

//void
//Grid::mark(uint& x, uint& y, const uint dir)
//{
//  setValueAt(x, y, dir);
//  move(newX, newY, dir);
//  setValueAt(newX,newY, inverse(dir));
//}

}

