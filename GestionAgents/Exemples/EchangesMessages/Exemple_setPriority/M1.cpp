#include "M1.h"

//--
M1::M1(size_t v) : Message()
{
 newMessage();

 _v = v;
}

//--
M1::M1(const M1& aM) : Message(aM)
{
 newMessage();
 _copy(aM);
}

//--
M1& M1::operator=(const M1& aM)
{
 if (this != &aM)
 {
  Message::operator=(aM);
  _destroy();
  _copy(aM);
 }
 return *this;
}

//--
M1::~M1(void)
{
 _destroy();
}

//--
bool operator==(const M1& aM1, const M1& aM2)
{
 return aM1.isEqualTo(aM2);
}

//--
bool operator!=(const M1& aM1, const M1& aM2)
{
 return !(aM1==aM2);
}

//--
size_t M1::getV(void)
{
 return _v;
}

void M1::setV(size_t v)
{
 _v = v;
}

//--
ostream& operator<<(ostream& os, const M1& aM)
{
 aM.display(os);
 return os;
}

//--
void M1::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 Message::display(os);

 // Affichage des attributs de la classe M1
 // Exemple : os << _at;

 cout << "Message de type M1, valeur interne : " << _v << endl;
}

//--
bool M1::isEqualTo(const M1& aM) const
{
 (void)aM; // Pour eviter un warning si pas utilise

 // Test des attributs de la classe M1
 // Exemple : if (_at != aM._at) return false;

 if (!(Message::isEqualTo(aM))) return false;
 if (_v != aM._v)               return false;
 return true;
}

//--
void M1::_copy(const M1& aM)
{
 (void)aM; // Pour eviter un warning si pas utilise

 // Affectation des attributs de la classe M1
 // Exemple : _at = aM._at;

 _v = aM._v;
}

//--
void M1::_destroy(void)
{
 // Destruction des attributs de la classe M1
 // Exemple : delete _at;
}

