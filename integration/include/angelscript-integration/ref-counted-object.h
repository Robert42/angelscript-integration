#ifndef ANGELSCRIPTINTEGRATION_REFCOUNTEDOBJECT_H
#define ANGELSCRIPTINTEGRATION_REFCOUNTEDOBJECT_H

#include <stdint.h>
#include "angelscript-integration.h"

namespace AngelScriptIntegration {

class RefCountedObject
{
public:
  RefCountedObject(const RefCountedObject&) = delete;
  RefCountedObject(RefCountedObject&&) = delete;
  RefCountedObject& operator=(const RefCountedObject&) = delete;
  RefCountedObject& operator=(RefCountedObject&&) = delete;

  void addReference();
  void releaseReference();

  AngelScript::asILockableSharedBool* get_weakReferenceFlag();

protected:
  RefCountedObject();
  virtual ~RefCountedObject();

  template<typename T>
  static void registerAsBaseOfClass(AngelScript::asIScriptEngine* engine, const char* className);

private:
  uint32_t referenceCount = 1;
  AngelScript::asILockableSharedBool* weakRefFlag = nullptr;
};


} // namespace AngelScriptIntegration

#include "./ref-counted-object.inl"

#endif // ANGELSCRIPTINTEGRATION_REFCOUNTEDOBJECT_H
