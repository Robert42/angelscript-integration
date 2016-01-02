#include <angelscript-integration/ref-counted-object.h>

namespace AngelScriptIntegration {

// see also http://www.angelcode.com/angelscript/sdk/docs/manual/doc_adv_weakref.html

RefCountedObject::RefCountedObject()
{
}

RefCountedObject::~RefCountedObject()
{
  if(weakRefFlag)
    weakRefFlag->Release();
}


void RefCountedObject::addReference()
{
  AngelScript::asAtomicInc(referenceCount);
}

void RefCountedObject::releaseReference()
{
  if(referenceCount == 1 && weakRefFlag)
    weakRefFlag->Set(true);

  if(AngelScript::asAtomicDec(referenceCount) == 0)
    delete this;
}

AngelScript::asILockableSharedBool* RefCountedObject::get_weakrefFlag()
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

