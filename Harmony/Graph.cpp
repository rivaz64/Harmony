#include "Graph.h"
#include "Figure.h"

namespace Harmony
{

float
Graph::getDistance(uint id,uint otherId)
{
  return size(getFigure(id)->getCenter()-getFigure(otherId)->getCenter());
}

float
Graph::getCost(uint id, uint idParent)
{
  return size(getFigure(id)->getCenter()-getFigure(id)->getCenter());
}

bool 
Graph::isAt(uint id, uint goalId)
{
  return id == goalId;
}

}

