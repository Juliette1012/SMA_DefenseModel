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

            Environnement(const char* name, int x, int y, double length, double width, const char* color);
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

           const char* getName(void);
           void setPosition(int x, int y);
           double getWidth(void);
           double getLength(void);
           double getPosX(void);
           double getPosY();

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
             const char* _name;
             int _x;
             int _y;
             double _length;
             double _width;

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const Environnement& anE);
   void _destroy(void);

};

#endif // _ENVIRONNEMENT_H_
