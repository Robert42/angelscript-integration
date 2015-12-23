#include <angelscript.h>
#include <QString>

namespace AngelScriptIntegration {

using AngelScript::asDWORD;

const asDWORD ACCESS_MASK_GLM = 1;

void init_message_callback_qt(AngelScript::asIScriptEngine* engine);
void init_logging_functions_qt(AngelScript::asIScriptEngine* engine);
void init_glm(AngelScript::asIScriptEngine* engine);


void log_debug(const std::string& message);
void log_info(const std::string& message);
void log_warning(const std::string& message);
void log_critical(const std::string& message);

void log_debug(const QString& message);
void log_info(const QString& message);
void log_warning(const QString& message);
void log_critical(const QString& message);

} // AngelScriptIntegration
