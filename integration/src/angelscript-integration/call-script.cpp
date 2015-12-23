#include <angelscript-integration/call-script.h>
#include <sdk/add_on/scriptbuilder/scriptbuilder.h>

#include <QMutex>
#include <QMutexLocker>

namespace AngelScriptIntegration {


AngelScript::asIScriptModule* loadAndCompileModule(AngelScript::asIScriptEngine* engine, const char* filepath, const char* moduleName)
{
  int r;
  AngelScript::CScriptBuilder builder;

  r = builder.StartNewModule(engine, moduleName); Q_ASSERT(r>=0);
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
