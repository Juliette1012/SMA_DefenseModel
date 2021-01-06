#include "MessageInt.h"

//--
MessageInt::MessageInt(int i) : Message(), _i(i)
{
 newMessage();
}

//--
MessageInt::MessageInt(const MessageInt& aM) : Message(aM)
{
 newMessage();
 _copy(aM);
}

//--
MessageInt& MessageInt::operator=(const MessageInt& aM)
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
MessageInt::~MessageInt(void)
{
 _destroy();
}

//--
bool operator==(const MessageInt& aM1, const MessageInt& aM2)
{
 return aM1.isEqualTo(aM2);
}

//--
bool operator!=(const MessageInt& aM1, const MessageInt& aM2)
{
 return !(aM1==aM2);
}

//--
void MessageInt::setInt(int i)
{
 _i = i;
}

//--
int  MessageInt::getInt(void) const
{
 return _i;
}

//--
ostream& operator<<(ostream& os, const MessageInt& aM)
{
 aM.display(os);
 return os;
}

//--
void MessageInt::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 Message::display(os);

 // Affichage des attributs de la classe MessageInt

 os << "La valeur de l'int est : " << _i << endl;
}

//--
bool MessageInt::isEqualTo(const MessageInt& aM) const
{
 (void)aM; // Pour eviter un warning si pas utilise

 // ### : Test des attributs de la classe MessageInt

 if (_i != aM._i) return false;

 if (!(Message::isEqualTo(aM))) return false;
 return true;
}

//--
void MessageInt::_copy(const MessageInt& aM)
{
 (void)aM; // Pour eviter un warning si pas utilise

 // ### : Affectation des attributs de la classe MessageInt

 _i = aM._i;
}

//--
void MessageInt::_destroy(void)
{
 // Destruction des attributs de la classe MessageInt
 // rien !
}

