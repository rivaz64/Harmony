#include "DNA.h"
namespace Harmony{

DNA::DNA(DNA& father, DNA& mother)
{
  //uint size = mother.m_genes.size();
  uint n = 0;
  for(auto& g : father.m_genes.m_data){
    m_genes.addVariableOfSize(g.first,g.second.size);
    uint d = rand()%2;
    uint m = rand()%36;
    if(m!=0){
      if(d==0){
        m_genes.setVariableAs(g.first,g.second.data);
      }
      else{
        m_genes.copyVariable(g.first,mother.m_genes.getVariablePointer(g.first));
      }
    }
    else{
      m_mutations[n](m_genes.getVariablePointer(g.first));
    }
    ++n;
  }
}

}


