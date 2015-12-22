#include <angelscript-integration/angelscript-integration.h>

#include <QDebug>
#include <QString>

namespace AngelScriptIntegration {

void handleMessage(const AngelScript::asSMessageInfo* message, void*)
{
  std::string text = QString("Angelscript -- %0 (%1  %2):\n%3").arg(message->section).arg(message->row).arg(message->col).arg(message->message).toStdString();
  switch(message->type)
  {
  case AngelScript::asMSGTYPE_ERROR:
    qCritical() << text.c_str();
    break;
  case AngelScript::asMSGTYPE_WARNING:
    qWarning() << text.c_str();
    break;
  case AngelScript::asMSGTYPE_INFORMATION:
    qDebug() << text.c_str();
    break;
  default:
    Q_UNREACHABLE();
  }
}

void init_message_callback_qt(AngelScript::asIScriptEngine* engine)
{
  engine->SetMessageCallback(asFUNCTION(handleMessage), nullptr, AngelScript::asCALL_CDECL);
}

} // AngelScriptIntegration

