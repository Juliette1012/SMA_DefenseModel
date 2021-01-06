#ifndef _C_H_
#define _C_H_

#include <iostream>

#include "MAS.h"

using namespace std;

class C : public Agent
{
  DEFCLASS(C)

  friend ostream& operator<<(ostream& os, const C& aC);

 public :

   // Allocateurs/Desallocateurs

            C(void);
            C(const C& aC);
            C& operator=(const C& aC);
   virtual ~C(void);

   virtual  void live(double dt);

   // Comparaisons

   friend  bool operator==(const C& aC1, const C& aC2);
   friend  bool operator!=(const C& aC1, const C& aC2);

   // Inspecteurs/modificateurs

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const C& aC) const;

 protected :

             // ###

 private :

             // ###

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const C& aC);
   void _destroy(void);

};

#endif // _C_H_
