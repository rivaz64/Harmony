#pragma once
#include "Prerequisites.h"
namespace Harmony{

struct SurfaceNode{
  uint id;
  Figure* figure;
};

/**
 * @brief a 2D surface divided in sections
*/
class Surface
{
 public:
  
  virtual SurfaceNode
  getCellAt(Dimencion point){return {0,nullptr};}

 protected:
};

}


