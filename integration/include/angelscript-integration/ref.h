#ifndef ANGELSCRIPTINTEGRATION_REF_H
#define ANGELSCRIPTINTEGRATION_REF_H

#include <stdint.h>
#include "angelscript-integration.h"

namespace AngelScriptIntegration {

class RefCountedObject;

template<typename T>
class ref final
{
public:
  explicit ref(T* ptr=nullptr);
  ref(const ref<T>& other);
  ref(ref<T>&& other);
  ~ref();

  ref<T>& operator=(const ref<T>& other);
  ref<T>& operator=(ref<T>&& other);

  T* addReference();
  T* ptr() const;

  T* operator->() const;

  bool operator==(const ref<T>& other) const;
  bool operator!=(const ref<T>& other) const;
  bool operator==(T* other) const;
  bool operator!=(T* other) const;
  friend bool operator==(T* a, const ref<T>& b){return b == a;}
  friend bool operator!=(T* a, const ref<T>& b){return b != a;}

  bool isNull() const;
  void reset();

  void swap(ref<T>& other);

private:
  T* _ptr;
};


} // namespace AngelScriptIntegration


#include "ref.inl"
#include "implementation/function-wrapper.h"

#endif // ANGELSCRIPTINTEGRATION_REF_H
