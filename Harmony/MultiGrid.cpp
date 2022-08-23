#include "MultiGrid.h"
#include "NavLink.h"
#include "HexGrid.h"

namespace Harmony
{

void
MultiGrid::setValueAt(uint x, uint y, uint z, uint value)
{
  m_grids[z]->setValueAt(x,y,value);
}

void 
MultiGrid::unsetValueAt(uint x, uint y, uint z, uint value)
{
  m_grids[z]->unsetValueAt(x,y,value);
}

uint 
MultiGrid::getValueAt(uint x, uint y, uint z)
{
  return m_grids[z]->getValueAt(x,y);
}

Grid* 
MultiGrid::getGrid(uint z)
{
  return m_grids[z];
}

map<uint, uint>
MultiGrid::getAdjacentCells(const uint id)
{
  uint localId = id%(m_sizeX*m_sizeY);
  uint x = localId%m_sizeX;
  uint y = localId/m_sizeX;
  uint z = id/(m_sizeX*m_sizeY);
  auto adjacents = Grid::getAdjacentCells(localId);
  auto& links = m_links[z];
  if(links.find(id) != links.end()){
    for(auto& link : links[id]){
      adjacents.insert({EXEL_CELL::LINK,link->getOther(id)});
    }
  }
  return adjacents;
}

float 
MultiGrid::getDistance(uint id)
{
  uint z = id/m_grids.size();
  auto& distances = m_distances[z];
  pair<float,NavLink*> minorDistance = distances[0];
  int numOfDist = distances.size();
  for(int i=1; i<numOfDist; ++i){
    if(minorDistance.first > distances[i].first){
      minorDistance = distances[i];
    }
  }
  ;
  return minorDistance.first+getCost(id,minorDistance.second->getNode1()%(m_sizeX*m_sizeY));
}

void 
MultiGrid::calculateDistances()
{
  uint goalFloor = m_goal/(m_sizeX*m_sizeY);
  uint numOfGrids = m_grids.size();
  auto& thisFloor = m_links[goalFloor];
  for(auto& node : thisFloor){
    float dist = m_grids[goalFloor]->getDistance(node.first/(m_sizeX*m_sizeY));
    for(auto& link : node.second){
      auto floor1 = link->getNode1()/(m_sizeX*m_sizeY);
      auto floor2 = link->getNode2()/(m_sizeX*m_sizeY);
      auto floor = (floor1==goalFloor)*floor2+(floor2==goalFloor)*floor1;
      m_distances[floor].push_back(pair<float,NavLink*>(dist,link));
    }
  }

  for(uint i = goalFloor+1; goalFloor<numOfGrids-1; ++i){
    auto& otherFloor = m_links[i];
    for(auto& node : thisFloor){
      float dist = getDistance(node.first/(m_sizeX*m_sizeY));
      for(auto& link : node.second){
        auto floor1 = link->getNode1()/(m_sizeX*m_sizeY);
        auto floor2 = link->getNode2()/(m_sizeX*m_sizeY);
        auto floor = (floor1==i)*floor2+(floor2==i)*floor1;
        m_distances[floor].push_back(pair<float,NavLink*>(dist,link));
      }
    }
  }

  for(uint i = goalFloor-1; i>=0; --i){
    auto& otherFloor = m_links[i];
    for(auto& node : thisFloor){
      float dist = getDistance(node.first/(m_sizeX*m_sizeY));
      for(auto& link : node.second){
        auto floor1 = link->getNode1()/(m_sizeX*m_sizeY);
        auto floor2 = link->getNode2()/(m_sizeX*m_sizeY);
        auto floor = (floor1==i)*floor2+(floor2==i)*floor1;
        m_distances[floor].push_back(pair<float,NavLink*>(dist,link));
      }
    }
  }
}

void
MultiGrid::addLink(NavLink* link)
{
  auto node1 = link->getNode1();
  auto node2 = link->getNode2();

  auto floor1 = node1/(m_sizeX*m_sizeY);
  auto floor2 = node2/(m_sizeX*m_sizeY);

  auto id1 = node1%(m_sizeX*m_sizeY);
  auto id2 = node2%(m_sizeX*m_sizeY);

  m_links[floor1][id1].push_back(link);
  m_links[floor2][id2].push_back(link);
}

void 
MultiGrid::setGoal(uint goal)
{
  m_goal = goal;
  uint goalFloor = m_goal/(m_sizeX*m_sizeY);
  m_grids[goalFloor]->setGoal(goal);
}

}

