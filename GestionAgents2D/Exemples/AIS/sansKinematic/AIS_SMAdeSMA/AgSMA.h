#ifndef _AGSMA_H_
#define _AGSMA_H_

#include <iostream>

#include "MAS.h"

#include "Agent.h"

#include "Ag.h"

using namespace std;

class AgSMA : public Agent
{
  DEFCLASS(AgSMA)

  friend ostream& operator<<(ostream& os, const AgSMA& anA);

 public :

   // Allocateurs/Desallocateurs

            AgSMA(size_t nb);
            AgSMA(const AgSMA& anA);
            AgSMA& operator=(const AgSMA& anA);
   virtual ~AgSMA(void);

            Ag* newAg(void);
            Ag* newAg(const Ag& anA);

   virtual  void live(double dt);

   // Comparaisons

   friend  bool operator==(const AgSMA& anA1, const AgSMA& anA2);
   friend  bool operator!=(const AgSMA& anA1, const AgSMA& anA2);

   // Inspecteurs/modificateurs

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const AgSMA& anA) const;

 protected :

             // ###

 private :

             Scheduler *_sched;

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const AgSMA& anA);
   void _destroy(void);

};

#endif // _AGSMA_H_
