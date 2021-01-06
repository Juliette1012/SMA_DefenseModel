#ifndef STLMAP_H
#define STLMAP_H

#include "Utility/stlUtil.h"

#ifndef __MSDOS__
#include <map>
#else
#include <map>
#endif

//--------------------------------------------------------------------------//
// class StlMap                                                             //
//--------------------------------------------------------------------------//

#ifndef __MSDOS__
template <class Key,class T,class Comp=StlLess<Key> >
class StlMap : public map<Key,T,Comp>
{
protected:
  typedef map<Key,T,Comp> stl_type;
#else // Microsoft STL is too different from original STL to be fully used
template <class Key,class T,class Comp=StlLess<Key> >
class StlMap : public std::map<Key,T,Comp>
{
protected:
  typedef std::map<Key,T,Comp> stl_type;
#endif // __MSDOS__
public:
  inline StlMap(void)
   : stl_type() {}
  inline StlMap(const Comp & comp)
   : stl_type(comp) {}
// #ifdef __STL_MEMBER_TEMPLATES
#if 1
  template <class InputIterator>
  inline StlMap(InputIterator first,InputIterator last)
   : stl_type(first,last) {}
  template <class InputIterator>
  inline StlMap(InputIterator first,InputIterator last,const Comp & comp)
   : stl_type(first,last,comp) {}
#else
  inline StlMap(const stl_type::value_type * first,
                const stl_type::value_type * last)
   : stl_type(first,last) {}
  inline StlMap(const stl_type::value_type * first,
                const stl_type::value_type * last,
                const Comp & comp)
   : stl_type(first,last,comp) {}
  inline StlMap(const_iterator first,const_iterator last)
   : stl_type(first,last) {}
  inline StlMap(const_iterator first,const_iterator last,const Comp & comp)
   : stl_type(first,last,comp) {}
#endif // __STL_MEMBER_TEMPLATES
  inline StlMap(const stl_type & m)
   : stl_type(m) {}
  inline virtual ~StlMap(void) {}
  inline StlMap<Key,T,Comp> & operator=(const stl_type & m)
    {
    stl_type::operator=(m);
    return(*this);
    }
};

#endif // STLMAP_H

