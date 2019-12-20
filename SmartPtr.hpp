/**************************************************************************/
/*!
  @file SmartPtr.hpp

  This library implements an smart pointer to use with diferent types
  autodestroys the pointer when the ptr direction is changed, when is
  called reset() or when is destroyed the object.


  Written by JPolanco.
*/
/**************************************************************************/
#ifndef SMART_PTR_H
#define SMART_PTR_H

#include <stdlib.h>

// Namespace that contains memory functions and objects
namespace memory
{
template <typename _Tptr>
// Class: Pointer
// The behaviour of the class is an property proxy for
// pointer interactions 
class Pointer
{
private:
// Internal pointer reference
  _Tptr *__ptr__;

public:
// [Constructor] Default constructor
  Pointer() : __ptr__(NULL) {}
// [Constructor] Gets and pointer and stores it
  Pointer(_Tptr *ptr) : __ptr__(ptr) {}
// [Operator] Sets a new ptr and deletes the last value
  Pointer<_Tptr>& operator=(_Tptr *_ptr);
// [Operator] Gets the ptr
  operator _Tptr *() const;
};

template <typename _Tptr>
// Class: SmartPointer
// The behaviour of the class is an property proxy for
// pointer interactions 
class SmartPointer
{
private:
// Internal proxy pointer
  Pointer<_Tptr> ptr;

public:
// [Constructor] Constructs the ptr with an ptr
  SmartPointer() : ptr(NULL) {}
// [Constructor] Constructs the ptr with an ptr
  SmartPointer(_Tptr *ptr) : ptr(ptr) {}
// [Getter] Gets the pointer to the value
  _Tptr *get() const;
// [Setter] Sets the value the type
  void set(_Tptr);
// [Operator] Sets an new ptr for the class
  SmartPointer<_Tptr>& operator=(SmartPointer &);
// [Operator] Sets an new ptr for the class
  SmartPointer<_Tptr>& operator=(const SmartPointer &ptr);
// [Operator] Sets an new ptr for the class
  SmartPointer<_Tptr>& operator=(_Tptr *ptr);
// [Operator] Sets an new ptr for the class
  SmartPointer<_Tptr>& operator=(const _Tptr *ptr);
// [Operator] Calls internal pointer operator
  _Tptr*operator->() const;
// [Public Method] Deletes actual pointer and sets NULL
  void reset();
// [Public Method] Checks if is null the pointer
  bool isNull();
};

template <typename _Tptr>
// Returns a new smart ptr of a type
// Needs that the _Tptr has a default constructor
// to instance a new _Tptr()
SmartPointer<_Tptr> make_ptr();
template <typename _Tptr>
SmartPointer<_Tptr> make_ptr(_Tptr);

/**************************************************************************/
/*
  Implementation of template functions
*/
/**************************************************************************/

template <typename _Tptr>
Pointer<_Tptr>&  Pointer<_Tptr>::operator=(_Tptr *_ptr)
{
  delete this->__ptr__;
  this->__ptr__ = static_cast<_Tptr *>(_ptr);
  return *this;
}

template <typename _Tptr>
Pointer<_Tptr>::operator _Tptr *() const
{
  return this->__ptr__;
}

template <typename _Tptr>
_Tptr *SmartPointer<_Tptr>::get() const {
  return ptr;
}

template <typename _Tptr>
void SmartPointer<_Tptr>::set(_Tptr val) {
  (*ptr) = val;
}

template <typename _Tptr>
SmartPointer<_Tptr>& SmartPointer<_Tptr>::operator=(SmartPointer &ptr) {
  this->ptr = ptr.get();
  return *this;
}

template <typename _Tptr>
SmartPointer<_Tptr>& SmartPointer<_Tptr>::operator=(const SmartPointer &ptr) {
  this->ptr = ptr.get();
  return *this;
}

template <typename _Tptr>
SmartPointer<_Tptr>& SmartPointer<_Tptr>::operator=(_Tptr *ptr) {
  this->ptr = ptr;
  return *this;
}

template <typename _Tptr>
SmartPointer<_Tptr>& SmartPointer<_Tptr>::operator=(const _Tptr *ptr) {
  this->ptr = ptr;
  return *this;
}

template <typename _Tptr>
void SmartPointer<_Tptr>::reset() {
  this->ptr = NULL;
}

template <typename _Tptr>
bool SmartPointer<_Tptr>::isNull() {
  return this->ptr == NULL;
}

template <typename _Tptr>
_Tptr* SmartPointer<_Tptr>::operator->() const {
  return this->ptr;
}

template <typename _Tptr>
SmartPointer<_Tptr> make_ptr()
{
  return SmartPointer<_Tptr>(new _Tptr());
}

template <typename _Tptr>
SmartPointer<_Tptr> make_ptr(_Tptr val) {
  return SmartPointer<_Tptr>(&val);
}

} // namespace memory

#endif // !SMART_PTR_H