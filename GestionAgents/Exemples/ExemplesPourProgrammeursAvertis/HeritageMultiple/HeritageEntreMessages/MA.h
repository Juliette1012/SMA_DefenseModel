#ifndef _MA_H_
#define _MA_H_

#include <iostream>

#include "MAS.h"

using namespace std;

class MA : public Message
{
  DEFCLASS(MA)

  friend ostream& operator<<(ostream& os, const MA& aM);

 public :

   // Allocateurs/Desallocateurs

            MA( /* ### */ );
            MA(const MA& aM);
            MA& operator=(const MA& aM);
   virtual ~MA(void);

   // Comparaisons

   friend  bool operator==(const MA& aM1, const MA& aM2);
   friend  bool operator!=(const MA& aM1, const MA& aM2);

   // Inspecteurs/modificateurs

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const MA& aM) const;

 protected :

             // ###

 private :

             // ###

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const MA& aM);
   void _destroy(void);

};

#endif // _MA_H_
