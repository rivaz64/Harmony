#include "NavSystem.h"
#include "Pawn.h"
#include "Grid.h"
#include "Figure.h"
#define CENTER(n) m_surface->getFigure(n)->getCenter()
#define DISTANCE(n) (CENTER(n)-centerStart).magnitud()
#define DISTANCE2(n,m) (CENTER(n)-CENTER(m)).magnitud()

namespace Harmony{

void 
NavSystem::addPawn(Pawn* pawn)
{
  
}

void 
insertToFind(PathFindNode newNode, list<PathFindNode>& forsearch){
  for(auto node = forsearch.begin(); node != forsearch.end(); ++node){
    if(node->distanceToGoal+node->distanceOfPath > newNode.distanceToGoal+newNode.distanceOfPath){
      forsearch.insert(node,newNode);
      return;
    }
  }
  forsearch.push_back(newNode);
}

bool 
NavSystem::findPath(uint startId, uint goalId, vector<uint>& path)
{
  list<PathFindNode> forsearch;
  //node, parent
  map<uint,uint> paths;
  auto centerStart = CENTER(startId);//CENTER(start);
  insertToFind({goalId,DISTANCE(goalId),0},forsearch);
  paths.insert({goalId,-1});
  while(forsearch.size()>0){
    auto actualAtNode = *forsearch.begin();
    auto searchAtID = actualAtNode.id;
    if(searchAtID == startId){
      //vector<uint> ans;
      uint actualNode = startId;
      while(actualNode != goalId){
        path.push_back(actualNode);
        actualNode = paths[actualNode];
      }
      path.push_back(actualNode);
      //return ans;
      return true;
    }
    auto adjacents = m_surface->getAdjacentCells(searchAtID);//tris[searchAtID];
    forsearch.pop_front();
    for(auto& node : adjacents){
      if(paths.find(node.second)==paths.end()){
        insertToFind({node.second,DISTANCE(node.second),DISTANCE2(node.second,searchAtID)+actualAtNode.distanceOfPath},forsearch);//forsearch.push_back(node.second);
        paths.insert({node.second,searchAtID});
      }
    }
  }
  return false;
}

}
