#ifndef ANGELSCRIPTINTEGRATION_WEAKREF_H
#define ANGELSCRIPTINTEGRATION_WEAKREF_H

#include "ref.h"

namespace AngelScriptIntegration {

template<typename T>
class weakref final
{
  static_assert(std::is_base_of<RefCountedObject, T>::value ||
                std::is_same<RefCountedObject, T>::value,
                "T must inherit from RefCountedObject");

public:
  weakref();
  explicit weakref(const ref<T>& ptr);
  weakref(const weakref<T>& other);
  weakref(weakref<T>&& other);
  ~weakref();

  weakref<T>& operator=(const ref<T>& ptr);
  weakref<T>& operator=(const weakref<T>& other);
  weakref<T>& operator=(weakref<T>&& other);

  ref<T> lock();

  bool isNull() const;
  void reset();

  void swap(weakref<T>& other);

private:
  T* _ptr;
  AngelScript::asILockableSharedBool* _is_deleted;

  void class_invariant();
};


} // namespace AngelScriptIntegration


#include "weakref.inl"

#endif // ANGELSCRIPTINTEGRATION_WEAKREF_H
