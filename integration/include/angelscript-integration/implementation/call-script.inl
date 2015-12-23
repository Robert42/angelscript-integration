#ifndef ANGELSCRIPTINTEGRATION_CALLSCRIPT_INL
#define ANGELSCRIPTINTEGRATION_CALLSCRIPT_INL

#include "../call-script.h"

namespace AngelScriptIntegration {


template<typename T_return, typename... T_args>
T_return callScript(AngelScript::asIScriptEngine* engine, const std::string& filepath, const char* functionToCall, const char* preferredModuleName, const T_args&... args)
{
  std::string moduleName = getUniqueModuleName(engine, preferredModuleName);
  AngelScript::asIScriptModule* module = loadAndCompileModule(engine, filepath.c_str(), moduleName.c_str());
}


} // namespace AngelScriptIntegration

#endif // ANGELSCRIPTINTEGRATION_CALLSCRIPT_INL

