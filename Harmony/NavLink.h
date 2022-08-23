#pragma once
#include "Prerequisites.h"

namespace Harmony{

/**
 * @brief to conect to nodes in diferent grids
*/
class NavLink
{
 public:

  NavLink() = default;

  NavLink(uint nodeId1, uint nodeId2) :
   m_nodeId1(nodeId1), m_nodeId2(nodeId2) {}

  inline uint 
  getOther(uint thisOne)
  {
    return (thisOne==m_nodeId1)*m_nodeId2+(thisOne==m_nodeId2)*m_nodeId1;
  }
  
  inline uint 
  getNode1()
  {
    return m_nodeId1;
  }

  inline uint 
  getNode2()
  {
    return m_nodeId2;
  }

 protected:

  uint m_nodeId1;

  uint m_nodeId2;
};

}



