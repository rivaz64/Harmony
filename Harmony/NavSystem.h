#pragma once
#include "Prerequisites.h"

namespace Harmony{

/**
 * @brief nodes used for the path finder
*/
struct PathFindNode
{
  /**
   * @brief the id of the node of the surface
  */
  uint id;

  /**
   * @brief the distance of this node to the objective
  */
  float distanceToGoal;

  /**
   * @brief the lenght of this path up until this point
  */
  float distanceOfPath;
};

/**
 * @brief class for navigating
*/
class NavSystem
{

 public:
  
  NavSystem(Surface* surface) :
    m_surface(surface){}

  void
  addPawn(Pawn* pawn);

  /**
   * @brief find a path to go from a node to another and returns the path of nodes
   * @param startId 
   * @param goalId 
   * @param path 
   * @return 
  */
  bool
  findPath(uint startId, uint goalId, vector<uint>& path);

 private:

  /**
   * @brief the pawns using this navSystem
  */
  map<Pawn*,Figure*> m_pawns; 

  /**
   * @brief the navmesh the system is going to use
  */
  Surface* m_surface;
};

}


