#include "Prerequisites.h"
//#include "Delegate.h"
#include "GeneticAlgorithm.h"




class Randomizer{
public:
void
randomLetter(char* letter){
  *letter = letters[rand()%27];
}

Harmony::string 
randomString(Harmony::uint n){
  Harmony::string s;
  s.resize(n);
  for(int i = 0; i<n; ++i){
    randomLetter(&(s[i]));
  }
}
Harmony::string letters = " abcdefghijklmnopqrstuvwxyz";

};


int main(int argc, char* argv[])
{
  Harmony::GeneticAlgorithm ga;
  ga.mutationProbability = 36;
  Harmony::string goal = "hello world";
  Randomizer r;
  auto mutation = Harmony::Delegate<char*>::createPtr<Harmony::Delegate<char*>,Randomizer,Randomizer::randomLetter>(&r);
  ga.m_data = {{sizeof(char),mutation},
               {sizeof(char),mutation},
               {sizeof(char),mutation},
               {sizeof(char),mutation},
               {sizeof(char),mutation},
               {sizeof(char),mutation},
               {sizeof(char),mutation},
               {sizeof(char),mutation},
               {sizeof(char),mutation},
               {sizeof(char),mutation},
               {sizeof(char),mutation},};

  Harmony::vector<Harmony::string> strings;
  for(int i = 0; i<12; ++i){
    strings.push_back(r.randomString(11));
  }

  //Harmony::print((int)sizeof(Harmony::MAZE_CELL));
}