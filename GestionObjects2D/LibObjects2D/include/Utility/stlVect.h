#ifndef STLVECT_H
#define STLVECT_H

#include "Utility/stlUtil.h"

#ifndef __MSDOS__
#include <vector>
#else
#include <vector>
#endif

//--------------------------------------------------------------------------//
// class StlVector                                                          //
//--------------------------------------------------------------------------//

#ifndef __MSDOS__
template <class T>
class StlVector : public vector<T>
{
protected:
  typedef vector<T> stl_type;
#else // Microsoft STL is too different from original STL to be fully used
template <class T>
class StlVector : public std::vector<T>
{
protected:
  typedef std::vector<T> stl_type;
#endif // __MSDOS__
public:
  inline StlVector(void)
   : stl_type() {}
  inline StlVector(typename stl_type::size_type n, const T & value)
   : stl_type(n,value) {}
  inline StlVector(typename stl_type::size_type n)
   : stl_type(n) {}
  inline StlVector(const stl_type & v)
   : stl_type(v) {}
// #ifdef __STL_MEMBER_TEMPLATES
#if 1
  template <class InputIterator>
  inline StlVector(InputIterator first,InputIterator last)
   : stl_type(first,last) {}
#else
  inline StlVector(const_iterator first,const_iterator last)
   : stl_type(first,last) {}
# endif // __STL_MEMBER_TEMPLATES
  inline virtual ~StlVector(void) {}
  inline StlVector<T> & operator=(const stl_type & v)
    {
    stl_type::operator=(v);
    return(*this);
    }
};

#endif // STLVECT_H

