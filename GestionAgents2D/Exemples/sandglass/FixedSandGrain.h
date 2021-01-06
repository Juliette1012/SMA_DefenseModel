#ifndef _FIXEDSANDGRAIN_H_
#define _FIXEDSANDGRAIN_H_

#include <iostream>

#include "MAS.h"
#include "SandGrain.h"

using namespace std;

class FixedSandGrain : public SandGrain
{
  DEFCLASS(FixedSandGrain)

  friend ostream& operator<<(ostream& os, const FixedSandGrain& aF);

 public :

   // Allocateurs/Desallocateurs

            FixedSandGrain(void);
            FixedSandGrain(const FixedSandGrain& aF);
            FixedSandGrain& operator=(const FixedSandGrain& aF);
   virtual ~FixedSandGrain(void);

   virtual  void live(double dt);

   // Comparaisons

   friend  bool operator==(const FixedSandGrain& aF1, const FixedSandGrain& aF2);
   friend  bool operator!=(const FixedSandGrain& aF1, const FixedSandGrain& aF2);

   // Inspecteurs/modificateurs

   virtual void onKeyPress(const char * key);

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const FixedSandGrain& aF) const;

 protected :

 private :

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const FixedSandGrain& aF);
   void _destroy(void);

};

#endif // _FIXEDSANDGRAIN_H_
