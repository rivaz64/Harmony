#pragma once
#include "Prerequisites.h"
#include "ConvexFigure.h"
#include "Graph.h"

namespace Harmony{

struct NavMeshNode
{
  /**
   * @brief the triangle representing this node
  */
  ConvexFigure fig;

  /**
   * @brief the nodes that can be reached from this node, key is the direction, value is the other node
  */
  map<uint,uint> adjacents;
};

class NavMesh :
  public Graph
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

  map<uint,uint>
  getAdjacentNodes(const uint id) override;

  //bool
  //nodeOfPoint(const Dimencion& point,uint& node);

  /**
   * @brief adds a pawn that is going to be using the navmesh
   * @param pawn 
  */
  //void
  //addPawn(Pawn* pawn);

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
  vector<NavMeshNode> m_nodes;


  map<Pawn*,uint> pawns; 
  
};

}


