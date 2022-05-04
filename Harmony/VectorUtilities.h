#pragma once

#include "Prerequisites.h"

namespace Harmony{
  
template<typename T>
inline T
average(const vector<T>& list){
  T ans;
  memset(&ans,0,sizeof(T));
  for(auto& i : list){
    ans += i;
  }
  return ans / static_cast<float>(list.size());
}

template<typename T>
inline T
farest(const vector<T>& list, const T& point){
  T ans; 
  float maxDist = 0;
  float actualDist;
  for(auto& i : list){
    actualDist = size(i-point);
    if(actualDist>maxDist){
      ans = i;
      maxDist = actualDist;
    }
  }
  return ans;
}


}