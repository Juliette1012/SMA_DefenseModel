#ifndef _ACSMA_H_
#define _ACSMA_H_

#include <iostream>

#include "MAS.h"

#include "Agent.h"

#include "Ac.h"

using namespace std;

class AcSMA : public Agent
{
  DEFCLASS(AcSMA)

  friend ostream& operator<<(ostream& os, const AcSMA& anA);

 public :

   // Allocateurs/Desallocateurs

            AcSMA(size_t nb);
            AcSMA(const AcSMA& anA);
            AcSMA& operator=(const AcSMA& anA);
   virtual ~AcSMA(void);

            Ac* newAc(void);
            Ac* newAc(const Ac& anA);

   virtual  void live(double dt);

   // Comparaisons

   friend  bool operator==(const AcSMA& anA1, const AcSMA& anA2);
   friend  bool operator!=(const AcSMA& anA1, const AcSMA& anA2);

   // Inspecteurs/modificateurs

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const AcSMA& anA) const;

 protected :

             // ###

 private :

             Scheduler *_sched;

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const AcSMA& anA);
   void _destroy(void);

};

#endif // _ACSMA_H_
