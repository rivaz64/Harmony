#pragma once
#include "Prerequisites.h"

namespace Harmony{

/**
 * @brief nodes used for the path finder
*/
struct SearchNode
{
  SearchNode(uint i) : id(i) {}

  /**
   * @brief the id of the node of the Graph
  */
  uint id;

  /**
   * @brief the node that searched for this
  */
  weak_ptr<SearchNode> parent;

  map<string,float> values;
};

namespace SEARCH_STATE
{
enum E{
Searching,
Failed,
Finish
};
}

/**
 * @brief class for navigating
*/
class NavSystem
{

 public:
  
  NavSystem(weak_ptr<Graph> Graph) :
    m_graph(Graph) {}

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
  findPath(uint startId, uint goalId, Path& path);

  virtual bool
  isBetterPath(weak_ptr<SearchNode> node, weak_ptr<SearchNode> newParent) {}

  virtual void
  addDataToNode(weak_ptr<SearchNode> node, weak_ptr<SearchNode> parent) {}

  virtual void
  addToOpenList(weak_ptr<SearchNode> node) {}

  SEARCH_STATE::E
  step();

  /**
   * @brief gets a path from the id to the start
   * @param id 
   * @return 
  */
  Path 
  getPath(uint id);

  inline void 
  setStart(uint id)
  {
    startId = id;
  }

  inline void 
  setGoal(uint id)
  {
    goalId = id;
  }

  inline void 
  reset()
  {
    m_openList.clear();
    m_closedList.clear();
  }

  Path
  getPath();

  inline bool
  run()
  {
    reset();
    auto state = SEARCH_STATE::Searching;
    while(state == SEARCH_STATE::Searching){
      state = step();
    }
    return state == SEARCH_STATE::Finish;
  }

 protected:

  /**
   * @brief the pawns using this navSystem
  */
  map<Pawn*,Figure*> m_pawns; 

  /**
   * @brief the navmesh the system is going to use
  */
  weak_ptr<Graph> m_graph;

  /**
   * @brief where to start seaching
  */
  uint startId;

  /**
   * @brief where to end the search
  */
  uint goalId;

  /**
   * @brief the nodes that are ready for search
  */
  list<weak_ptr<SearchNode>> m_openList;

  /**
   * @brief the nodes that have been searched
  */
  map<uint,shared_ptr<SearchNode>> m_closedList;
};

}


