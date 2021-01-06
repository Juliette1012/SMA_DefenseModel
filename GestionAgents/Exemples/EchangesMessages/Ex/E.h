#ifndef _E_H_
#define _E_H_

#include <iostream>

#include "MAS.h"

using namespace std;

class E : public Agent
{
  DEFCLASS(E)

  friend ostream& operator<<(ostream& os, const E& anE);

 public :

   // Allocateurs/Desallocateurs

            E(int e);
            E(const E& anE);
            E& operator=(const E& anE);
   virtual ~E(void);

   virtual  void live(double dt);

   // Comparaisons

   friend  bool operator==(const E& anE1, const E& anE2);
   friend  bool operator!=(const E& anE1, const E& anE2);

   // Inspecteurs/modificateurs

           void setE(int e);
           int  getE(void) const;

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const E& anE) const;

 protected :

      // Attribut protege

          int _cycle;

 private :

      // Attribut private

          int    _e;

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const E& anE);
   void _destroy(void);

};

#endif // _E_H_
