#pragma once

#include "Prerequisites.h"
#include "Vector2f.h"

namespace Harmony{
  
static const float PI = 3.1415926536;

/**
 * @brief gets the angle of a vector
 * @param v 
 * @return 
*/
inline float
VectorToAngle(const Vector2f& v){
  return atan2f(v.y,v.x);
}

/**
 * @brief mantains the value of the angle between pi and -pi
 * @param v 
 * @return 
*/
inline float
angleInRange(float v){
  return fmodf(v,PI);
}

inline float
angleBetween(float v1, float v2){
  return angleInRange(v2-v1);
}

}