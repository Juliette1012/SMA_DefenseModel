#ifndef _POISSON_H_
#define _POISSON_H_

#include <iostream>

#include "MAS.h"
#include "Agent2D.h"

#include "AppliData.h"

using namespace std;

class Poisson : public Agent2D
{
  DEFCLASS(Poisson)

  friend ostream& operator<<(ostream& os, const Poisson& aP);

 public :

   // Allocateurs/Desallocateurs

            Poisson(AppliData* data);
            Poisson(const Poisson& aP);
            Poisson& operator=(const Poisson& aP);
   virtual ~Poisson(void);

   virtual  void live(double dt);

   // Comparaisons

   friend  bool operator==(const Poisson& aP1, const Poisson& aP2);
   friend  bool operator!=(const Poisson& aP1, const Poisson& aP2);

   // Inspecteurs/modificateurs

   virtual void onKeyPress(const char * key);

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const Poisson& aP) const;

 protected :

           AppliData* _data;

 private :

             // ###

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const Poisson& aP);
   void _destroy(void);

};

#endif // _POISSON_H_
