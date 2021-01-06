#ifndef STLSET_H
#define STLSET_H

#include "Utility/stlUtil.h"

#ifndef __MSDOS__
#include <set>
#else
#include <set>
#endif

//--------------------------------------------------------------------------//
// class StlSet                                                             //
//--------------------------------------------------------------------------//

#ifndef __MSDOS__
template <class Key,class Comp=StlLess<Key> >
class StlSet : public set<Key,Comp>
{
protected:
  typedef set<Key,Comp> stl_type;
#else // Microsoft STL is too different from original STL to be fully used
template <class Key,class Comp=StlLess<Key> >
class StlSet : public std::set<Key,Comp>
{
protected:
  typedef std::set<Key,Comp> stl_type;
#endif // __MSDOS__
public:
  inline StlSet(void)
   : stl_type() {}
  inline StlSet(const Comp & comp)
   : stl_type(comp) {}
// #ifdef __STL_MEMBER_TEMPLATES
#if 1
  template <class InputIterator>
  inline StlSet(InputIterator first,InputIterator last)
   : stl_type(first,last) {}
  template <class InputIterator>
  inline StlSet(InputIterator first,InputIterator last,const Comp & comp)
   : stl_type(first,last,comp) {}
#else
  inline StlSet(const stl_type::value_type * first,
                const stl_type::value_type * last)
   : stl_type(first,last) {}
  inline StlSet(const stl_type::value_type * first,
                const stl_type::value_type * last,
                const Comp & comp)
   : stl_type(first,last,comp) {}
  inline StlSet(const_iterator first,const_iterator last)
   : stl_type(first,last) {}
  inline StlSet(const_iterator first,const_iterator last,const Comp & comp)
   : stl_type(first,last,comp) {}
#endif // __STL_MEMBER_TEMPLATES
  inline StlSet(const stl_type & s)
   : stl_type(s) {}
  inline virtual ~StlSet(void) {}
  inline StlSet<Key,Comp> & operator=(const stl_type & s)
    {
    stl_type::operator=(s);
    return(*this);
    }
};

#endif // STLSET_H

