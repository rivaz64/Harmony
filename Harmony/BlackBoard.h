#pragma once

#include "Prerequisites.h"


#ifdef _DEBUG
#include "Debuger.h"
#endif

namespace Harmony{

//struct BlackBoardNode{
//  void* data;
//  size_t size;
//};

/**
 * @brief a blackboard
*/
class BlackBoard
{
 public:
  /**
   * @brief adds a variable to the blackboard
   * @tparam T 
   * @param name 
  */
  template<class T>
  void
  addVariableOfType(const string& name)
  {
   
    if( m_data.find(name) != m_data.end()){
      return;
    }
    //m_data.insert({name,new Object});
    m_data.insert({name,{reinterpret_cast<void*>(new T)}});
  }
  
  /**
   * @brief reads a variable of the blackboard
   * @tparam T 
   * @param name 
   * @return 
  */
  template<class T>
  T*
  getVariableAs(const string& name) const
  {
    
    if( m_data.find(name) == m_data.end()){
      return nullptr;
    }
    //return m_data[name];
    return reinterpret_cast<T*>(m_data.at(name));
  }
  
  

  /**
   * @brief writes to a variable of the keyboard
   * @tparam T 
   * @param name 
   * @param value 
   * @return 
  */
  template<class T>
  inline void
  setVariableAs(const string& name,const T& value)
  { 
    if( m_data.find(name) == m_data.end()){
      return;
    }
    *((T*)m_data[name]) = value;
  }

  

  /**
   * @brief copys a variable without knowing its type
   * @param name 
   * @param value 
  */
  //inline void
  //copyVariable(const string& name, void* value)
  //{
  //  if( m_data.find(name) == m_data.end()){
  //    return;
  //  }
  //  memcpy(m_data[name],value,m_data[name].size);
  //}

  inline uint 
  size() const{
    m_data.size();
  }

 private:
  
  /**
   * @brief everything writen in the keyboard
  */
  map<string,void*> m_data;

  friend class DNA;
  //map<string,void*> m_data;
};

}
