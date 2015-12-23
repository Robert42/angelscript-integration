#ifndef ANGELSCRIPTINTEGRATION_H
#define ANGELSCRIPTINTEGRATION_H

#include <angelscript.h>
#include <QString>

namespace AngelScriptIntegration {

using AngelScript::asDWORD;

const asDWORD ACCESS_MASK_GLM = 1;

enum class GlmFlags
{
  NO_SWIZZLE = 0,
  ALL_SWIZZLE = 7
};

void init_message_callback_qt(AngelScript::asIScriptEngine* engine);
void init_logging_functions_qt(AngelScript::asIScriptEngine* engine);
void init_glm(AngelScript::asIScriptEngine* engine, GlmFlags swizzle);

void AngelScriptCheck(int returnCode);

} // namesapce AngelScriptIntegration

#endif // ANGELSCRIPTINTEGRATION_H
