#ifndef _M2_H_
#define _M2_H_

#include <iostream>

#include "MAS.h"

#include "Message.h"

using namespace std;

class M2 : public Message
{
  DEFCLASS(M2)

  friend ostream& operator<<(ostream& os, const M2& aM);

 public :

   // Allocateurs/Desallocateurs

            M2(size_t v);
            M2(const M2& aM);
            M2& operator=(const M2& aM);
   virtual ~M2(void);

   // Comparaisons

   friend  bool operator==(const M2& aM1, const M2& aM2);
   friend  bool operator!=(const M2& aM1, const M2& aM2);

   // Inspecteurs/modificateurs

           size_t getV(void);
           void   setV(size_t v);

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const M2& aM) const;

 protected :

             // ###

 private :

             size_t _v;

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const M2& aM);
   void _destroy(void);

};

#endif // _M2_H_
