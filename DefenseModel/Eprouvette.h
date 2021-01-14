#ifndef _EPROUVETTE_H_
#define _EPROUVETTE_H_

#include <iostream>
#include <tuple>
#include "Object2D.h"
#include "ImAgent.h"
#include "AgentIA.h"
#include "Label.h"
#include "Ag.h"
#include "Ac.h"

class Ag; 
class Ac; 
class AgentIA;

#define SIZE 100

using namespace std;

class Eprouvette : public Object2D
{
  friend ostream& operator<<(ostream& os, const Eprouvette& anE);

 public :

   // Allocateurs/Desallocateurs

            Eprouvette(Label* l, size_t size=SIZE);
            Eprouvette(const Eprouvette& anE);
            Eprouvette& operator=(const Eprouvette& anE);
   virtual ~Eprouvette(void);

   virtual  void onKeyPress(const char * key);

            void event_H(void);
            void event_S(void);
            void event_C(void);
            void event_0(void);
            void event_1(void);
            void event_2(void);

            void vizualisation(const char* name, Environnement *env, AgentIA* agtIA);


   // Comparaisons

   friend  bool operator==(const Eprouvette& anE1, const Eprouvette& anE2);
   friend  bool operator!=(const Eprouvette& anE1, const Eprouvette& anE2);

   // Inspecteurs/modificateurs

          int  getSize(void) const;
          void setHostAgtIA(AgentIA* agtIA);
          void deleteLastHost();

          vector<int> getTypeAcHost(void);
          void setTypeAcHost(int type);
          void clearTypeAcHost(void);

          int getTypeAgHost(void);
          void setTypeAgHost(int type);
          void clearTypeAgHost(void);

          void saveAcImmaturePosHost(double x, double y);
          vector<tuple<double, double>> getAcImmaturePosHost(void);
          void setAcImmaturePosHost(vector<tuple<double,double>> positions);

          void saveAcMaturePosHost(double x, double y);
          vector<tuple<double, double>> getAcMaturePosHost(void);
          void setAcMaturePosHost(vector<tuple<double,double>> positions);

          void saveAcMemoirePosHost(double x, double y);
          vector<tuple<double, double>> getAcMemoirePosHost(void);
          void setAcMemoirePosHost(vector<tuple<double,double>> positions);

          void clearAcPosHost(void);

          void saveAgPosHost(double x, double y);
          vector<tuple<double, double>> getAgPosHost(void);
          void setAgPosHost(vector<tuple<double,double>> positions);
          void clearAgPosHost(void);

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const Eprouvette& anE) const;

 protected :          
           Label* _l;

          class AgentIA* _hostAgtIA = NULL;
          vector<int> _typeAcHost;
          int _typeAgHost;

           vector<tuple<double, double>> _agPosHost;
           vector<tuple<double, double>> _acImmaturePosHost;
           vector<tuple<double, double>> _acMaturePosHost;
           vector<tuple<double, double>> _acMemoirePosHost;

 private :

           size_t _size;
           bool   _start; // Les Ac sont-ils "actifs"


 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const Eprouvette& anE);
   void _destroy(void);

};

#endif // _EPROUVETTE_H_
