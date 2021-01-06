#include "C.h"

//--
C::C(void) : Agent()
{
 newAgent();
}

//--
C::C(const C& aC) : Agent(aC)
{
 newAgent();
 _copy(aC);
}

//--
C& C::operator=(const C& aC)
{
 if (this != &aC)
 {
  Agent::operator=(aC);
  _destroy();
  _copy(aC);
 }
 return *this;
}

//--
C::~C(void)
{
 _destroy();
}

//--
void C::live(double dt)
{
 (void)dt;

 // "Comportement" d'un Agent de la classe C
 cout << "C::My name is " << getName() << endl;
}

//--
bool operator==(const C& aC1, const C& aC2)
{
 return aC1.isEqualTo(aC2);
}

//--
bool operator!=(const C& aC1, const C& aC2)
{
 return !(aC1==aC2);
}

//--
ostream& operator<<(ostream& os, const C& aC)
{
 aC.display(os);
 return os;
}

//--
void C::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 Agent::display(os);

 // ### : Affichage des attributs de la classe C
 // Exemple : os << _at;
}

//--
bool C::isEqualTo(const C& aC) const
{
 (void)aC; // Pour eviter un warning si pas utilise

 // ### : Test des attributs de la classe C
 // Exemple : if (_at != aC._at) return false;

 if (!(Agent::isEqualTo(aC))) return false;
 return true;
}

//--
void C::_copy(const C& aC)
{
 (void)aC; // Pour eviter un warning si pas utilise

 // ### : Affectation des attributs de la classe C
 // Exemple : _at = aC._at;
}

//--
void C::_destroy(void)
{
 // ### : Destruction des attributs de la classe C
 // Exemple : delete _at;
}

