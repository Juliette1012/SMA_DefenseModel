#ifndef STLMUSET_H
#define STLMUSET_H

#include "Utility/stlUtil.h"

#ifndef __MSDOS__
#include <multiset>
#else
#include <set>
#endif

//--------------------------------------------------------------------------//
// class StlMultiSet                                                        //
//--------------------------------------------------------------------------//

#ifndef __MSDOS__
template <class Key,class Comp=StlLess<Key> >
class StlMultiSet : public multiset<Key,Comp>
{
protected:
  typedef multiset<Key,Comp> stl_type;
#else // Microsoft STL is too different from original STL to be fully used
template <class Key,class Comp=StlLess<Key> >
class StlMultiSet : public std::multiset<Key,Comp>
{
protected:
  typedef std::multiset<Key,Comp> stl_type;
#endif // __MSDOS__
public:
  inline StlMultiSet(void)
   : stl_type() {}
  inline StlMultiSet(const Comp & comp)
   : stl_type(comp) {}
#ifdef __STL_MEMBER_TEMPLATES
  template <class InputIterator>
  inline StlMultiSet(InputIterator first,InputIterator last)
   : stl_type(first,last) {}
  template <class InputIterator>
  inline StlMultiSet(InputIterator first,InputIterator last,const Comp & comp)
   : stl_type(first,last,comp) {}
#else
  inline StlMultiSet(const stl_type::value_type * first,
                     const stl_type::value_type * last)
   : stl_type(first,last) {}
  inline StlMultiSet(const stl_type::value_type * first,
                     const stl_type::value_type * last,
                     const Comp & comp)
   : stl_type(first,last,comp) {}
  inline StlMultiSet(const_iterator first,const_iterator last)
   : stl_type(first,last) {}
  inline StlMultiSet(const_iterator first,const_iterator last,
                     const Comp & comp)
   : stl_type(first,last,comp) {}
#endif // __STL_MEMBER_TEMPLATES
  inline StlMultiSet(const stl_type & s)
   : stl_type(s) {}
  inline virtual ~StlMultiSet(void) {}
  inline StlMultiSet<Key,Comp> & operator=(const stl_type & s)
    {
    stl_type::operator=(s);
    return(*this);
    }
};

#endif // STLMUSET_H

