#include "Toto.h"

//--
Toto::Toto( /* ### */ ) : Agent()
{
 newAgent();
}

//--
Toto::Toto(const Toto& aT) : Agent(aT)
{
 newAgent();
 _copy(aT);
}

//--
Toto& Toto::operator=(const Toto& aT)
{
 if (this != &aT)
 {
  Agent::operator=(aT);
  _destroy();
  _copy(aT);
 }
 return *this;
}

//--
Toto::~Toto(void)
{
 _destroy();
}

//--
void Toto::live(double dt)
{
 (void)dt; // Pour eviter un warning si pas utilise

 // ### : "Comportement" d'un Agent de la classe Toto
 
 cout << "Hello " << getName() << endl;
}

//--
bool operator==(const Toto& aT1, const Toto& aT2)
{
 return aT1.isEqualTo(aT2);
}

//--
bool operator!=(const Toto& aT1, const Toto& aT2)
{
 return !(aT1==aT2);
}

//--
ostream& operator<<(ostream& os, const Toto& aT)
{
 aT.display(os);
 return os;
}

//--
void Toto::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 Agent::display(os);

 // ### : Affichage des attributs de la classe Toto
 // Exemple : os << _at;
}

//--
bool Toto::isEqualTo(const Toto& aT) const
{
 (void)aT; // Pour eviter un warning si pas utilise

 // ### : Test des attributs de la classe Toto
 // Exemple : if (_at != aT._at) return false;

 if (!(Agent::isEqualTo(aT))) return false;
 return true;
}

//--
void Toto::_copy(const Toto& aT)
{
 (void)aT; // Pour eviter un warning si pas utilise

 // ### : Affectation des attributs de la classe Toto
 // Exemple : _at = aT._at;
}

//--
void Toto::_destroy(void)
{
 // ### : Destruction des attributs de la classe Toto
 // Exemple : delete _at;
}

