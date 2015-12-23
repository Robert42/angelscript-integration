#ifndef ANGELSCRIPTINTEGRATION_CALLSCRIPT_H
#define ANGELSCRIPTINTEGRATION_CALLSCRIPT_H

#include <angelscript.h>
#include <QString>

namespace AngelScriptIntegration {

void pass_arg_to_angelscript(AngelScript::asIScriptContext*context, bool value);
void pass_arg_to_angelscript(AngelScript::asIScriptContext*context, qint8 value);
void pass_arg_to_angelscript(AngelScript::asIScriptContext*context, quint8 value);
void pass_arg_to_angelscript(AngelScript::asIScriptContext*context, qint16 value);
void pass_arg_to_angelscript(AngelScript::asIScriptContext*context, quint16 value);
void pass_arg_to_angelscript(AngelScript::asIScriptContext*context, qint32 value);
void pass_arg_to_angelscript(AngelScript::asIScriptContext*context, quint32 value);
void pass_arg_to_angelscript(AngelScript::asIScriptContext*context, qint64 value);
void pass_arg_to_angelscript(AngelScript::asIScriptContext*context, quint64 value);

AngelScript::asIScriptModule* loadAndCompileModule(AngelScript::asIScriptEngine* engine, const char* filepath, const char* moduleName);
std::string getUniqueModuleName(AngelScript::asIScriptEngine* engine, const char* preferredModuleName);

template<typename T_return, typename... T_args>
T_return callScript(AngelScript::asIScriptEngine* engine, const QString& filepath, const char* functionToCall, const char* preferredModuleName, const T_args&... args);

} // namespace AngelScriptIntegration

#include "implementation/call-script.inl"

#endif // ANGELSCRIPTINTEGRATION_CALLSCRIPT_H
