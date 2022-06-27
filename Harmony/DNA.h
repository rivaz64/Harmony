#pragma once

#include "Prerequisites.h"
#include "BlackBoard.h"
#include "Delegate.h"

namespace Harmony{

/**
 * @brief the default data for a instance that is a mixture of 2 other instances
*/

class DNA
{
 public:

  void
  addData(void* data, size_t size);

  void
  mixData(const DNA& d1, const DNA& d2);

 private:
  vector<pair<void*,size_t>> m_data;

};

}


