#pragma once
#ifndef DELEGATE_HPP
# define DELEGATE_HPP
#include "Prerequisites.h"
#include "Debuger.h"
namespace Harmony{

/**
 * @brief the parent class for every type of delegate
*/
class Delegator 
{
 public:
  virtual void
  execute() 
  {
    print("void execution");
  }
};

/**
 * @brief can execute functions, this is not my code, to be updated to a better implementation
*/
template<typename... _Types>
class Delegate :
  public Delegator
{
 public:
  Delegate()
      : object_ptr(0)
      , stub_ptr(0)
  {}

  template <class DelegatorType, class T,void (T::*TMethod)(_Types...)>
  static Delegate create(T* object_ptr, _Types... _Args)
  {
      DelegatorType d(std::forward<_Types>(_Args)...);
      d.object_ptr = object_ptr;
      d.stub_ptr = &method_stub<T, TMethod>; 
      return d;
  }

  void 
  operator()(_Types&&... _Args) const
  {
      return (*stub_ptr)(object_ptr, std::forward<_Types>(_Args)...);
  }

 private:
  typedef void (*stub_type)(void* object_ptr, _Types&&...);

  void* object_ptr;
  stub_type stub_ptr;

  template <class T, void (T::*TMethod)(_Types...)>
  static void method_stub(void* object_ptr, _Types&&... _Args)
  {
      T* p = static_cast<T*>(object_ptr);
      return (p->*TMethod)(std::forward<_Types>(_Args)...); 
  }
};

}


#endif