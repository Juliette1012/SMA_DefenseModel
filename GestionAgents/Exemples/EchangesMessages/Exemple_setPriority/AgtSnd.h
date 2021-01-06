#ifndef _AGTSND_H_
#define _AGTSND_H_

#include <iostream>

#include "MAS.h"

#include "Agent.h"

using namespace std;

class AgtSnd : public Agent
{
  DEFCLASS(AgtSnd)

  friend ostream& operator<<(ostream& os, const AgtSnd& anA);

 public :

   // Allocateurs/Desallocateurs

            AgtSnd( /* ### */ );
            AgtSnd(const AgtSnd& anA);
            AgtSnd& operator=(const AgtSnd& anA);
   virtual ~AgtSnd(void);

   virtual  void live(double dt);

   // Comparaisons

   friend  bool operator==(const AgtSnd& anA1, const AgtSnd& anA2);
   friend  bool operator!=(const AgtSnd& anA1, const AgtSnd& anA2);

   // Inspecteurs/modificateurs

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const AgtSnd& anA) const;

 protected :

             // ###

 private :

             // ###

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const AgtSnd& anA);
   void _destroy(void);

};

#endif // _AGTSND_H_
