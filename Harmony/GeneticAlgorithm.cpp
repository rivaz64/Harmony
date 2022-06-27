#include "GeneticAlgorithm.h"

namespace Harmony{

void 
GeneticAlgorithm::init(size_t n)
{
  m_population.resize(n);
  init();
}

void 
GeneticAlgorithm::init(const vector<char*>& v)
{
  m_population = v;
  init();
}

void 
GeneticAlgorithm::init()
{
  auto n = m_population.size();
  auto size = m_data.size();
  size_t actualPos = 0;
  for(int i = 0; i<n; ++i){
    for(int i = 0; i<size; ++i){
      (*m_data[i].second)(m_population[n]+actualPos);
    }
  }
}

void 
GeneticAlgorithm::orderByFitness()
{
  auto size = m_population.size();
  vector<uint> fitnesses(size);
  for(size_t i = 0; i<size; ++i){
    (*m_fitness)(m_population[i],&fitnesses[i]);
  }
  /**
   * @brief todo: change for a more efficient sort.
  */
  for(size_t i = 0; i<size-1; ++i){
    for(size_t o = i+1; o<size; ++o){
       if(fitnesses[i]>fitnesses[o]){
         swap(fitnesses[i],fitnesses[o]);
         swap(m_population[i],m_population[o]);
       }
    }
  }

}

void
GeneticAlgorithm::combine(char* data1, char* data2, char* data)
{
  auto size = m_data.size();
  size_t actualPos = 0;
  for(int i = 0; i<size; ++i){
    uint mutation = rand()%m_mutationProbability;
    if(mutation == 0){
      (*m_data[i].second)(data+actualPos);
      
    }
    else{
      uint selected = rand()%2;
      if(selected == 0){
        memcpy(data+actualPos,data1+actualPos,m_data[i].first);
      }
      else{
        memcpy(data+actualPos,data2+actualPos,m_data[i].first);
      }
    }
    actualPos += m_data[i].first;
  }
}

}

