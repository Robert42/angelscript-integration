#ifndef ANGELSCRIPTINTEGRATION_REF_INL
#define ANGELSCRIPTINTEGRATION_REF_INL

#include "ref.h"

namespace AngelScriptIntegration {


template<typename T>
ref<T>::ref(T* ptr)
  : _ptr(ptr)
{
}

template<typename T>
ref<T>::ref(const ref<T>& other)
  : _ptr(other._ptr)
{
  if(_ptr)
    _ptr->addReference();
}

template<typename T>
ref<T>::ref(ref<T>&& other)
  : _ptr(other._ptr)
{
  other._ptr = nullptr;
}

template<typename T>
ref<T>::~ref()
{
  if(this->_ptr)
    this->_ptr->releaseReference();
}

template<typename T>
ref<T>& ref<T>::operator=(const ref<T>& other)
{
  if(this->_ptr)
    this->_ptr->releaseReference();

  this->_ptr = other._ptr;

  if(this->_ptr)
    this->_ptr->addReference();

  return *this;
}

template<typename T>
ref<T>& ref<T>::operator=(ref<T>&& other)
{
  std::swap(other._ptr, this->_ptr);
  return *this;
}

template<typename T>
T* ref<T>::addReference()
{
  if(_ptr)
    _ptr->addReference();
  return _ptr;
}

template<typename T>
T* ref<T>::ptr() const
{
  return _ptr;
}

template<typename T>
T* ref<T>::operator->() const
{
  return _ptr;
}

template<typename T>
bool ref<T>::operator==(const ref<T>& other) const
{
  return this->_ptr == other._ptr;
}

template<typename T>
bool ref<T>::operator!=(const ref<T>& other) const
{
  return this->_ptr != other._ptr;
}

template<typename T>
bool ref<T>::operator==(T* other) const
{
  return this->_ptr == other;
}

template<typename T>
bool ref<T>::operator!=(T* other) const
{
  return this->_ptr != other;
}

template<typename T>
bool ref<T>::isNull() const
{
  return _ptr==nullptr;
}

template<typename T>
void ref<T>::reset()
{
  this->swap(ref<T>());
}

template<typename T>
void ref<T>::swap(ref<T>& other)
{
  *this = std::move(other);
}


} // namespace AngelScriptIntegration

#endif // ANGELSCRIPTINTEGRATION_REF_INL
