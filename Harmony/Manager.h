#pragma once
#include "ForDecHarmony.h"

namespace Harmony{

namespace PAWNS{
enum E{
  GOER=0,
  VIEW
};
}

/**
 * @brief Harmony itself
*/
class Manager
{
 public:

  Manager();

  /**
   * @brief adds a pawn to be controlled by harmony
   * @param  
  */
  void
  addPawn(Pawn* pawn, PAWNS::E type);

  /**
   * @brief updates all the controllers
   * @param delta 
  */
  void
  update(float delta);

 private:
  vector<Controller*> controllers;
  map<string,State*> states;
  map<string,Action*> actions;

};

}

