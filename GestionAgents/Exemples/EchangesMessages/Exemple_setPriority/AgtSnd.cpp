#include "AgtSnd.h"

#include "M1.h"
#include "M2.h"
#include "AgtRcv.h"

//--
AgtSnd::AgtSnd( /* ### */ ) : Agent()
{
 newAgent();
}

//--
AgtSnd::AgtSnd(const AgtSnd& anA) : Agent(anA)
{
 newAgent();
 _copy(anA);
}

//--
AgtSnd& AgtSnd::operator=(const AgtSnd& anA)
{
 if (this != &anA)
 {
  Agent::operator=(anA);
  _destroy();
  _copy(anA);
 }
 return *this;
}

//--
AgtSnd::~AgtSnd(void)
{
 _destroy();
}

//--
void AgtSnd::live(double dt)
{
 (void)dt; // Pour eviter un warning si pas utilise

 // "Comportement" d'un Agent de la classe AgtSnd

 AgtRcv *recv = (AgtRcv*)getAgent("AgtRcv.1");  // On recupere celui qui va
 if (recv==NULL) return;                        // recevoir

 size_t alea=randomMinMax(1,10);

 cout << "###" << endl;
 cout << "### Alea = " << alea << endl;
 cout << "###" << endl;

 for(size_t i=0;i<alea;i++)
 {
  M1 m1(i);
  M2 m2(i);
#if 1                     // 1 : pour tester la priorite des messages...
  m1.setPriority(1);      // Le setPriority peut aussi etre mis dans les
  m2.setPriority(0);      // constructeurs des classes M1 et M2
#endif
  sendMessageTo(m1,recv);
  sendMessageTo(m2,recv);
  m1.setV(i+100);
  sendMessageTo(m1,recv);
  m2.setV(i+100);
  sendMessageTo(m2,recv);
 }
}

//--
bool operator==(const AgtSnd& anA1, const AgtSnd& anA2)
{
 return anA1.isEqualTo(anA2);
}

//--
bool operator!=(const AgtSnd& anA1, const AgtSnd& anA2)
{
 return !(anA1==anA2);
}

//--
ostream& operator<<(ostream& os, const AgtSnd& anA)
{
 anA.display(os);
 return os;
}

//--
void AgtSnd::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 Agent::display(os);

 // ### : Affichage des attributs de la classe AgtSnd
 // Exemple : os << _at;
}

//--
bool AgtSnd::isEqualTo(const AgtSnd& anA) const
{
 (void)anA; // Pour eviter un warning si pas utilise

 // ### : Test des attributs de la classe AgtSnd
 // Exemple : if (_at != anA._at) return false;

 if (!(Agent::isEqualTo(anA))) return false;
 return true;
}

//--
void AgtSnd::_copy(const AgtSnd& anA)
{
 (void)anA; // Pour eviter un warning si pas utilise

 // ### : Affectation des attributs de la classe AgtSnd
 // Exemple : _at = anA._at;
}

//--
void AgtSnd::_destroy(void)
{
 // ### : Destruction des attributs de la classe AgtSnd
 // Exemple : delete _at;
}

