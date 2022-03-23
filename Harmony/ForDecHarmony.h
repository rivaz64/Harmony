#pragma once
#include <vector>
#include <map>
#include <string>
#include <iostream>

namespace Harmony{

using std::vector;
using std::map;
using std::string;

class Vector2f;
class Pawn;
class Controller;
class State;
class Message;
class BlackBoard;
class Action;

inline
void 
print(const Harmony::string& str){
  std::cout<<str<<std::endl;
}
}