#include "DNA.h"
namespace Harmony{

void 
DNA::addData(void* data, size_t size)
{
  m_data.push_back({data,size});
}

void 
DNA::mixData(const DNA& d1, const DNA& d2)
{ 
  size_t size = m_data.size();
  for(uint i = 0; i<size; ++i){
    uint selected = rand()%2;
    if(selected == 0){
      memcpy(m_data[i].first,d1.m_data[i].first,m_data[i].second);
    }
    else{
      memcpy(m_data[i].first,d2.m_data[i].first,m_data[i].second);
    }
  }
}

}


