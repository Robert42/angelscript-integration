#include <angelscript-integration/angelscript-integration.h>

#include <QDebug>
#include <QString>

namespace AngelScriptIntegration {

void handleMessage(const AngelScript::asSMessageInfo* message, void*);

void init_message_callback_qt(AngelScript::asIScriptEngine* engine)
{
  int r = engine->SetMessageCallback(AngelScript::asFUNCTION(handleMessage), nullptr, AngelScript::asCALL_CDECL); Q_ASSERT(r >= 0);
}

void log_debug(const std::string& message);
void log_info(const std::string& message);
void log_warning(const std::string& message);
void log_critical(const std::string& message);

void init_logging_functions_qt(AngelScript::asIScriptEngine* engine)
{
  int r;
  r = engine->RegisterGlobalFunction("void log_debug(const string &in)", AngelScript::asFUNCTION(log_debug), AngelScript::asCALL_CDECL); Q_ASSERT(r >= 0);
  r = engine->RegisterGlobalFunction("void log_info(const string &in)", AngelScript::asFUNCTION(log_info), AngelScript::asCALL_CDECL); Q_ASSERT(r >= 0);
  r = engine->RegisterGlobalFunction("void log_warning(const string &in)", AngelScript::asFUNCTION(log_warning), AngelScript::asCALL_CDECL); Q_ASSERT(r >= 0);
  r = engine->RegisterGlobalFunction("void log_critical(const string &in)", AngelScript::asFUNCTION(log_critical), AngelScript::asCALL_CDECL); Q_ASSERT(r >= 0);
}


void init_glm(AngelScript::asIScriptEngine* engine)
{
  asDWORD previousMask = engine->SetDefaultAccessMask(ACCESS_MASK_GLM);


  engine->SetDefaultAccessMask(previousMask);
}

void log_debug(const QString& message);
void log_info(const QString& message);
void log_warning(const QString& message);
void log_critical(const QString& message);


void handleMessage(const AngelScript::asSMessageInfo* message, void*)
{
  QString text = QString("Angelscript -- %0 (%1  %2):\n%3").arg(message->section).arg(message->row).arg(message->col).arg(message->message);
  switch(message->type)
  {
  case AngelScript::asMSGTYPE_ERROR:
    log_critical(text);
    break;
  case AngelScript::asMSGTYPE_WARNING:
    log_warning(text);
    break;
  case AngelScript::asMSGTYPE_INFORMATION:
    log_info(text);
    break;
  default:
    Q_UNREACHABLE();
  }
}

void log_debug(const QString& message)
{
  log_debug(message.toStdString());
}

void log_info(const QString& message)
{
  log_info(message.toStdString());
}

void log_warning(const QString& message)
{
  log_warning(message.toStdString());
}

void log_critical(const QString& message)
{
  log_critical(message.toStdString());
}

void log_debug(const std::string& message)
{
  qDebug() << message.c_str();
}

void log_info(const std::string& message)
{
  qInfo() << message.c_str();
}

void log_warning(const std::string& message)
{
  qWarning() << message.c_str();
}

void log_critical(const std::string& message)
{
  qCritical() << message.c_str();
}



} // AngelScriptIntegration

