#include "MB.h"

//--
MB::MB( /* ### */ ) : Message()
{
 newMessage();
}

//--
MB::MB(const MB& aM) : Message(aM)
{
 newMessage();
 _copy(aM);
}

//--
MB& MB::operator=(const MB& aM)
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
MB::~MB(void)
{
 _destroy();
}

//--
bool operator==(const MB& aM1, const MB& aM2)
{
 return aM1.isEqualTo(aM2);
}

//--
bool operator!=(const MB& aM1, const MB& aM2)
{
 return !(aM1==aM2);
}

//--
ostream& operator<<(ostream& os, const MB& aM)
{
 aM.display(os);
 return os;
}

//--
void MB::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 Message::display(os);

 // ### : Affichage des attributs de la classe MB
 // Exemple : os << _at;
}

//--
bool MB::isEqualTo(const MB& aM) const
{
 (void)aM; // Pour eviter un warning si pas utilise

 // ### : Test des attributs de la classe MB
 // Exemple : if (_at != aM._at) return false;

 if (!(Message::isEqualTo(aM))) return false;
 return true;
}

//--
void MB::_copy(const MB& aM)
{
 (void)aM; // Pour eviter un warning si pas utilise

 // ### : Affectation des attributs de la classe MB
 // Exemple : _at = aM._at;
}

//--
void MB::_destroy(void)
{
 // ### : Destruction des attributs de la classe MB
 // Exemple : delete _at;
}

