#pragma once
#include "Prerequisites.h"
#include "Delegate.h"
namespace Harmony{

class GeneticAlgorithm
{
 public:

  GeneticAlgorithm(uint mutationProbability,
                   uint numOfParents,
                   uint numOfChilds,
                   vector<pair<size_t,Delegate<char*>*>>&& data,
                   Delegate<char*,uint*>* fitness):
    m_mutationProbability(mutationProbability),
    m_numOfParents(numOfParents),
    m_numOfChilds(numOfChilds),
    m_data(move(data)),
    m_fitness(fitness){}

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

  void
  nextGeneration();

  inline vector<char*>&
  getPopulation(){
    return m_population;
  }

 public:

  /**
   * @brief the posibility in 1 that a utation happen permember
  */
  uint m_mutationProbability;

  /**
   * @brief the number of best to make childs randomly
  */
  uint m_numOfParents;

  /**
   * @brief the number to eliminate each generation that will be replaced with childs
  */
  uint m_numOfChilds;

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
   * @brief calculates how fitt an instance is
  */
  Delegate<char*,uint*>* m_fitness; 

  
};


}

