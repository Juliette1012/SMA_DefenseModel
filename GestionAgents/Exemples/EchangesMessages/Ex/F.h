#ifndef _F_H_
#define _F_H_

#include <iostream>

#include "MAS.h"
#include "E.h"

using namespace std;

class F : public E
{
  DEFCLASS(F)

  friend ostream& operator<<(ostream& os, const F& aF);

 public :

   // Allocateurs/Desallocateurs

            F(int e, int f);
            F(const F& aF);
            F& operator=(const F& aF);
   virtual ~F(void);

   virtual  void live(double dt);

   // Comparaisons

   friend  bool operator==(const F& aF1, const F& aF2);
   friend  bool operator!=(const F& aF1, const F& aF2);

   // Inspecteurs/modificateurs

           void setF(int f);
           int  getF(void) const;

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const F& aF) const;

 protected :

      // Pas d'attribut protege

 private :

      // Attribut prive

      int _f;

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const F& aF);
   void _destroy(void);

};

#endif // _F_H_
