#ifndef ANGELSCRIPTINTEGRATION_IMPLEMENTATION_FUNCTIONWRAPPER_H
#define ANGELSCRIPTINTEGRATION_IMPLEMENTATION_FUNCTIONWRAPPER_H

#include <angelscript.h>

namespace AngelScriptIntegration {
namespace impl {

template<typename T_function>
class WrapMethodWithReferences;

template<typename T_class, typename T_return, typename... T_args>
struct WrapMethodWithReferences<T_return(T_class::*)(T_args...)>
{
public:
  typedef T_return(T_class::*function_ptr)(T_args...);

  template<function_ptr function>
  struct BindFunction
  {
    static T_return call(T_class* instance, T_args... arg)
    {
      return (instance->*function)(arg...);
    }
  };
};

#define asMETHOD_WITH_REF(CLASS, METHOD) AngelScript::asFUNCTION(AngelScriptIntegration::impl::WrapMethodWithReferences<decltype(&CLASS::METHOD)>::BindFunction<&CLASS::METHOD>::call)

} // impl
} // AngelScriptIntegration

#endif // ANGELSCRIPTINTEGRATION_IMPLEMENTATION_FUNCTIONWRAPPER_H
