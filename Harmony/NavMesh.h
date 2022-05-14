#pragma once
#include "Prerequisites.h"
#include "Triangle.h"

namespace Harmony{

struct NavMeshNode{
  /**
   * @brief the triangle representing this node
  */
  Triangle tri;

  /**
   * @brief the nodes that can be reached from this node
  */
  vector<uint> adjacents;
};

class NavMesh
{
 public:

  /**
   * @brief generates the navmesh 
   * @param minPoint the minpoint of the box for generating the navmesh
   * @param maxPoint the maxpoint of the box for generating the navmesh
   * @param obstacles the places the pawn can not be
  */
  void
  generate(const Dimencion& minPoint, 
           const Dimencion& maxPoint, 
           const vector<vector<Dimencion>>& obstacles);

 public:

  /**
   * @brief the tris of the navMesh
  */
  vector<NavMeshNode> tris;

  //map<Pawn,uint> 
  
};

}


