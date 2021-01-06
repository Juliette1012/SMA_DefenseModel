#include "AgtRcv.h"

#include "M1.h"
#include "M2.h"

#include <vector>

using namespace std;

//--
AgtRcv::AgtRcv( /* ### */ ) : Agent()
{
 newAgent();
}

//--
AgtRcv::AgtRcv(const AgtRcv& anA) : Agent(anA)
{
 newAgent();
 _copy(anA);
}

//--
AgtRcv& AgtRcv::operator=(const AgtRcv& anA)
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
AgtRcv::~AgtRcv(void)
{
 _destroy();
}

//--
void AgtRcv::live(double dt)
{
 (void)dt; // Pour eviter un warning si pas utilise

 // "Comportement" d'un Agent de la classe AgtRcv

 // Traitement des Messages avec priorites fixes avec
 // setPriority (voir dans AgtSnd.cpp la methode live)

 cout << "-------------- Les messages --------------" << endl;

 while (getNbMessages())
 {
  Message* m = getNextMessage();

  if (m->isA("M1"))
  {
   M1* m1=(M1*)m;
   cout << "M1: " << m1->getV() << endl;
  }
  else
  if (m->isA("M2"))
  {
   M2* m2=(M2*)m;
   cout << "M2: " << m2->getV() << endl;
  }
  else cout << "Message ni M1, ni M2" << endl;

  delete m;
 }
}

//--
bool operator==(const AgtRcv& anA1, const AgtRcv& anA2)
{
 return anA1.isEqualTo(anA2);
}

//--
bool operator!=(const AgtRcv& anA1, const AgtRcv& anA2)
{
 return !(anA1==anA2);
}

//--
ostream& operator<<(ostream& os, const AgtRcv& anA)
{
 anA.display(os);
 return os;
}

//--
void AgtRcv::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 Agent::display(os);

 // ### : Affichage des attributs de la classe AgtRcv
 // Exemple : os << _at;
}

//--
bool AgtRcv::isEqualTo(const AgtRcv& anA) const
{
 (void)anA; // Pour eviter un warning si pas utilise

 // ### : Test des attributs de la classe AgtRcv
 // Exemple : if (_at != anA._at) return false;

 if (!(Agent::isEqualTo(anA))) return false;
 return true;
}

//--
void AgtRcv::_copy(const AgtRcv& anA)
{
 (void)anA; // Pour eviter un warning si pas utilise

 // ### : Affectation des attributs de la classe AgtRcv
 // Exemple : _at = anA._at;
}

//--
void AgtRcv::_destroy(void)
{
 // ### : Destruction des attributs de la classe AgtRcv
 // Exemple : delete _at;
}

