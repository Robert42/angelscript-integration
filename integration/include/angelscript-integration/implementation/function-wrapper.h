#ifndef ANGELSCRIPTINTEGRATION_IMPLEMENTATION_FUNCTIONWRAPPER_H
#define ANGELSCRIPTINTEGRATION_IMPLEMENTATION_FUNCTIONWRAPPER_H

#include <angelscript-integration/ref.h>
#include <angelscript-integration/weakref.h>

namespace AngelScriptIntegration {
namespace impl {


// see also http://www.angelcode.com/angelscript/sdk/docs/manual/doc_obj_handle.html
// see also http://www.angelcode.com/angelscript/sdk/docs/manual/doc_generic.html


template<typename T>
inline T result_updateRefCount(T t){return t;}

template<typename T>
inline T* result_updateRefCount(const ref<T>& t)
{
  t.ptr()->addReference();
  return t.ptr();
}


template <typename T>
struct ReturnType
{
  typedef  T type;
};

template <typename T>
struct ReturnType<ref<T>>
{
  typedef T* type;
};



template<typename T_function>
class WrapMethodWithReferences;

template<typename T_class, typename T_return, typename... T_args>
struct WrapMethodWithReferences<T_return(T_class::*)(T_args...)>
{
public:
  typedef T_return(T_class::*function_ptr)(T_args...);

  typedef typename ReturnType<T_return>::type T_return_filtered;

  template<function_ptr function>
  struct BindFunction
  {
    T_return_filtered call(T_args... arg)
    {
      T_class* instance = static_cast<T_class>(this);

      return result_updateRefCount((instance->*function)(arg...));
    }
  };
};



template<typename T_function>
class WrapFunctionWithReferences;

template<typename T_return, typename... T_args>
struct WrapFunctionWithReferences<T_return(T_args...)>
{
public:
  typedef T_return(function_ptr)(T_args...);

  typedef typename ReturnType<T_return>::type T_return_filtered;

  template<function_ptr function>
  struct BindFunction
  {
    static T_return_filtered call(T_args... arg)
    {
      return result_updateRefCount(function(arg...));
    }
  };
};

#define asMETHOD_WITH_REF(CLASS, METHOD) AngelScript::asMETHOD(AngelScriptIntegration::impl::WrapMethodWithReferences<decltype(&CLASS::METHOD)>::BindFunction<&CLASS::METHOD>, call)
#define asFUNCTION_WITH_REF(FUNCTION) AngelScript::asFUNCTION(AngelScriptIntegration::impl::WrapFunctionWithReferences<decltype(FUNCTION)>::BindFunction<FUNCTION>::call)

} // impl
} // AngelScriptIntegration

#endif // ANGELSCRIPTINTEGRATION_IMPLEMENTATION_FUNCTIONWRAPPER_H
