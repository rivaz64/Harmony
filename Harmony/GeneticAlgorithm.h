#pragma once
#include "Prerequisites.h"
#include "Delegate.h"
#include "DNA.h"
namespace Harmony{

class GeneticAlgorithm
{
 public:

  void
  init(size_t n);

  void
  init(const vector<char*>& v);

  void
  init();

  void
  orderByFitness();

  void
  combine(char* data1, char* data2, char* data);

 public:

  /**
   * @brief the population to put at test
  */
  vector<char*> m_population;

  /**
   * @brief 
   * how much the member is in size
   * the mutation to aply to this member
  */
  vector<pair<size_t,Delegate<char*>*>> m_data;

  /**
   * @brief the posibility in 1 that a utation happen permember
  */
  uint m_mutationProbability;

  /**
   * @brief calculates how fitt an instance is
  */
  Delegate<char*,uint*>* m_fitness; 


};


}

