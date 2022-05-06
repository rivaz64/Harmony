#pragma once

#include "Prerequisites.h"
#include "Vector2f.h"

namespace Harmony{

#ifndef PI
static const float PI = 3.1415926536;
#endif

/**
 * @brief gets the angle of a vector
 * @param v 
 * @return 
*/
inline float
VectorToAngle(const Dimencion& v){
  #ifdef UNREAL_HARMONY
  return atan2f(v.Y,v.X);
  #else
  return atan2f(v.y,v.x);
  #endif
}

inline Dimencion
AngleToVector(float v){
  #ifdef UNREAL_HARMONY
  return Dimencion(cos(v),sin(v),0);
  #else
  return Dimencion(cos(v),sin(v));
  #endif
}

/**
 * @brief mantains the value of the angle between pi and -pi
 * @param v 
 * @return 
*/
inline float
angleInRange(float v){
  return fmodf(fmodf(v+PI,PI*2)+PI*2,PI*2)-PI;
}

inline float
angleBetween(float v1, float v2){
  return angleInRange(v2-v1);
}

inline Vector2f
randomAngle(){
  auto randAngle = ((float)rand()/(float)RAND_MAX)*2.f*PI;
  return Vector2f(cos(randAngle),sin(randAngle));
}

}