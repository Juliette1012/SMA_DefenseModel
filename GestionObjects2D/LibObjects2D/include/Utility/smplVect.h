#ifndef SMPLVECT_H
#define SMPLVECT_H

#include <string.h>

// !!! WARNING !!!
//
// This vector must only be used for very simple types (int, char or pointer)
// --> data are passed by copy and not by reference !

//--------------------------------------------------------------------------//
// class SimpleVector                                                       //
//--------------------------------------------------------------------------//

template <class T>
class SimpleVector
{
public:
// Allocators
  inline SimpleVector(size_t size=0);
  inline SimpleVector(T data,size_t size=1);
  inline SimpleVector(const SimpleVector<T> & v);
  inline SimpleVector(const T * v,size_t size);
  inline virtual ~SimpleVector(void);
// Inspectors
  inline size_t getSize(void) const;
  inline size_t getCapacity(void) const;
  inline T operator[](size_t pos) const;
  inline T getBack(void) const;
  inline T getFront(void) const;
// Modifiers
  inline void raz(void);
  inline void swap(SimpleVector<T> & other);
  inline void resize(size_t capacity);
  inline void resizeIfNeeded(size_t capacity);
  inline T & operator[](size_t pos);
  inline T & accessBack(void);
  inline T & accessFront(void);
  inline void insert(size_t pos,T data);
  inline void pushBack(T data);
  inline void pushFront(T data);
  inline void erase(size_t pos);
  inline T readErase(size_t pos);
  inline void popBack(void);
  inline T readPopBack(void);
  inline void popFront(void);
  inline T readPopFront(void);
  inline SimpleVector<T> & operator=(const SimpleVector<T> & v);
  inline SimpleVector<T> & operator+=(const SimpleVector<T> & v);
  inline SimpleVector<T> & affect(const T * v,size_t size);
  inline SimpleVector<T> & add(const T * v,size_t size);
protected:
// Attributes
  size_t _capacity;
  size_t _size;
  T * _memory;
};

#include "Utility/smplVect.Ci"

#endif // SMPLVECT_H
