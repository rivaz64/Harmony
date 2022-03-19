#include "ForDecHarmony.h"

#include "BlackBoard.h"

void main(){
  Harmony::BlackBoard bb;
  bb.addVariableOfType<Harmony::string>("test");
  bb.setVariableAs<Harmony::string>("test","working");
  Harmony::print(*bb.getVariableAs<Harmony::string>("test"));
}