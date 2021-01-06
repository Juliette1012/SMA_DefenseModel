#ifndef _TOTO_H_
#define _TOTO_H_

#include <iostream>

#include "MAS.h"

#include "Agent.h"

using namespace std;

class Toto : public Agent
{
  DEFCLASS(Toto)

   friend ostream& operator<<(ostream& os, const Toto& aT);

 public :

   // Allocateurs/Desallocateurs

            Toto( /* ### */ );
            Toto(const Toto& aT);
            Toto& operator=(const Toto& aT);
   virtual ~Toto(void);

   virtual  void live(double dt);

   // Comparaisons

   friend  bool operator==(const Toto& aT1, const Toto& aT2);
   friend  bool operator!=(const Toto& aT1, const Toto& aT2);

   // Inspecteurs/modificateurs

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const Toto& aT) const;

 protected :

             // ###

 private :

             // ###

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const Toto& aT);
   void _destroy(void);

};

#endif // _TOTO_H_
