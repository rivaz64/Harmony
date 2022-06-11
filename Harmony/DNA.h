#pragma once

#include "Prerequisites.h"
#include "BlackBoard.h"

namespace Harmony{

/**
 * @brief the default data for a instance that is a mixture of 2 other instances
*/

namespace GENE{
enum E{
FLOAT,
INT
};
}

class DNA
{
 public:
  
  /**
   * @brief build the base gene with the types is going to have
   * @param genes 
  */
  DNA(const BlackBoard& genes) : m_genes(genes) {}

  DNA(const DNA& father, const DNA& mother);

 private:
  BlackBoard m_genes;
};

}


