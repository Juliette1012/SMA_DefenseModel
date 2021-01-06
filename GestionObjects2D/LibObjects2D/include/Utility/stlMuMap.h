#ifndef STLMUMAP_H
#define STLMUMAP_H

#include "Utility/stlUtil.h"

#ifndef __MSDOS__
#include <multimap>
#else
#include <map>
#endif

//--------------------------------------------------------------------------//
// class StlMultiMap                                                        //
//--------------------------------------------------------------------------//

#ifndef __MSDOS__
template <class Key,class T,class Comp=StlLess<Key> >
class StlMultiMap : public multimap<Key,T,Comp>
{
protected:
  typedef multimap<Key,T,Comp> stl_type;
#else // Microsoft STL is too different from original STL to be fully used
template <class Key,class T,class Comp=StlLess<Key> >
class StlMultiMap : public std::multimap<Key,T,Comp>
{
protected:
  typedef std::multimap<Key,T,Comp> stl_type;
#endif // __MSDOS__
public:
  inline StlMultiMap(void)
   : stl_type() {}
  inline StlMultiMap(const Comp & comp)
   : stl_type(comp) {}
#ifdef __STL_MEMBER_TEMPLATES
  template <class InputIterator>
  inline StlMultiMap(InputIterator first,InputIterator last)
   : stl_type(first,last) {}
  template <class InputIterator>
  inline StlMultiMap(InputIterator first,InputIterator last,const Comp & comp)
   : stl_type(first,last,comp) {}
#else
  inline StlMultiMap(const stl_type::value_type * first,
                     const stl_type::value_type * last)
   : stl_type(first,last) {}
  inline StlMultiMap(const stl_type::value_type * first,
                     const stl_type::value_type * last,
                     const Comp & comp)
   : stl_type(first,last,comp) {}
  inline StlMultiMap(const_iterator first,const_iterator last)
   : stl_type(first,last) {}
  inline StlMultiMap(const_iterator first,const_iterator last,
                     const Comp & comp)
   : stl_type(first,last,comp) {}
#endif // __STL_MEMBER_TEMPLATES
  inline StlMultiMap(const stl_type & m)
   : stl_type(m) {}
  inline virtual ~StlMultiMap(void) {}
  inline StlMultiMap<Key,T,Comp> & operator=(const stl_type & m)
    {
    stl_type::operator=(m);
    return(*this);
    }
};

#endif // STLMUMAP_H

