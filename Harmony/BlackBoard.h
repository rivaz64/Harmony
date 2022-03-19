#pragma once

#include "ForDecHarmony.h"

namespace Harmony{

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
       #ifdef _DEBUG
      print("key "+name+" allready exists");
      #endif
      return;
    }
    
    m_data.insert({name,reinterpret_cast<void*>(new T)});
  }
  
  /**
   * @brief reads a variable of the blackboard
   * @tparam T 
   * @param name 
   * @return 
  */
  template<class T>
  T*
  getVariableAs(const string& name)
  {
    
    if( m_data.find(name) == m_data.end()){
      #ifdef _DEBUG
      print("key "+name+" does not exists");
      #endif
      return nullptr;
    }
    
    return reinterpret_cast<T*>(m_data[name]);
  }
  
  /**
   * @brief writes to a variable of the keyboard
   * @tparam T 
   * @param name 
   * @param value 
   * @return 
  */
  template<class T>
  void
  setVariableAs(const string& name, const T& value)
  {
    
    if( m_data.find(name) == m_data.end()){
      #ifdef _DEBUG
      print("key "+name+" does not exists");
      #endif
      return;
    }
    *reinterpret_cast<T*>(m_data[name]) = value;
  }

 private:
  
  /**
   * @brief everything writen in the keyboard
  */
  map<string,void*> m_data;
};

}


