#ifndef _SANDGRAIN_H_
#define _SANDGRAIN_H_

#define DT 0.02
#define GRAV 9.81
#define DIAM 0.1
#define TRANSFERT 0.8
#define RENDEMENT 0.4

#include <iostream>

#include "MAS.h"
#include "Agent2D.h"

using namespace std;

class SandGrain : public Agent2D
{
  DEFCLASS(SandGrain)

  friend ostream& operator<<(ostream& os, const SandGrain& aS);

 public :

   // Allocateurs/Desallocateurs

            SandGrain(void);
            SandGrain(const SandGrain& aS);
            SandGrain& operator=(const SandGrain& aS);
   virtual ~SandGrain(void);

   virtual  void live(double dt);

   // Comparaisons

   friend  bool operator==(const SandGrain& aS1, const SandGrain& aS2);
   friend  bool operator!=(const SandGrain& aS1, const SandGrain& aS2);

   // Inspecteurs/modificateurs

   virtual void onKeyPress(const char * key);

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const SandGrain& aS) const;

 protected :

             bool   _fixed;

 private :

             double _sx,_sy;
             double _g;
             int    _contact;

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const SandGrain& aS);
   void _destroy(void);

};

#endif // _SANDGRAIN_H_
