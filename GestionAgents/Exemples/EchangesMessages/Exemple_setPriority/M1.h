#ifndef _M1_H_
#define _M1_H_

#include <iostream>

#include "MAS.h"

#include "Message.h"

using namespace std;

class M1 : public Message
{
  DEFCLASS(M1)

  friend ostream& operator<<(ostream& os, const M1& aM);

 public :

   // Allocateurs/Desallocateurs

            M1(size_t v);
            M1(const M1& aM);
            M1& operator=(const M1& aM);
   virtual ~M1(void);

   // Comparaisons

   friend  bool operator==(const M1& aM1, const M1& aM2);
   friend  bool operator!=(const M1& aM1, const M1& aM2);

   // Inspecteurs/modificateurs

           size_t getV(void);
           void   setV(size_t v);

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const M1& aM) const;

 protected :

             // ###

 private :

             size_t _v;

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const M1& aM);
   void _destroy(void);

};

#endif // _M1_H_
