#ifndef _SANDGLASS_H_
#define _SANDGLASS_H_

#include <iostream>

#include "MAS.h"
#include "Agent2D.h"

using namespace std;

class SandGlass : public Agent2D
{
  DEFCLASS(SandGlass)

  friend ostream& operator<<(ostream& os, const SandGlass& aS);

 public :

   // Allocateurs/Desallocateurs

            SandGlass(int side,int nbGrain);
            SandGlass(const SandGlass& aS);
            SandGlass& operator=(const SandGlass& aS);
   virtual ~SandGlass(void);

   virtual  void live(double dt);

   // Comparaisons

   friend  bool operator==(const SandGlass& aS1, const SandGlass& aS2);
   friend  bool operator!=(const SandGlass& aS1, const SandGlass& aS2);

   // Inspecteurs/modificateurs

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const SandGlass& aS) const;

 protected :

 private :

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const SandGlass& aS);
   void _destroy(void);

};

#endif // _SANDGLASS_H_
