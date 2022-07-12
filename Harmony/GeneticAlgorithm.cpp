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
    for(int actualPos = 0; actualPos<size; ++actualPos){
      (*m_data[actualPos].second)(m_population[i]+actualPos);
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
    if(fitnesses[i]>1){
      int a=0;
    }
  }
  /**
   * @brief TODO: change for a more efficient sort.
  */
  for(size_t i = 0; i<size-1; ++i){
    for(size_t o = i+1; o<size; ++o){
       if(fitnesses[i]<fitnesses[o]){
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

void
GeneticAlgorithm::nextGeneration()
{
  orderByFitness();
  vector<char*> newChilds(m_numOfChilds);
  auto size = m_population.size();
  newChilds.resize(m_numOfChilds);
  for(int i = 0; i<m_numOfChilds; ++i){
    newChilds[i] = new char[m_data.size()+1];
    newChilds[i][m_data.size()] = 0;
    int p1 = rand()%m_numOfParents;
    int p2 = rand()%m_numOfParents;
    while(p1==p2){
      p1 = rand()%m_numOfParents;
      p2 = rand()%m_numOfParents;
    }
    combine(m_population[p1],m_population[p2],newChilds[i]);
  }
  for(int i = 0; i<m_numOfChilds; ++i){
    delete m_population[size-m_numOfChilds+i];
    m_population[size-m_numOfChilds+i] = newChilds[i];
  }
}

}

