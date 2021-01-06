#include "MA.h"

//--
MA::MA( /* ### */ ) : Message()
{
 newMessage();
}

//--
MA::MA(const MA& aM) : Message(aM)
{
 newMessage();
 _copy(aM);
}

//--
MA& MA::operator=(const MA& aM)
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
MA::~MA(void)
{
 _destroy();
}

//--
bool operator==(const MA& aM1, const MA& aM2)
{
 return aM1.isEqualTo(aM2);
}

//--
bool operator!=(const MA& aM1, const MA& aM2)
{
 return !(aM1==aM2);
}

//--
ostream& operator<<(ostream& os, const MA& aM)
{
 aM.display(os);
 return os;
}

//--
void MA::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 Message::display(os);

 // ### : Affichage des attributs de la classe MA
 // Exemple : os << _at;
}

//--
bool MA::isEqualTo(const MA& aM) const
{
 (void)aM; // Pour eviter un warning si pas utilise

 // ### : Test des attributs de la classe MA
 // Exemple : if (_at != aM._at) return false;

 if (!(Message::isEqualTo(aM))) return false;
 return true;
}

//--
void MA::_copy(const MA& aM)
{
 (void)aM; // Pour eviter un warning si pas utilise

 // ### : Affectation des attributs de la classe MA
 // Exemple : _at = aM._at;
}

//--
void MA::_destroy(void)
{
 // ### : Destruction des attributs de la classe MA
 // Exemple : delete _at;
}

