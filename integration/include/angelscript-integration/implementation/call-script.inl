#ifndef ANGELSCRIPTINTEGRATION_CALLSCRIPT_INL
#define ANGELSCRIPTINTEGRATION_CALLSCRIPT_INL

#include "../call-script.h"

namespace AngelScriptIntegration {
namespace Implementation {

inline void _pass_arguments_to_angelscript(AngelScript::asIScriptContext*, int)
{
}

template<typename T_arg_i, typename... T_args>
void _pass_arguments_to_angelscript(AngelScript::asIScriptContext* context, int i, const T_arg_i& arg_i, const T_args&... other_args)
{
  pass_arg_to_angelscript(context, i, arg_i);

  _pass_arguments_to_angelscript(context, i+1, other_args...);
}

} // namespace Implementation


template<typename T_return, typename... T_args>
T_return callScriptFunction(AngelScript::asIScriptFunction* function, const T_args&... args)
{
  static_assert(std::is_same<T_return, void>::value, "Return types other than void are currently not supported");

  Q_ASSERT(function != nullptr);
  AngelScript::asIScriptEngine* engine = function->GetEngine();

  AngelScript::asIScriptContext* context = engine->CreateContext();

  context->Prepare(function);

  Implementation::_pass_arguments_to_angelscript(context, 0, args...);

  int r = context->Execute();

  Q_ASSERT(r == AngelScript::asEXECUTION_FINISHED);

  context->Release();
}


template<typename T_return, typename... T_args>
T_return callScript(AngelScript::asIScriptEngine* engine, const std::string& filepath, const char* functionDeclarationToCall, const char* preferredModuleName, const T_args&... args)
{
  std::string moduleName = getUniqueModuleName(engine, preferredModuleName);
  AngelScript::asIScriptModule* module = loadAndCompileModule(engine, filepath.c_str(), moduleName.c_str());

  AngelScript::asIScriptFunction* function = module->GetFunctionByDecl(functionDeclarationToCall);

  Q_ASSERT(function != nullptr);

  return callScriptFunction<T_return>(function, args...);
}


} // namespace AngelScriptIntegration

#endif // ANGELSCRIPTINTEGRATION_CALLSCRIPT_INL

