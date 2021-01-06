#include "M2.h"

//--
M2::M2(size_t v) : Message()
{
 newMessage();

 _v = v;
}

//--
M2::M2(const M2& aM) : Message(aM)
{
 newMessage();
 _copy(aM);
}

//--
M2& M2::operator=(const M2& aM)
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
M2::~M2(void)
{
 _destroy();
}

//--
bool operator==(const M2& aM1, const M2& aM2)
{
 return aM1.isEqualTo(aM2);
}

//--
bool operator!=(const M2& aM1, const M2& aM2)
{
 return !(aM1==aM2);
}

//--
size_t M2::getV(void)
{
 return _v;
}

void M2::setV(size_t v)
{
 _v = v;
}

//--
ostream& operator<<(ostream& os, const M2& aM)
{
 aM.display(os);
 return os;
}

//--
void M2::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 Message::display(os);

 // Affichage des attributs de la classe M2
 // Exemple : os << _at;

 cout << "Message de type M2, valeur interne : " << _v << endl;
}

//--
bool M2::isEqualTo(const M2& aM) const
{
 (void)aM; // Pour eviter un warning si pas utilise

 // Test des attributs de la classe M2
 // Exemple : if (_at != aM._at) return false;

 if (!(Message::isEqualTo(aM))) return false;
 if (_v != aM._v)               return false;
 return true;
}

//--
void M2::_copy(const M2& aM)
{
 (void)aM; // Pour eviter un warning si pas utilise

 // Affectation des attributs de la classe M2
 // Exemple : _at = aM._at;

 _v = aM._v;
}

//--
void M2::_destroy(void)
{
 // Destruction des attributs de la classe M2
 // Exemple : delete _at;
}

