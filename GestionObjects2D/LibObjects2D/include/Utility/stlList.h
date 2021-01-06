#ifndef STLLIST_H
#define STLLIST_H

#include "Utility/stlUtil.h"

#ifndef __MSDOS__
#include <list>
#else
#include <list>
#endif

//--------------------------------------------------------------------------//
// class StlList                                                            //
//--------------------------------------------------------------------------//

#ifndef __MSDOS__
template <class T>
class StlList : public list<T>
{
protected:
  typedef list<T> stl_type;
#else // Microsoft STL is too different from original STL to be fully used
template <class T>
class StlList : public std::list<T>
{
protected:
  typedef std::list<T> stl_type;
#endif // __MSDOS__
public:
  inline StlList(void)
   : stl_type() {}
  inline StlList(typename stl_type::size_type n, const T & value)
   : stl_type(n,value) {}
  inline StlList(typename stl_type::size_type n)
   : stl_type(n) {}
// #ifdef __STL_MEMBER_TEMPLATES
#if 1
  template <class InputIterator>
  inline StlList(InputIterator first,InputIterator last)
   : stl_type(first,last) {}
#else
  inline StlList(const T * first,const T * last)
   : stl_type(first,last) {}
  inline StlList(const_iterator first,const_iterator last)
   : stl_type(first,last) {}
# endif // __STL_MEMBER_TEMPLATES
  inline StlList(const stl_type & l)
   : stl_type(l) {}
  inline virtual ~StlList(void) {}
  inline StlList<T> & operator=(const stl_type & l)
    {
    stl_type::operator=(l);
    return(*this);
    }
};

#endif // STLLIST_H

