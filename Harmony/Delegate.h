#pragma once
#ifndef DELEGATE_HPP
# define DELEGATE_HPP

namespace Harmony{

/**
 * @brief can execute functions, this is not my code, to be updated to a better implementation
*/
template<class U>
class Delegate
{
public:
    Delegate()
        : object_ptr(0)
        , stub_ptr(0)
    {}

    template <class T, void (T::*TMethod)(U)>
    static Delegate from_method(T* object_ptr)
    {
        Delegate d;
        d.object_ptr = object_ptr;
        d.stub_ptr = &method_stub<T, TMethod>; 
        return d;
    }

    void operator()(U a1) const
    {
        return (*stub_ptr)(object_ptr, a1);
    }

private:
    typedef void (*stub_type)(void* object_ptr, U);

    void* object_ptr;
    stub_type stub_ptr;

    template <class T, void (T::*TMethod)(U)>
    static void method_stub(void* object_ptr, U a1)
    {
        T* p = static_cast<T*>(object_ptr);
        return (p->*TMethod)(a1); 
    }
};

}


#endif