#ifndef _IMAGENT_H_
#define _IMAGENT_H_

#include <iostream>

#include "MAS.h"

#include "Agent2D.h"

using namespace std;

class ImAgent : public Agent2D
{
  DEFCLASS(ImAgent)

  friend ostream& operator<<(ostream& os, const ImAgent& anI);

 public :

   // Allocateurs/Desallocateurs

            ImAgent(void);
            ImAgent(const ImAgent& anI);
            ImAgent& operator=(const ImAgent& anI);
   virtual ~ImAgent(void);

   virtual  void onKeyPress(const char * key);

   virtual  void live(double dt);

   // Comparaisons

   friend  bool operator==(const ImAgent& anI1, const ImAgent& anI2);
   friend  bool operator!=(const ImAgent& anI1, const ImAgent& anI2);

   // Inspecteurs/modificateurs

       // distance retourne une distance
            double distance(double xP,double yP) const;

       // towards retourne une distance et oriente vers xP, yP
            double towards(double xP,double yP);

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const ImAgent& anI) const;

 protected :

             double _squareSize;

 private :

             

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const ImAgent& anI);
   void _destroy(void);

};

#endif // _IMAGENT_H_
