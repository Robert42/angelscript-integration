#ifndef ANGELSCRIPTINTEGRATION_IMPLEMENTATION_FUNCTIONWRAPPER_H
#define ANGELSCRIPTINTEGRATION_IMPLEMENTATION_FUNCTIONWRAPPER_H

#include <angelscript-integration/ref.h>
#include <angelscript-integration/weakref.h>

namespace AngelScriptIntegration {
namespace impl {


// see also http://www.angelcode.com/angelscript/sdk/docs/manual/doc_obj_handle.html
// see also http://www.angelcode.com/angelscript/sdk/docs/manual/doc_generic.html

template<typename T_function>
class WrapMethodWithReferences;




template<typename T>
inline void result_updateRefCount(const T&){}

template<typename T>
inline void result_updateRefCount(ref<T>& t) = delete;

template<typename T>
inline void result_updateRefCount(const ref<T>& t) = delete;

template<typename T>
inline void result_updateRefCount(ref<T> t)
{
  t.ptr()->addReference();
}

template<typename T_class, typename T_return, typename... T_args>
struct WrapMethodWithReferences<T_return(T_class::*)(T_args...)>
{
public:
  typedef T_return(T_class::*function_ptr)(T_args...);

  template<function_ptr function>
  struct BindFunction
  {
    T_return call(T_args... arg)
    {
      T_class* instance = static_cast<T_class>(this);

      T_return result = (instance->*function)(arg...);

      result_updateRefCount(result);

      return result;
    }
  };
};

#define asMETHOD_WITH_REF(CLASS, METHOD) AngelScript::asMETHOD(AngelScriptIntegration::impl::WrapMethodWithReferences<decltype(&CLASS::METHOD)>::BindFunction<&CLASS::METHOD>, call)

} // impl
} // AngelScriptIntegration

#endif // ANGELSCRIPTINTEGRATION_IMPLEMENTATION_FUNCTIONWRAPPER_H
