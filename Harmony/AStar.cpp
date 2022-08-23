#include "AStar.h"
#include "Graph.h"

namespace Harmony
{

bool
AStar::isBetterPath(weak_ptr<SearchNode> wNode, weak_ptr<SearchNode> wParent)
{
  auto node = wNode.lock();
  auto parent = wParent.lock();
  auto graph = m_graph.lock();
  return node->values["f"] > parent->values["cost"] + graph->getCost(node->id,parent->id) + graph->getDistance(node->id,goalId);
}

void AStar::addDataToNode(weak_ptr<SearchNode> wNode, weak_ptr<SearchNode> wParent)
{
  auto node = wNode.lock();
  auto parent = wParent.lock();
  auto graph = m_graph.lock();
  node->values["cost"] = parent->values["cost"] + graph->getCost(node->id,parent->id);
  node->values["f"] = node->values["cost"] + graph->getDistance(node->id,goalId);
}

void AStar::addToOpenList(weak_ptr<SearchNode> wNode)
{
  auto node = wNode.lock();
  for(auto it = m_openList.begin(); it != m_openList.end(); ++it){
    if(node->values["f"] < it->lock()->values["f"]){
      m_openList.insert(it,node);
      return;
    }
  }
  m_openList.push_back(node);
}

}

