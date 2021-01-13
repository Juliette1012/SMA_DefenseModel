#ifndef _AG_H_
#define _AG_H_

#include <iostream>

#include "MAS.h"

#include "ImAgent.h"
#include "AgentIA.h"


class AgentIA;
using namespace std;

class Ag : public ImAgent
{
  DEFCLASS(Ag)

  friend ostream& operator<<(ostream& os, const Ag& anA);

 public :

   // Allocateurs/Desallocateurs

            Ag(AgentIA* host);
            Ag(string type, AgentIA* host);
            Ag(const Ag& anA);
            Ag& operator=(const Ag& anA);
   virtual ~Ag(void);

   virtual  void onKeyPress(const char * key);

            void event_H(void);

   virtual  void live(double dt);
            void displayAg();


   // Comparaisons

   friend  bool operator==(const Ag& anA1, const Ag& anA2);
   friend  bool operator!=(const Ag& anA1, const Ag& anA2);

   // Inspecteurs/modificateurs

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const Ag& anA) const;

 protected :
            string _type;
            class AgentIA* _host;
             // ###

 private :

             // ###

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const Ag& anA);
   void _destroy(void);

};

#endif // _AG_H_
