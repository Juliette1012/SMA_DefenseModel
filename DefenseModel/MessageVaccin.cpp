#include "MessageVaccin.h"

//--
MessageVaccin::MessageVaccin() : Message()
{
 newMessage();
}

//--
MessageVaccin::MessageVaccin(const MessageVaccin& aM) : Message(aM)
{
 newMessage();
 _copy(aM);
}

//--
MessageVaccin& MessageVaccin::operator=(const MessageVaccin& aM)
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
MessageVaccin::~MessageVaccin(void)
{
 _destroy();
}

//--
bool operator==(const MessageVaccin& aM1, const MessageVaccin& aM2)
{
 return aM1.isEqualTo(aM2);
}

//--
bool operator!=(const MessageVaccin& aM1, const MessageVaccin& aM2)
{
 return !(aM1==aM2);
}

//--
ostream& operator<<(ostream& os, const MessageVaccin& aM)
{
 aM.display(os);
 return os;
}

//--
void MessageVaccin::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 Message::display(os);

 // ### : Affichage des attributs de la classe MessageVaccin
 // Exemple : os << _at;
}

//--
bool MessageVaccin::isEqualTo(const MessageVaccin& aM) const
{
 (void)aM; // Pour eviter un warning si pas utilise

 // ### : Test des attributs de la classe MessageVaccin
 // Exemple : if (_at != aM._at) return false;
}

//--
void MessageVaccin::_copy(const MessageVaccin& aM)
{
 (void)aM; // Pour eviter un warning si pas utilise

 // ### : Affectation des attributs de la classe MessageVaccin
 // Exemple : _at = aM._at;
}

//--
void MessageVaccin::_destroy(void)
{
 // ### : Destruction des attributs de la classe MessageVaccin
 // Exemple : delete _at;
}

