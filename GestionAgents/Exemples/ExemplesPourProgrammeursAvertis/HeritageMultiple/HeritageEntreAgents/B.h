#ifndef _B_H_
#define _B_H_

#include <iostream>

#include "MAS.h"
#include "A.h"

using namespace std;

class B : public A
{
  DEFCLASS(B)

  friend ostream& operator<<(ostream& os, const B& aB);

 public :

   // Allocateurs/Desallocateurs

            B(void);
            B(const B& aB);
            B& operator=(const B& aB);
   virtual ~B(void);

   virtual  void live(double dt);

   // Comparaisons

   friend  bool operator==(const B& aB1, const B& aB2);
   friend  bool operator!=(const B& aB1, const B& aB2);

   // Inspecteurs/modificateurs

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const B& aB) const;

 protected :

             // ###

 private :

             // ###

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const B& aB);
   void _destroy(void);

};

#endif // _B_H_
