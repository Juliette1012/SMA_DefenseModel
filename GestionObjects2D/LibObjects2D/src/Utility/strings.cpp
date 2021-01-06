#include "Utility/strings.h"

//--------------------------------------------------------------------------//
// class Strings                                                            //
//--------------------------------------------------------------------------//

//-------- Allocators ------------------------------------------------------//
// inline Strings::Strings(void)

// inline Strings::Strings(const Strings & str)

// inline Strings::Strings(char c,size_t n)

// inline Strings::Strings(const char * str)

// inline Strings::Strings(char * str)

// inline Strings::Strings(const unsigned char * str)

// inline Strings::Strings(unsigned char * str)

// inline Strings::Strings(void * p)
 
// inline Strings::Strings(int i)
 
// inline Strings::Strings(unsigned int i)
 
// inline Strings::Strings(short s)
 
// inline Strings::Strings(unsigned short s)

// inline Strings::Strings(long l)
 
// inline Strings::Strings(unsigned long l)
 
// inline Strings::Strings(float f,bool showReal)
 
// inline Strings::Strings(double d,bool showReal)

// inline Strings::~Strings(void)

// inline void * Strings::operator new(size_t size)

// inline void * Strings::operator new(size_t size,void * block)

// inline void Strings::operator delete(void * block,size_t size)

//-------- Inspectors ------------------------------------------------------//
// inline size_t Strings::len(void) const

// inline bool Strings::empty(void) const

// inline Strings::operator const char *(void) const

// inline char Strings::operator[](int n) const

Strings Strings::subString(size_t start,size_t length) const
{
if(start>len()) start=len();
if(start+length>len()) length=len()-start;
Strings str('\0',length);
str.affect(_memory+start,length);
str.pushBack('\0');
return(str);
}

int Strings::lookUp(const Strings & str) const
{
if(str.len())
  {
  for(size_t i=0;i<len();i++)
    {
    if(!::strncmp(_memory+i,str._memory,str.len()))
      return(i);
    }
  }
return(-1);
}

Strings Strings::basename(void) const
{
const char separ='/';
Strings str(*this);
#ifdef __MSDOS__
for(char * ptr=str._memory;*ptr;ptr++)
  {
  if(*ptr=='\\') *ptr=separ;
  }
#endif
char * limit=::strrchr(str._memory,separ);
if(limit==str._memory+str.len()-1) // last char is separ
  {
  str.popBack();
  str.accessBack()='\0';
  limit=::strrchr(str._memory,separ);
  }
if(limit) limit++;
else limit=str._memory;
return(Strings(limit));
}

Strings Strings::dirname(void) const
{
const char separ='/';
Strings str(*this);
#ifdef __MSDOS__
for(char * ptr=str._memory;*ptr;ptr++)
  {
  if(*ptr=='\\') *ptr=separ;
  }
#endif
char * limit=::strrchr(str._memory,separ);
if(limit==str._memory+str.len()-1) // last char is separ
  {
  str.popBack();
  str.accessBack()='\0';
  limit=::strrchr(str._memory,separ);
  }
if(limit) limit++;
else limit=str._memory;
return(str.subString(0,limit-str._memory));
}

Strings Strings::extension(void) const
{
char * limit=::strrchr(_memory,'.');
if(limit) return(Strings(limit));
else return(Strings(""));
}

//-------- Comparisons -----------------------------------------------------//
// inline bool operator==(const Strings & str1,const Strings & str)

// inline bool operator!=(const Strings & str1,const Strings & str2)

// inline bool operator<(const Strings & str1,const Strings & str2)

// inline bool operator<=(const Strings & str1,const Strings & str2)

// inline bool operator>=(const Strings & str1,const Strings & str2)

// inline bool operator>(const Strings & str1,const Strings & str2)

//-------- Input/Output ----------------------------------------------------//
ostream & operator<<(ostream & stream,const Strings & str)
{
return(stream << str._memory);
}

Strings Strings::dump(void) const
{
Strings str="\"";
for(size_t i=0;i<len();i++)
  {
  switch(_memory[i])
    {
    case '\a': str+="\\a";  break;
    case '\b': str+="\\b";  break;
    case '\f': str+="\\f";  break;
    case '\n': str+="\\n";  break;
    case '\t': str+="\\t";  break;
    case '\v': str+="\\v";  break;
    case '\\': str+="\\\\"; break;
    case '\"': str+="\\\""; break;
    default: str+=_memory[i];
    }
  }
str+="\"";
return(str);
}

void Strings::dump(ostream & stream) const
{
stream << dump();
}

istream & operator>>(istream & stream,Strings & str)
{
char line[0x100];
stream.getline(line,0x100,'\n');
str=line;
return(stream);
}

//-------- Modifiers -------------------------------------------------------//
// inline void Strings::raz(void)

// inline char& Strings::operator[](int n)

// inline Strings & Strings::operator=(const char * str)

// inline Strings & Strings::operator=(const Strings & str)

// inline Strings & Strings::operator+=(char c)

// inline Strings & Strings::operator+=(const Strings & str)

// inline Strings & Strings::operator+=(const char * str)

// inline Strings operator+(const Strings & str1,const Strings & str2)

// inline Strings operator+(const Strings & str1,const char * str2)

// inline Strings operator+(const char * str1,const Strings & str2)

int Strings::subst(const Strings & str1, const Strings & str2)
{
int pos=lookUp(str1);
if(pos>=0)
  {
  size_t length=len()+str2.len()-str1.len();
  Strings tmp('\0',length);
  tmp.affect(_memory,pos);
  tmp.add(str2._memory,str2.len());
  tmp.add(_memory+pos+str1.len(),len()+1-pos-str1.len());
  *this=tmp;
  }
return(pos);
}

int Strings::substAll(const Strings & str1, const Strings & str2)
{
int nb=0;
if(str1.len())
  {
  for(size_t pos=0;pos<len();pos++)
    {
    if(!::strncmp(_memory+pos,str1._memory,str1.len()))
      {
      size_t length=len()+str2.len()-str1.len();
      Strings tmp('\0',length);
      tmp.affect(_memory,pos);
      tmp.add(str2._memory,str2.len());
      tmp.add(_memory+pos+str1.len(),len()+1-pos-str1.len());
      *this=tmp;
      pos+=str2.len()-1;
      nb++;
      }
    }
  }
return(nb);
}

void Strings::toLower(void)
{
char offset='a'-'A';
for(size_t pos=len();pos--;)
  {
  if((_memory[pos]>='A')&&(_memory[pos]<='Z'))
    _memory[pos]+=offset;
  }
}

void Strings::toUpper(void)
{
char offset='a'-'A';
for(size_t pos=len();pos--;)
  {
  if((_memory[pos]>='a')&&(_memory[pos]<='z'))
    _memory[pos]-=offset;
  }
}

bool Strings::toLower(size_t pos)
{
char offset='a'-'A';
if((pos<len())&&(_memory[pos]>='A')&&(_memory[pos]<='Z'))
  {
  _memory[pos]+=offset;
  return(true);
  }
return(false);
}

bool Strings::toUpper(size_t pos)
{
char offset='a'-'A';
if((pos<len())&&(_memory[pos]>='a')&&(_memory[pos]<='z'))
  {
  _memory[pos]-=offset;
  return(true);
  }
return(false);
}

