#pragma once

#include "Prerequisites.h"

namespace Harmony
{

class Path
{
 
 protected:
  
  vector<shared_ptr<SearchNode>> m_nodes;

  friend class NavSystem; 
};

}


