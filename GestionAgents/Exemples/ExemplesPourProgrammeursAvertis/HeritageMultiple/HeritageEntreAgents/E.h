#ifndef _E_H_
#define _E_H_

#include <iostream>

#include "MAS.h"
#include "B.h"
#include "D.h"

using namespace std;

class E : public B,
          public D
{
  DEFCLASS(E)

  friend ostream& operator<<(ostream& os, const E& anE);

 public :

   // Allocateurs/Desallocateurs

            E(int e);
            E(const E& anE);
            E& operator=(const E& anE);
   virtual ~E(void);

   virtual  void live(double dt);

           string getName(void) const;        // Redefinition
           string getClass(void) const;       // des methodes
           bool   isA(string aClass) const;   // de Agent

   // Comparaisons

   friend  bool operator==(const E& anE1, const E& anE2);
   friend  bool operator!=(const E& anE1, const E& anE2);

   // Gestion des messages : Redefinition des methodes de Agent

           size_t   getNbMessages(void) const;
           Message* getNextMessage(void);

           void     setSensitivity(string aClass,bool yesNo);
                                                                 // retourne
           size_t   sendMessageTo(Message& aM,Agent *dest) const;// 1(ok),0(ko)
           void     broadcastMessage(Message& aM) const;

   // Inspecteurs/modificateurs

           void setE(int e);
           int  getE(void) const;

 protected :

   // Methodes a appeler par une classe derivee

           void newAgent(void); // Pour lever l'ambiguite (heritage multiple)
           void newAgent(Agent* This); // Idem...

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const E& anE) const;

 protected :

      // Attribut protege

          int _cycle;

 private :

      // Attribut private

          Agent* _This;   // Important pour la redefinition des methodes
                          // afin de lever les ambiguites. 
          int    _e;

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const E& anE);
   void _destroy(void);

};

#endif // _E_H_
