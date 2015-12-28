#include <angelscript-integration/change-working-dir.h>

namespace AngelScriptIntegration {

ChangeWorkingDir::ChangeWorkingDir(const QDir& currentDir)
  : oldDir(QDir::current())
{
  QDir::setCurrent(currentDir.path());
}

ChangeWorkingDir::~ChangeWorkingDir()
{
  QDir::setCurrent(oldDir.path());
}

} // namespace AngelScriptIntegration
