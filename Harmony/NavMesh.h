#pragma once
#include "Prerequisites.h"
#include "Triangle.h"
#include "Surface.h"

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
  float distanceToGoal;

  /**
   * @brief the distance of this node to the objective
  */
  float distanceOfPath;
};

class NavMesh :
  public Surface
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

  bool
  getCellAt(const Dimencion& point,uint& nodeId) override;

  const Figure*
  getFigure(const uint id) override;

  //bool
  //nodeOfPoint(const Dimencion& point,uint& node);

  /**
   * @brief adds a pawn that is going to be using the navmesh
   * @param pawn 
  */
  void
  addPawn(Pawn* pawn);

  /**
   * @brief finds a path in points 
   * @param start 
   * @param end 
   * @return the path in points
  */
  list<Dimencion>
  findPath(Dimencion start, Dimencion end);

  /**
   * @brief finds a path form a node to another
   * @param start 
   * @param end 
   * @return a path of nodes
  */
  vector<uint>
  findPath(uint start, uint end);

  /**
   * @brief a linetrace using navmesh
   * @param originalPos 
   * @param destiny 
   * @param actualNode 
   * @param obstacle 
   * @param normal 
   * @return 
  */
  uint
  goToNewNode(const Dimencion& originalPos,
              const Dimencion& destiny, 
              uint actualNodeId, 
              Dimencion& obstacle, 
              Dimencion& normal);

  /**
   * @brief updates the pawns and in which node they are
   * @param deltaTime 
  */
  void
  update(float deltaTime);

 public:

  /**
   * @brief the tris of the navMesh
  */
  vector<NavMeshNode> tris;


  map<Pawn*,uint> pawns; 
  
};

}


