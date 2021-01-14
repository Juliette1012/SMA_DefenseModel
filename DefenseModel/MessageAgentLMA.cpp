#include "MessageAgentLMA.h"

//--
MessageAgentLMA::MessageAgentLMA(int i) : Message(), _i(i)
{
 newMessage();
}

//--
MessageAgentLMA::MessageAgentLMA(const MessageAgentLMA& aM) : Message(aM)
{
 newMessage();
 _copy(aM);
}

//--
MessageAgentLMA& MessageAgentLMA::operator=(const MessageAgentLMA& aM)
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
MessageAgentLMA::~MessageAgentLMA(void)
{
 _destroy();
}

//--
bool operator==(const MessageAgentLMA& aM1, const MessageAgentLMA& aM2)
{
 return aM1.isEqualTo(aM2);
}

//--
bool operator!=(const MessageAgentLMA& aM1, const MessageAgentLMA& aM2)
{
 return !(aM1==aM2);
}

//--
void MessageAgentLMA::setInt(int i)
{
 _i = i;
}

//--
int  MessageAgentLMA::getInt(void) const
{
 return _i;
}

//--
ostream& operator<<(ostream& os, const MessageAgentLMA& aM)
{
 aM.display(os);
 return os;
}

//--
void MessageAgentLMA::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 Message::display(os);

 // Affichage des attributs de la classe MessageAgentLMA

 os << "La valeur de l'int est : " << _i << endl;
}

//--
bool MessageAgentLMA::isEqualTo(const MessageAgentLMA& aM) const
{
 (void)aM; // Pour eviter un warning si pas utilise

 // ### : Test des attributs de la classe MessageAgentLMA

 if (_i != aM._i) return false;

 if (!(Message::isEqualTo(aM))) return false;
 return true;
}

//--
void MessageAgentLMA::_copy(const MessageAgentLMA& aM)
{
 (void)aM; // Pour eviter un warning si pas utilise

 // ### : Affectation des attributs de la classe MessageAgentLMA

 _i = aM._i;
}

//--
void MessageAgentLMA::_destroy(void)
{
 // Destruction des attributs de la classe MessageAgentLMA
 // rien !
}

