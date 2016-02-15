#include <angelscript-integration/call-script.h>
#include <sdk/add_on/scriptbuilder/scriptbuilder.h>

#include <QMutex>
#include <QMutexLocker>
#include <QDebug>

namespace AngelScriptIntegration {


void pass_arg_to_angelscript(AngelScript::asIScriptContext* context, int i, bool value)
{
  context->SetArgDWord(i, value);
}

void pass_arg_to_angelscript(AngelScript::asIScriptContext* context, int i, qint8 value)
{
  context->SetArgByte(i, value);
}

void pass_arg_to_angelscript(AngelScript::asIScriptContext* context, int i, quint8 value)
{
  context->SetArgByte(i, value);
}

void pass_arg_to_angelscript(AngelScript::asIScriptContext* context, int i, qint16 value)
{
  context->SetArgWord(i, value);
}

void pass_arg_to_angelscript(AngelScript::asIScriptContext* context, int i, quint16 value)
{
  context->SetArgWord(i, value);
}

void pass_arg_to_angelscript(AngelScript::asIScriptContext* context, int i, qint32 value)
{
  context->SetArgDWord(i, value);
}

void pass_arg_to_angelscript(AngelScript::asIScriptContext* context, int i, quint32 value)
{
  context->SetArgDWord(i, value);
}

void pass_arg_to_angelscript(AngelScript::asIScriptContext* context, int i, qint64 value)
{
  context->SetArgQWord(i, value);
}

void pass_arg_to_angelscript(AngelScript::asIScriptContext* context, int i, quint64 value)
{
  context->SetArgQWord(i, value);
}

int handle_include_file(const char* c_include, const char* c_from, AngelScript::CScriptBuilder* builder, void* userParam)
{
  const QVector<QDir>& includeDirectories = *reinterpret_cast<QVector<QDir>*>(userParam);
  QString include = QString::fromStdString(c_include);
  QString from = QString::fromStdString(c_from);
  QDir currentDir = QFileInfo(from).dir();

  QFileInfo includedFile = currentDir.absoluteFilePath(include);

  for(const QDir& dir : includeDirectories)
  {
    if(includedFile.exists())
      break;

    includedFile = dir.absoluteFilePath(include);
  }

  if(!includedFile.exists())
  {
    qWarning() << "Couldn't find the inluding file" << include << "from the file" << from;
    return -1;
  }

  std::string foundFile = includedFile.absoluteFilePath().toStdString();
  return builder->AddSectionFromFile(foundFile.c_str());
}

AngelScript::asIScriptModule* loadAndCompileModule(AngelScript::asIScriptEngine* engine, const char* filepath, const char* moduleName, const ConfigCallScript& config)
{
  int r;
  AngelScript::CScriptBuilder builder;

  QVector<QDir> includeDirectories = config.includeDirectories;

  r = builder.StartNewModule(engine, moduleName); Q_ASSERT(r>=0);
  builder.SetIncludeCallback(handle_include_file, &includeDirectories);
  builder.GetModule()->SetAccessMask(config.accessMask);
  r = builder.AddSectionFromFile(filepath); Q_ASSERT(r>=0);
  r = builder.BuildModule(); Q_ASSERT(r>=0);

  return builder.GetModule();
}


/*!
\brief Returns a unique name for a module.

\param engine
\param preferredModuleName if no other module already has this name, this preferred name will be used. Otherwise, a number will be added.

\return
*/
std::string getUniqueModuleName(AngelScript::asIScriptEngine* engine, const char* preferredModuleName)
{
  std::string preferredName = preferredModuleName;

  for(int i=0; true; ++i)
  {
    std::string moduleName = i>1 ?  preferredName + "-" + std::to_string(i) : preferredName;

    if(engine->GetModule(moduleName.c_str()) == nullptr)
      return moduleName;
  }

  Q_UNREACHABLE();
}


} // namespace AngelScriptIntegration
