#include "Prerequisites.h"
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
  return s;
}

void
isAns(char* c,Harmony::uint* ans){
  *ans = 0;
  for(int i = 0;i<goal.size();++i){
    if(goal[i] == c[i]){
      ++(*ans);
    }
  }
}

Harmony::string letters = " abcdefghijklmnopqrstuvwxyz";
Harmony::string goal = "hello world";

};


int main(int argc, char* argv[])
{
  Harmony::bind()
  //Randomizer *r = new Randomizer;
  //auto mutation = Harmony::Delegate<char*>::createPtr<Harmony::Delegate<char*>,Randomizer,&Randomizer::randomLetter>(r);
  //auto goal = Harmony::Delegate<char*,Harmony::uint*>::createPtr<Harmony::Delegate<char*,Harmony::uint*>,Randomizer,&Randomizer::isAns>(r);
  //int totalPop = 66;
  //Harmony::GeneticAlgorithm ga(36,11,55,
  //{{sizeof(char),mutation},
  // {sizeof(char),mutation},
  // {sizeof(char),mutation},
  // {sizeof(char),mutation},
  // {sizeof(char),mutation},
  // {sizeof(char),mutation},
  // {sizeof(char),mutation},
  // {sizeof(char),mutation},
  // {sizeof(char),mutation},
  // {sizeof(char),mutation},
  // {sizeof(char),mutation},},
  // goal);
  //
  //Harmony::vector<Harmony::string> strings;
  //Harmony::vector<char*> chars;
  //strings.resize(totalPop);
  //chars.resize(totalPop);
  //for(int i = 0; i<totalPop; ++i){
  //  strings[i] = r->randomString(11);
  //  chars[i] = new char[12];
  //  memcpy(chars[i],(char*)strings[i].c_str(),12);
  //}
  //ga.init(chars);
  //int a;
  //while(true){
  //  for(int o=0; o<7776; ++o){
  //    ga.nextGeneration();
  //  }
  //  auto& pop = ga.getPopulation();
  //  for(int i = 0; i<totalPop; ++i){
  //    Harmony::print(pop[i]);
  //  }
  //  Harmony::print("");
  //  std::cin>>a;
  //}
  
}