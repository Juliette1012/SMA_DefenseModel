#ifndef STLUTIL_H
#define STLUTIL_H

#ifndef __MSDOS__
#include <algorithm>
#include <functional>
#include <utility>
using namespace std;
#else
#pragma warning( disable : 4786 )
#pragma warning( disable : 4291 )
#include <utility>
#include <functional>
#include <algorithm>
#endif

// #ifdef __STL_USE_STD_ALLOCATORS
// #  define STL_ALLOC(T) TypedAllocator<T>
// #else
// #  define STL_ALLOC(T) BlockAllocator
// #endif

//--------------------------------------------------------------------------//
// function stlForEach                                                      //
//--------------------------------------------------------------------------//

template <class InputIterator,class Function>
inline
InputIterator stlForEach(InputIterator first,InputIterator last,Function f)
{
#ifndef __MSDOS__
return(for_each(first,last,f));
#else
return(std::for_each(first,last,f));
#endif // MSDOS
}

//--------------------------------------------------------------------------//
// function stlFind                                                         //
//--------------------------------------------------------------------------//

template <class InputIterator,class T>
inline
InputIterator stlFind(InputIterator first,InputIterator last,const T & value)
{
#ifndef __MSDOS__
return(find(first,last,value));
#else
return(std::find(first,last,value));
#endif // MSDOS
}

//--------------------------------------------------------------------------//
// class StlPair                                                            //
//--------------------------------------------------------------------------//

#ifndef __MSDOS__
template <class T1,class T2>
class StlPair : public pair<T1,T2>
{
protected:
  typedef pair<T1,T2> stl_type;
#else
template <class T1,class T2>
class StlPair : public std::pair<T1,T2>
{
protected:
  typedef std::pair<T1,T2> stl_type;
#endif // __MSDOS__
public:
  inline StlPair(void) : stl_type() {}
  inline StlPair(const T1 & a,const T2 & b) : stl_type(a,b) {}
  inline StlPair(const stl_type & p) : stl_type(p) {}
#ifdef __STL_MEMBER_TEMPLATES
  template <class U1,class U2>
  inline StlPair(const StlPair<U1,U2> & p) : stl_type(p) {}
#else
  inline StlPair(const StlPair<T1,T2> & p) : stl_type(p) {}
#endif
  inline StlPair<T1,T2> & operator=(const StlPair<T1,T2> & p)
    {
    stl_type::operator=(p);
    return(*this);
    }
  inline StlPair<T1,T2> & operator=(const stl_type & p)
    {
    stl_type::operator=(p);
    return(*this);
    }
};

//--------------------------------------------------------------------------//
// class StlLess                                                            //
//--------------------------------------------------------------------------//

template <class T>
#ifndef __MSDOS__
class StlLess : public less<T> {};
#else
class StlLess : public std::less<T> {};
#endif // __MSDOS__

//--------------------------------------------------------------------------//
// class StlPtrLess                                                         //
//--------------------------------------------------------------------------//

// comparisons through pointers

#ifndef __MSDOS__
template <class T>
struct StlPtrLess : binary_function<T*,T*,bool>
#else
template <class T>
struct StlPtrLess : std::binary_function<T*,T*,bool>
#endif // __MSDOS__
{
inline bool operator()(const T * x,const T * y) const
  {return(*x<*y);}
};

#endif // STLUTIL_H

