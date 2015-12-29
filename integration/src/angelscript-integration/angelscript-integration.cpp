#include <angelscript-integration/angelscript-integration.h>

#include <QDebug>
#include <QString>

namespace AngelScriptIntegration {

void handleMessage(const AngelScript::asSMessageInfo* message, void*);

void init_message_callback_qt(AngelScript::asIScriptEngine* engine)
{
  int r = engine->SetMessageCallback(AngelScript::asFUNCTION(handleMessage), nullptr, AngelScript::asCALL_CDECL); AngelScriptCheck(r);
}

void log_debug(const std::string& message);
void log_info(const std::string& message);
void log_warning(const std::string& message);
void log_critical(const std::string& message);

void init_logging_functions_qt(AngelScript::asIScriptEngine* engine)
{
  asDWORD previousMask = engine->SetDefaultAccessMask(ACCESS_MASK_ALL);

  int r;
  r = engine->RegisterGlobalFunction("void log_debug(const string &in)", AngelScript::asFUNCTION(log_debug), AngelScript::asCALL_CDECL); AngelScriptCheck(r);
  r = engine->RegisterGlobalFunction("void log_info(const string &in)", AngelScript::asFUNCTION(log_info), AngelScript::asCALL_CDECL); AngelScriptCheck(r);
  r = engine->RegisterGlobalFunction("void log_warning(const string &in)", AngelScript::asFUNCTION(log_warning), AngelScript::asCALL_CDECL); AngelScriptCheck(r);
  r = engine->RegisterGlobalFunction("void log_critical(const string &in)", AngelScript::asFUNCTION(log_critical), AngelScript::asCALL_CDECL); AngelScriptCheck(r);

  engine->SetDefaultAccessMask(previousMask);
}

void init_glm_vectors(AngelScript::asIScriptEngine* engine, GlmFlags swizzle);

void init_glm(AngelScript::asIScriptEngine* engine, GlmFlags swizzle)
{
  asDWORD previousMask = engine->SetDefaultAccessMask(ACCESS_MASK_GLM);

  init_glm_vectors(engine, swizzle);

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


#define CASE(x) case AngelScript::x:return #x;
const char* AngelScriptReturnCodeAsString(AngelScript::asERetCodes returnCode)
{
  switch(returnCode)
  {
    CASE(asSUCCESS)
	  CASE(asERROR)
	  CASE(asCONTEXT_ACTIVE)
	  CASE(asCONTEXT_NOT_FINISHED)
	  CASE(asCONTEXT_NOT_PREPARED)
	  CASE(asINVALID_ARG)
	  CASE(asNO_FUNCTION)
	  CASE(asNOT_SUPPORTED)
	  CASE(asINVALID_NAME)
	  CASE(asNAME_TAKEN)
	  CASE(asINVALID_DECLARATION)
	  CASE(asINVALID_OBJECT)
	  CASE(asINVALID_TYPE)
	  CASE(asALREADY_REGISTERED)
	  CASE(asMULTIPLE_FUNCTIONS)
	  CASE(asNO_MODULE)
	  CASE(asNO_GLOBAL_VAR)
	  CASE(asINVALID_CONFIGURATION)
	  CASE(asINVALID_INTERFACE)
	  CASE(asCANT_BIND_ALL_FUNCTIONS)
	  CASE(asLOWER_ARRAY_DIMENSION_NOT_REGISTERED)
	  CASE(asWRONG_CONFIG_GROUP)
	  CASE(asCONFIG_GROUP_IS_IN_USE)
	  CASE(asILLEGAL_BEHAVIOUR_FOR_TYPE)
	  CASE(asWRONG_CALLING_CONV)
	  CASE(asBUILD_IN_PROGRESS)
	  CASE(asINIT_GLOBAL_VARS_FAILED)
	  CASE(asOUT_OF_MEMORY)
	  CASE(asMODULE_IS_IN_USE)
  default:
    return "Unknown AngelScript ReturnCode";
  }
}
const char* AngelScriptExecutionReturnCodeAsString(AngelScript::asEContextState returnCode)
{
  switch(returnCode)
  {
  CASE(asEXECUTION_FINISHED)
  CASE(asEXECUTION_SUSPENDED)
  CASE(asEXECUTION_ABORTED)
  CASE(asEXECUTION_EXCEPTION)
  CASE(asEXECUTION_PREPARED)
  CASE(asEXECUTION_UNINITIALIZED)
  CASE(asEXECUTION_ACTIVE)
  CASE(asEXECUTION_ERROR)
  default:
    return "Unknown AngelScript Context State";
  }
}
#undef CASE

void AngelScriptCheck(int r)
{
  AngelScript::asERetCodes returnCode = static_cast<AngelScript::asERetCodes>(r);

  if(returnCode >= 0)
    return;

  const char* strReturnCode = AngelScriptReturnCodeAsString(returnCode);

  qCritical() << "AngelScriptCheck(): Error Code " << strReturnCode << " detected!";

  Q_ASSERT(returnCode >= 0);
}


void CheckExecutionResult(AngelScript::asIScriptContext* context, int r)
{
  if(r == AngelScript::asEXECUTION_FINISHED)
    return;

  AngelScript::asEContextState contextState = static_cast<AngelScript::asEContextState>(r);

  AngelScriptCheck(r);

  const char* strReturnCode = AngelScriptExecutionReturnCodeAsString(contextState);

  qCritical() << "CheckExecutionResult(): ContextState " << strReturnCode << " detected!";

  if(contextState == AngelScript::asEXECUTION_EXCEPTION)
    qCritical() << "Exception detected in " << context->GetExceptionFunction()->GetDeclaration() << " in line " << context->GetExceptionLineNumber() << "\nmessage: " << context->GetExceptionString();

  Q_ASSERT(contextState == AngelScript::asEXECUTION_FINISHED);
}


} // namespace AngelScriptIntegration

