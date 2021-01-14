#include "MessageAgentCMA.h"

//--
MessageAgentCMA::MessageAgentCMA() : Message()
{
 newMessage();
}

//--
MessageAgentCMA::MessageAgentCMA(const MessageAgentCMA& aM) : Message(aM)
{
 newMessage();
 _copy(aM);
}

//--
MessageAgentCMA& MessageAgentCMA::operator=(const MessageAgentCMA& aM)
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
MessageAgentCMA::~MessageAgentCMA(void)
{
 _destroy();
}


//--
bool operator==(const MessageAgentCMA& aM1, const MessageAgentCMA& aM2)
{
 return aM1.isEqualTo(aM2);
}

//--
bool operator!=(const MessageAgentCMA& aM1, const MessageAgentCMA& aM2)
{
 return !(aM1==aM2);
}

//--
ostream& operator<<(ostream& os, const MessageAgentCMA& aM)
{
 aM.display(os);
 return os;
}

//--
void MessageAgentCMA::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 Message::display(os);

 // ### : Affichage des attributs de la classe MessageAgentCMA
 // Exemple : os << _at;
}

//--
bool MessageAgentCMA::isEqualTo(const MessageAgentCMA& aM) const
{
 (void)aM; // Pour eviter un warning si pas utilise

 // ### : Test des attributs de la classe MessageAgentCMA
 // Exemple : if (_at != aM._at) return false;
}

//--
void MessageAgentCMA::_copy(const MessageAgentCMA& aM)
{
 (void)aM; // Pour eviter un warning si pas utilise

 // ### : Affectation des attributs de la classe MessageAgentCMA
 // Exemple : _at = aM._at;
}

//--
void MessageAgentCMA::_destroy(void)
{
 // ### : Destruction des attributs de la classe MessageAgentCMA
 // Exemple : delete _at;
}

