#ifndef STRINGS_H
#define STRINGS_H

#include <iostream>
#include <stdio.h>

#include "Utility/smplVect.h"
#include "Utility/stlVect.h"
#include "Utility/stlList.h"

//--------------------------------------------------------------------------//
// class Strings                                                            //
//--------------------------------------------------------------------------//

class Strings : protected SimpleVector<char>
{
public:
// Allocators
  inline Strings(void);
  inline Strings(const Strings & str);
  inline Strings(char c,size_t n=1);
  inline Strings(const char * str);
  inline Strings(char * str);
  inline Strings(const unsigned char * str);
  inline Strings(unsigned char * str);
  inline Strings(void * p);
  inline Strings(int i);
  inline Strings(unsigned int i);
  inline Strings(short s);
  inline Strings(unsigned short s);
  inline Strings(long l);
  inline Strings(unsigned long l);
  inline Strings(float f,bool showReal=false);
  inline Strings(double d,bool showReal=false);
  inline virtual ~Strings(void);
  inline void * operator new(size_t size);
  inline void * operator new(size_t size,void * block);
  inline void operator delete(void * block,size_t size);
// Inspectors
  inline size_t len(void) const;
  inline bool empty(void) const;
  inline operator const char *(void) const;
  inline char operator[](int n) const;
  Strings subString(size_t start,size_t length) const;
  int lookUp(const Strings & str) const;
  Strings basename(void) const;
  Strings dirname(void) const;
  Strings extension(void) const;
// Comparisons
  inline friend bool operator==(const Strings & str1,const Strings & str2);
  inline friend bool operator!=(const Strings & str1,const Strings & str2);
  inline friend bool operator<(const Strings & str1,const Strings & str2);
  inline friend bool operator<=(const Strings & str1,const Strings & str2);
  inline friend bool operator>=(const Strings & str1,const Strings & str2);
  inline friend bool operator>(const Strings & str1,const Strings & str2);
// Input/output
  friend ostream & operator<<(ostream & stream,const Strings & str);
  Strings dump(void) const;
  void dump(ostream & stream) const;
  friend istream & operator>>(istream & stream,Strings & str);
// Modifiers
  inline void raz(void);
  inline char & operator[](int n);
  inline Strings & operator=(const char * str);
  inline Strings & operator=(const Strings & str);
  inline Strings & operator+=(char c);
  inline Strings & operator+=(const Strings & str);
  inline Strings & operator+=(const char * str);
  inline friend Strings operator+(const Strings & str1,const Strings & str2);
  inline friend Strings operator+(const Strings & str1,const char * str2);
  inline friend Strings operator+(const char * str1,const Strings & str2);
  int subst(const Strings & str1,const Strings & str2);
  int substAll(const Strings & str1,const Strings & str2);
  void toLower(void);
  void toUpper(void);
  bool toLower(size_t pos);
  bool toUpper(size_t pos);
};

typedef StlVector<Strings> StringsVect;
typedef StlList<Strings> StringsList;

#include "Utility/strings.Ci"

#endif // STRINGS_H

