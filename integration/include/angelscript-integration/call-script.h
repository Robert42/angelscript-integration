#ifndef ANGELSCRIPTINTEGRATION_CALLSCRIPT_H
#define ANGELSCRIPTINTEGRATION_CALLSCRIPT_H

#include <angelscript.h>
#include <QString>

namespace AngelScriptIntegration {

void pass_arg_to_angelscript(AngelScript::asIScriptContext*context, int i, bool value);
void pass_arg_to_angelscript(AngelScript::asIScriptContext*context, int i, qint8 value);
void pass_arg_to_angelscript(AngelScript::asIScriptContext*context, int i, quint8 value);
void pass_arg_to_angelscript(AngelScript::asIScriptContext*context, int i, qint16 value);
void pass_arg_to_angelscript(AngelScript::asIScriptContext*context, int i, quint16 value);
void pass_arg_to_angelscript(AngelScript::asIScriptContext*context, int i, qint32 value);
void pass_arg_to_angelscript(AngelScript::asIScriptContext*context, int i, quint32 value);
void pass_arg_to_angelscript(AngelScript::asIScriptContext*context, int i, qint64 value);
void pass_arg_to_angelscript(AngelScript::asIScriptContext*context, int i, quint64 value);

AngelScript::asIScriptModule* loadAndCompileModule(AngelScript::asIScriptEngine* engine, const char* filepath, const char* moduleName);
std::string getUniqueModuleName(AngelScript::asIScriptEngine* engine, const char* preferredModuleName);

template<typename T_return, typename... T_args>
T_return callScript(AngelScript::asIScriptEngine* engine, const QString& filepath, const char* functionDeclarationToCall, const char* preferredModuleName, const T_args&... args);

template<typename T_return, typename... T_args>
T_return callScriptFunction(AngelScript::asIScriptFunction* function, const T_args&... args);

} // namespace AngelScriptIntegration

#include "implementation/call-script.inl"

#endif // ANGELSCRIPTINTEGRATION_CALLSCRIPT_H
