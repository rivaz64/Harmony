#pragma once

namespace Harmony{

namespace CLASS{
enum E{
  Object,
  Pawn
  
};
}

/**
 * @brief the parent class of all objects in Harmony
*/
class Object
{
  virtual CLASS::E
  getClass();
};

}


