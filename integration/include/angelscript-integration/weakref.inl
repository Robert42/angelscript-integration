#ifndef ANGELSCRIPTINTEGRATION_WEAKREF_INL
#define ANGELSCRIPTINTEGRATION_WEAKREF_INL

#include "weakref.h"

namespace AngelScriptIntegration {


template<typename T>
inline void weakref<T>::class_invariant() const
{
  Q_ASSERT((_ptr==nullptr) == (_is_deleted==nullptr));
}

template<typename T>
weakref<T>::weakref()
  : _ptr(nullptr),
    _is_deleted(nullptr)
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
weakref<T>::weakref(const weakref<T>& other)
  : _ptr(other._ptr),
    _is_deleted(other._is_deleted)
{
  if(_is_deleted)
    _is_deleted->AddRef();

  class_invariant();
}

template<typename T>
weakref<T>::weakref(weakref<T>&& other)
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
    this->_is_deleted->Release();
}

template<typename T>
weakref<T>& weakref<T>::operator=(const ref<T>& ptr)
{
  weakref<T> temp(ptr);
  this->swap(temp);
  return *this;
}

template<typename T>
weakref<T>& weakref<T>::operator=(const weakref<T>& other)
{
  other.class_invariant();
  class_invariant();

  if(this->_is_deleted)
    this->_is_deleted->Release();

  this->_ptr = other._ptr;
  this->_is_deleted = other._is_deleted;

  if(this->_is_deleted)
    this->_is_deleted->AddRef();
}

template<typename T>
weakref<T>& weakref<T>::operator=(weakref<T>&& other)
{
  class_invariant();

  std::swap(other._ptr, this->_ptr);
  std::swap(other._is_deleted, this->_is_deleted);

  return *this;
}

template<typename T>
ref<T> weakref<T>::lock() const
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
bool weakref<T>::operator==(const weakref<T>& other) const
{
  return (this->isNull() && other.isNull()) || this->_ptr == other._ptr;
}

template<typename T>
bool weakref<T>::operator!=(const weakref<T>& other) const
{
  return !this->operator ==(other);
}

template<typename T>
bool weakref<T>::operator==(const ref<T>& other) const
{
  return this->operator ==(other.ptr());
}

template<typename T>
bool weakref<T>::operator!=(const ref<T>& other) const
{
  return !this->operator ==(other);
}

template<typename T>
bool weakref<T>::operator==(T* other) const
{
  return (this->isNull() && other==nullptr) || this->_ptr == other;
}

template<typename T>
bool weakref<T>::operator!=(T* other) const
{
  return !this->operator ==(other);
}

template<typename T>
bool weakref<T>::isNull() const
{
  class_invariant();
  return _is_deleted==nullptr || _is_deleted->Get();
}

template<typename T>
void weakref<T>::reset()
{
  this->swap(weakref<T>());
}

template<typename T>
void weakref<T>::swap(weakref<T>& other)
{
  *this = std::move(other);
}

} // namespace AngelScriptIntegration

#endif // ANGELSCRIPTINTEGRATION_WEAKREF_INL
