#include "Agt.h"

//--
Agt::Agt(size_t v) : Agent()
{
 newAgent();
 _v = v;
}

//--
Agt::Agt(const Agt& anA) : Agent(anA)
{
 newAgent();
 _copy(anA);
}

//--
Agt& Agt::operator=(const Agt& anA)
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
Agt::~Agt(void)
{
 _destroy();
}

//--
void Agt::live(double dt)
{
 (void)dt; // Pour eviter un warning si pas utilise

 // "Comportement" d'un Agent de la classe Agt

 cout << "My name is " << getName() << " and my value is " << _v << endl;
}

//--
bool operator==(const Agt& anA1, const Agt& anA2)
{
 return anA1.isEqualTo(anA2);
}

//--
bool operator!=(const Agt& anA1, const Agt& anA2)
{
 return !(anA1==anA2);
}

//--
ostream& operator<<(ostream& os, const Agt& anA)
{
 anA.display(os);
 return os;
}

//--
void Agt::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 Agent::display(os);

 // ### : Affichage des attributs de la classe Agt
 // Exemple : os << _at;

 os << _v;
}

//--
bool Agt::isEqualTo(const Agt& anA) const
{
 (void)anA; // Pour eviter un warning si pas utilise

 // ### : Test des attributs de la classe Agt
 // Exemple : if (_at != anA._at) return false;

 if (!(Agent::isEqualTo(anA))) return false;
 if (_v != anA._v)             return false;
 return true;
}

//--
void Agt::_copy(const Agt& anA)
{
 (void)anA; // Pour eviter un warning si pas utilise

 // ### : Affectation des attributs de la classe Agt
 // Exemple : _at = anA._at;
 
 _v = anA._v;
}

//--
void Agt::_destroy(void)
{
 // ### : Destruction des attributs de la classe Agt
 // Exemple : delete _at;
}
