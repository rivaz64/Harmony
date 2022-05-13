#pragma once
#include "Prerequisites.h"
#include "Triangle.h"

namespace Harmony{

class NavMesh
{
 public:

  
  void
  generateFromPoints(const Dimencion& minPoint, 
                     const Dimencion& maxPoint, 
                     const vector<vector<Dimencion>>& obstacles);

 public:

  vector<Triangle> tris;
};

}


