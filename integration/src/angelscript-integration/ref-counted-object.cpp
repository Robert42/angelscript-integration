#include <angelscript-integration/ref-counted-object.h>

namespace AngelScriptIntegration {


RefCountedObject::RefCountedObject()
{
}

RefCountedObject::~RefCountedObject()
{
}


void RefCountedObject::addReference()
{
  ++referenceCount;
}

void RefCountedObject::releaseReference()
{
  if(--referenceCount == 0)
    delete this;
}

AngelScript::asILockableSharedBool* RefCountedObject::get_weakReferenceFlag()
{
  if(!weakRefFlag)
  {
    AngelScript::asAcquireExclusiveLock();

    if(!weakRefFlag)
      weakRefFlag = AngelScript::asCreateLockableSharedBool();

    AngelScript::asReleaseExclusiveLock();
  }

  return weakRefFlag;
}


} // namespace AngelScriptIntegration

