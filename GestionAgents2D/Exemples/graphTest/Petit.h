#ifndef _PETIT_H_
#define _PETIT_H_

#include <iostream>

#include "MAS.h"

#include "Poisson.h"
#include "AppliData.h"

using namespace std;

class Petit : public Poisson
{
  DEFCLASS(Petit)

  friend ostream& operator<<(ostream& os, const Petit& aP);

 public :

   // Allocateurs/Desallocateurs

            Petit(Poisson* precedent,AppliData* data);
            Petit(const Petit& aP);
            Petit& operator=(const Petit& aP);
   virtual ~Petit(void);

   virtual  void live(double dt);

   // Comparaisons

   friend  bool operator==(const Petit& aP1, const Petit& aP2);
   friend  bool operator!=(const Petit& aP1, const Petit& aP2);

   // Inspecteurs/modificateurs

   virtual void onKeyPress(const char * key);

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const Petit& aP) const;

 protected :

             // ###

 private :
             Poisson* _precedent;

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const Petit& aP);
   void _destroy(void);

};

#endif // _PETIT_H_
