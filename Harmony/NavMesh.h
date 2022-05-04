#pragma once
#include "Prerequisites.h"
#include "Triangle.h"

namespace Harmony{

class NavMesh
{
 public:

  
  void
  generateFromPoints(const vector<Vector2f>& points);

 public:

  vector<Triangle> tris;
};

}


