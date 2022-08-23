#include "NavSystem.h"
#include "Pawn.h"
#include "Grid.h"
#include "Figure.h"
#include "Path.h"

namespace Harmony{

void 
NavSystem::addPawn(Pawn* pawn)
{
  
}

//void 
//insertToFind(PathFindNode newNode, list<PathFindNode>& forsearch){
//  for(auto node = forsearch.begin(); node != forsearch.end(); ++node){
//    if(node->distanceToGoal+node->distanceOfPath > newNode.distanceToGoal+newNode.distanceOfPath){
//      forsearch.insert(node,newNode);
//      return;
//    }
//  }
//  forsearch.push_back(newNode);
//}

bool 
NavSystem::findPath(uint startId, uint goalId, Path& path)
{
  setStart(startId);
  setGoal(goalId);
  bool result = run();
  if(result){
    path = getPath();
    return true;
  }
  return false;
}

SEARCH_STATE::E
NavSystem::step()
{
  if(m_openList.size() == 0 || m_graph.expired()){
    return SEARCH_STATE::Failed;
  }

  auto graph = m_graph.lock();
  auto node = m_openList.begin()->lock();
  auto adjacents = graph->getAdjacentNodes(node->id);
  weak_ptr<SearchNode> adjacentNode;

  if(graph->isAt(node->id,goalId)){
    return SEARCH_STATE::Finish;
  }

  for(auto& adjacent : adjacents){
    if(m_closedList.find(adjacent.second) != m_closedList.end()){
      adjacentNode = m_closedList[adjacent.second];
    }
    else{
      auto newNode = make_shared<SearchNode>(adjacent.second);
      m_closedList.insert({adjacent.second,newNode});
      adjacentNode = newNode;
      addDataToNode(adjacentNode,node);
      addToOpenList(node);
      continue;
    }
    if(isBetterPath(adjacentNode,node)){
      addDataToNode(adjacentNode,node);
      for(auto it = m_openList.begin(); it != m_openList.end(); ++it){
        if((it->lock()->id == adjacent.second)){
          m_openList.erase(it);
          break;
        }
      }
      addToOpenList(node);
    }
  }

  
  return SEARCH_STATE::Searching;
}

Path 
NavSystem::getPath(uint id)
{
  Path path;
  if(m_closedList.find(id) == m_closedList.end()) return path;
  auto node = m_closedList[id];
  path.m_nodes.push_back(node);
  while(node){
    node = node->parent.lock();
    path.m_nodes.push_back(node);
  }
  return path;
}

Path 
NavSystem::getPath()
{
  return getPath(goalId);
}

}
