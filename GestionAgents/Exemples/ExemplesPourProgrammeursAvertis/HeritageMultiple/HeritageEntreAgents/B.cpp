#include "B.h"

//--
B::B(void) : A()
{
 newAgent();
}

//--
B::B(const B& aB) : A(aB)
{
 newAgent();
 _copy(aB);
}

//--
B& B::operator=(const B& aB)
{
 if (this != &aB)
 {
  A::operator=(aB);
  _destroy();
  _copy(aB);
 }
 return *this;
}

//--
B::~B(void)
{
 _destroy();
}

//--
void B::live(double dt)
{
 (void)dt;

 // Comportement" d'un Agent de la classe B
 cout << "B::My name is " << getName() << endl;
}

//--
bool operator==(const B& aB1, const B& aB2)
{
 return aB1.isEqualTo(aB2);
}

//--
bool operator!=(const B& aB1, const B& aB2)
{
 return !(aB1==aB2);
}

//--
ostream& operator<<(ostream& os, const B& aB)
{
 aB.display(os);
 return os;
}

//--
void B::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 A::display(os);

 // ### : Affichage des attributs de la classe B
 // Exemple : os << _at;
}

//--
bool B::isEqualTo(const B& aB) const
{
 (void)aB; // Pour eviter un warning si pas utilise

 // ### : Test des attributs de la classe B
 // Exemple : if (_at != aB._at) return false;

 if (!(A::isEqualTo(aB))) return false;
 return true;
}

//--
void B::_copy(const B& aB)
{
 (void)aB; // Pour eviter un warning si pas utilise

 // ### : Affectation des attributs de la classe B
 // Exemple : _at = aB._at;
}

//--
void B::_destroy(void)
{
 // ### : Destruction des attributs de la classe B
 // Exemple : delete _at;
}

