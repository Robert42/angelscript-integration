#ifndef ANGELSCRIPTINTEGRATION_REFCOUNTEDOBJECT_INL
#define ANGELSCRIPTINTEGRATION_REFCOUNTEDOBJECT_INL

#include "./ref-counted-object.h"

namespace AngelScriptIntegration {


template<typename T>
void RefCountedObject::registerAsBaseOfClass(AngelScript::asIScriptEngine* engine, const char* className)
{
  static_assert(std::is_base_of<RefCountedObject, T>::value, "T must inherit from AngelScriptIntegration::RefCountedObject");

  int r = 0;

  r = engine->RegisterObjectBehaviour(className, AngelScript::asBEHAVE_ADDREF, "void f()", AngelScript::asMETHOD(T,addReference), AngelScript::asCALL_THISCALL); AngelScriptCheck(r);
  r = engine->RegisterObjectBehaviour(className, AngelScript::asBEHAVE_RELEASE, "void f()", AngelScript::asMETHOD(T,releaseReference), AngelScript::asCALL_THISCALL); AngelScriptCheck(r);
  r = engine->RegisterObjectBehaviour(className, AngelScript::asBEHAVE_GET_WEAKREF_FLAG, "int& f()", AngelScript::asMETHOD(T,get_weakrefFlag), AngelScript::asCALL_THISCALL); AngelScriptCheck(r);
}

template<typename T>
ref<T> RefCountedObject::as_ref()
{
  Q_ASSERT(dynamic_cast<T*>(this) != nullptr);

  T* ptr = static_cast<T*>(this);

  ptr->addReference();

  return ref<T>(ptr);
}


} // namespace AngelScriptIntegration

#endif // ANGELSCRIPTINTEGRATION_REFCOUNTEDOBJECT_INL
