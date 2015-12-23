#include <angelscript.h>
#include <QString>

namespace AngelScriptIntegration {

using AngelScript::asDWORD;

const asDWORD ACCESS_MASK_GLM = 1;

void init_message_callback_qt(AngelScript::asIScriptEngine* engine);
void init_logging_functions_qt(AngelScript::asIScriptEngine* engine);
void init_glm(AngelScript::asIScriptEngine* engine);

} // AngelScriptIntegration
