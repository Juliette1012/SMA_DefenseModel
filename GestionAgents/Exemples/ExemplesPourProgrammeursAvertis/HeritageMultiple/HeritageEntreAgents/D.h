#ifndef _D_H_
#define _D_H_

#include <iostream>

#include "MAS.h"
#include "C.h"

using namespace std;

class D : public C
{
  DEFCLASS(D)

  friend ostream& operator<<(ostream& os, const D& aD);

 public :

   // Allocateurs/Desallocateurs

            D(void);
            D(const D& aD);
            D& operator=(const D& aD);
   virtual ~D(void);

   virtual  void live(double dt);

   // Comparaisons

   friend  bool operator==(const D& aD1, const D& aD2);
   friend  bool operator!=(const D& aD1, const D& aD2);

   // Inspecteurs/modificateurs

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const D& aD) const;

 protected :

             // ###

 private :

             // ###

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const D& aD);
   void _destroy(void);

};

#endif // _D_H_
