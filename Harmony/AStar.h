#pragma once
#include "NavSystem.h"

namespace Harmony
{

class AStar :
  public NavSystem
{
 public:

  AStar() = default;

  AStar(weak_ptr<Graph> Graph) :
    NavSystem(Graph) {}

  bool
  isBetterPath(weak_ptr<SearchNode> node, weak_ptr<SearchNode> newParent);

  virtual void
  addDataToNode(weak_ptr<SearchNode> node, weak_ptr<SearchNode> parent);

  virtual void
  addToOpenList(weak_ptr<SearchNode> node);

};

}


