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


} // namespace AngelScriptIntegration

