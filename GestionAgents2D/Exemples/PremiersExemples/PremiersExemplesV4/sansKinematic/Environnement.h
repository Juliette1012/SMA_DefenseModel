#ifndef _ENVIRONNEMENT_H_
#define _ENVIRONNEMENT_H_

#include <iostream>

#include "MAS.h"

#include "Agent2D.h"

using namespace std;

class Environnement : public Agent2D
{
  DEFCLASS(Environnement)

  friend ostream& operator<<(ostream& os, const Environnement& anE);

 public :

   // Allocateurs/Desallocateurs

            Environnement(double size);
            Environnement(const Environnement& anE);
            Environnement& operator=(const Environnement& anE);
   virtual ~Environnement(void);

   virtual  void live(double dt);

   virtual  void onKeyPress(const char * key);
   virtual  void onMouseDrag(double dx,double dy);

   // Comparaisons

   friend  bool operator==(const Environnement& anE1,
                           const Environnement& anE2);
   friend  bool operator!=(const Environnement& anE1,
                           const Environnement& anE2);

   // Inspecteurs/modificateurs

           double getSize(void);

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const Environnement& anE) const;

 protected :

             // ###

 private :

             double    _size;

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const Environnement& anE);
   void _destroy(void);

};

#endif // _ENVIRONNEMENT_H_
