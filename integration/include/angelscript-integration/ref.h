#ifndef ANGELSCRIPTINTEGRATION_REF_H
#define ANGELSCRIPTINTEGRATION_REF_H

#include "ref-counted-object.h"

namespace AngelScriptIntegration {

template<typename T>
class ref final
{
  static_assert(std::is_base_of<RefCountedObject, T>::value ||
                std::is_same<RefCountedObject, T>::value,
                "T must inherit from RefCountedObject");

public:
  explicit ref(T* ptr=nullptr);
  ref(const ref<T>& other);
  ref(ref<T>&& other);
  ~ref();

  ref<T>& operator=(const ref<T>& other);
  ref<T>& operator=(ref<T>&& other);

  T* addReference();
  T* ptr();

  T* operator->();

  bool isNull() const;
  void reset();

private:
  T* _ptr;
};


} // namespace AngelScriptIntegration


#include "ref.inl"

#endif // ANGELSCRIPTINTEGRATION_REF_H
