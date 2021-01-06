#include "MessageColor.h"

//--
MessageColor::MessageColor(const char* color) : Message()
{
 newMessage();

 _color = color;
}

//--
MessageColor::MessageColor(const MessageColor& aM) : Message(aM)
{
 newMessage();
 _copy(aM);
}

//--
MessageColor& MessageColor::operator=(const MessageColor& aM)
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
MessageColor::~MessageColor(void)
{
 _destroy();
}

//--
const char* MessageColor::getColor(void)
{
 return _color.c_str();
}

//--
bool operator==(const MessageColor& aM1, const MessageColor& aM2)
{
 return aM1.isEqualTo(aM2);
}

//--
bool operator!=(const MessageColor& aM1, const MessageColor& aM2)
{
 return !(aM1==aM2);
}

//--
ostream& operator<<(ostream& os, const MessageColor& aM)
{
 aM.display(os);
 return os;
}

//--
void MessageColor::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 Message::display(os);

 // ### : Affichage des attributs de la classe MessageColor
 // Exemple : os << _at;

 os << _color;
}

//--
bool MessageColor::isEqualTo(const MessageColor& aM) const
{
 (void)aM; // Pour eviter un warning si pas utilise

 // ### : Test des attributs de la classe MessageColor
 // Exemple : if (_at != aM._at) return false;

 if (!(Message::isEqualTo(aM))) return false;
 if (_color != aM._color) return false;
 return true;
}

//--
void MessageColor::_copy(const MessageColor& aM)
{
 (void)aM; // Pour eviter un warning si pas utilise

 // ### : Affectation des attributs de la classe MessageColor
 // Exemple : _at = aM._at;

 _color = aM._color;
}

//--
void MessageColor::_destroy(void)
{
 // ### : Destruction des attributs de la classe MessageColor
 // Exemple : delete _at;
}

