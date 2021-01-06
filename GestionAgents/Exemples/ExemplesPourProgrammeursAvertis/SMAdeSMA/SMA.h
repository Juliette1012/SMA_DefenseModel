#ifndef _SMA_H_
#define _SMA_H_

#include <iostream>

#include "MAS.h"

using namespace std;

class SMA : public Agent
{
  DEFCLASS(SMA)

  friend ostream& operator<<(ostream& os, const SMA& aS);

 public :

   // Allocateurs/Desallocateurs

            SMA(size_t nbAgents);
            SMA(const SMA& aS);
            SMA& operator=(const SMA& aS);
   virtual ~SMA(void);

   virtual  void live(double dt);

   // Comparaisons

   friend  bool operator==(const SMA& aS1, const SMA& aS2);
   friend  bool operator!=(const SMA& aS1, const SMA& aS2);

   // Inspecteurs/modificateurs

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const SMA& aS) const;

 protected :

 private :

           Scheduler *_sched;

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const SMA& aS);
   void _destroy(void);

};

#endif // _SMA_H_
