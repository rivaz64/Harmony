#pragma once
#include "Detector.h"

namespace Harmony{

/**
 * @brief sees the things in the world
*/
class Vision :
  public Detector
{
 public:
  
  void
  update(float delta) override;
};

}


