#ifndef _LABEL_H_
#define _LABEL_H_

#include <iostream>

#include "MAS.h"
#include "Agent2D.h"
#include "Environnement.h"

using namespace std;

class Label : public Agent2D
{
  DEFCLASS(Label)

  friend ostream& operator<<(ostream& os, const Label& aL);

 public :

   // Allocateurs/Desallocateurs

            Label(Environnement* env);
            Label(const Label& aL);
            Label& operator=(const Label& aL);
   virtual ~Label(void);

   virtual  void live(double dt);

            void setText(const char* name, Environnement* env);

   // Comparaisons

   friend  bool operator==(const Label& aL1, const Label& aL2);
   friend  bool operator!=(const Label& aL1, const Label& aL2);

   // Inspecteurs/modificateurs

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const Label& aL) const;

 protected :

             // ###

 private :

             // ###

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const Label& aL);
   void _destroy(void);

};

#endif // _LABEL_H_
