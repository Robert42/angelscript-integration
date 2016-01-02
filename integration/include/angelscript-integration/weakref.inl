#ifndef ANGELSCRIPTINTEGRATION_REF_INL
#define ANGELSCRIPTINTEGRATION_REF_INL

#include "weakref.h"

namespace AngelScriptIntegration {


template<typename T>
inline void weakref<T>::class_invariant()
{
  Q_ASSERT((_ptr==nullptr) == (_is_deleted==nullptr));
}

template<typename T>
weakref<T>::weakref()
  : _ptr(nullptr),
    _isvalid(nullptr)
{
}

template<typename T>
weakref<T>::weakref(const ref<T>& ptr)
  : _ptr(ptr.ptr()),
    _is_deleted(_ptr ? _ptr->get_weakrefFlag() : nullptr)
{
  class_invariant();
}

template<typename T>
weakref::weakref(const weakref<T>& other)
  : _ptr(other._ptr),
    _is_deleted(other._is_deleted)
{
  if(_is_deleted)
    _is_deleted->addReference();

  class_invariant();
}

template<typename T>
weakref::weakref(weakref<T>&& other)
  : _ptr(other._ptr),
    _is_deleted(other._is_deleted)
{
  other._ptr = nullptr;
  other._is_deleted = nullptr;
}

template<typename T>
weakref<T>::~weakref()
{
  class_invariant();

  if(this->_is_deleted)
    this->_is_deleted->releaseReference();
}

template<typename T>
weakref& weakref<T>::operator=(const weakref<T>& other)
{
  class_invariant();

  if(this->_is_deleted)
    this->_is_deleted->releaseReference();

  this->_ptr = other._ptr;
  this->_is_deleted = other._is_deleted;

  if(this->_is_deleted)
    this->_is_deleted->addReference();
}

template<typename T>
weakref& weakref<T>::operator=(weakref<T>&& other)
{
  class_invariant();

  std::swap(other._ptr, this->_ptr);
  std::swap(other._is_deleted, this->_is_deleted);
}

template<typename T>
ref<T> weakref<T>::lock()
{
  class_invariant();

  if(!isNull())
  {
    _ptr->addReference();

    // Thread safety: The reference may be decreased by another thread before increasing it here, recheck
    if(!_is_deleted->Get())
    {
      return ref<T>(_ptr);
    }
  }

  return ref<T>();
}

template<typename T>
bool weakref<T>::isNull()
{
  class_invariant();
  return _is_deleted==nullptr || _is_deleted->Get();
}

void weakref<T>::reset()
{
  weakref<T>(std::move(this));
}

} // namespace AngelScriptIntegration

#endif // ANGELSCRIPTINTEGRATION_REF_INL
