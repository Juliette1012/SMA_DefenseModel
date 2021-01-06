#include "MAB.h"

//--
MAB::MAB( /* ### */ ) : MA( /* ### */ ),
                        MB( /* ### */ )
{
 _This = reinterpret_cast<Message*>(this);

 MA::newMessage(_This);
 MB::newMessage(_This);
}

//--
MAB::MAB(const MAB& aM) : MA(aM),
                          MB(aM)
{
 _This = (Message*)(void*)this;

 MA::newMessage(_This);
 MB::newMessage(_This);
 _copy(aM);
}

//--
MAB& MAB::operator=(const MAB& aM)
{
 if (this != &aM)
 {
  MA::operator=(aM);
  MB::operator=(aM);
  _destroy();
  _copy(aM);
 }
 return *this;
}

//--
MAB::~MAB(void)
{
 _destroy();
}

//--
void MAB::newMessage(void)
{
 MA::newMessage();
 MB::newMessage();
}

//--
void MAB::newMessage(Message* This)
{
 MA::newMessage(This);
 MB::newMessage(This);
}

//--
Agent* MAB::getEmitter(void) const
{
 return _This->getEmitter();
}

//--
string MAB::getClass(void) const
{
 return _This->getClass();
}

//--
bool MAB::isA(string aClass) const
{
 return _This->isA(aClass);
}

//--
bool operator==(const MAB& aM1, const MAB& aM2)
{
 return aM1.isEqualTo(aM2);
}

//--
bool operator!=(const MAB& aM1, const MAB& aM2)
{
 return !(aM1==aM2);
}

//--
ostream& operator<<(ostream& os, const MAB& aM)
{
 aM.display(os);
 return os;
}

//--
void MAB::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 MA::display(os);
 MB::display(os);

 // ### : Affichage des attributs de la classe MAB
 // Exemple : os << _at;
}

//--
bool MAB::isEqualTo(const MAB& aM) const
{
 (void)aM; // Pour eviter un warning si pas utilise

 // ### : Test des attributs de la classe MAB
 // Exemple : if (_at != aM._at) return false;

 if (!(MA::isEqualTo(aM))) return false;
 if (!(MB::isEqualTo(aM))) return false;
 return true;
}

//--
void MAB::_copy(const MAB& aM)
{
 (void)aM; // Pour eviter un warning si pas utilise

 // ### : Affectation des attributs de la classe MAB
 // Exemple : _at = aM._at;
}

//--
void MAB::_destroy(void)
{
 // ### : Destruction des attributs de la classe MAB
 // Exemple : delete _at;
}

