#ifndef _EPROUVETTE_H_
#define _EPROUVETTE_H_

#include <iostream>

#include "Object2D.h"

#define SIZE 100

using namespace std;

class Eprouvette : public Object2D
{
  friend ostream& operator<<(ostream& os, const Eprouvette& anE);

 public :

   // Allocateurs/Desallocateurs

            Eprouvette(size_t size=SIZE);
            Eprouvette(const Eprouvette& anE);
            Eprouvette& operator=(const Eprouvette& anE);
   virtual ~Eprouvette(void);

   virtual  void onKeyPress(const char * key);

            void event_H(void);
            void event_S(void);
            void event_C(void);
            void event_G(void);

   // Comparaisons

   friend  bool operator==(const Eprouvette& anE1, const Eprouvette& anE2);
   friend  bool operator!=(const Eprouvette& anE1, const Eprouvette& anE2);

   // Inspecteurs/modificateurs

           int  getSize(void) const;

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const Eprouvette& anE) const;

 protected :

 private :

           size_t _size;
           bool   _start; // Les Ac sont-ils "actifs"

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const Eprouvette& anE);
   void _destroy(void);

};

#endif // _EPROUVETTE_H_
