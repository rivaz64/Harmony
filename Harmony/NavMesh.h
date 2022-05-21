#pragma once
#include "Prerequisites.h"
#include "Triangle.h"

namespace Harmony{

struct NavMeshNode
{
  /**
   * @brief the triangle representing this node
  */
  Triangle tri;

  /**
   * @brief the nodes that can be reached from this node
  */
  map<uint,uint> adjacents;
};

struct PathFindNode
{
  uint id;

  /**
   * @brief the distance of this node to the objective
  */
  float distance;
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

  list<Vector2f>
  findPath(Vector2f start, Vector2f end);

  vector<uint>
  findPath(uint start, uint end);

 public:

  /**
   * @brief the tris of the navMesh
  */
  vector<NavMeshNode> tris;


  //map<Pawn,uint> 
  
};

}


