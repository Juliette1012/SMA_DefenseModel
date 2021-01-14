#include "MessageAgentIA.h"

//--
MessageAgentIA::MessageAgentIA(int i) : Message(), _i(i)
{
 newMessage();
}

//--
MessageAgentIA::MessageAgentIA(const MessageAgentIA& aM) : Message(aM)
{
 newMessage();
 _copy(aM);
}

//--
MessageAgentIA& MessageAgentIA::operator=(const MessageAgentIA& aM)
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
MessageAgentIA::~MessageAgentIA(void)
{
 _destroy();
}

//--
bool operator==(const MessageAgentIA& aM1, const MessageAgentIA& aM2)
{
 return aM1.isEqualTo(aM2);
}

//--
bool operator!=(const MessageAgentIA& aM1, const MessageAgentIA& aM2)
{
 return !(aM1==aM2);
}

//--
void MessageAgentIA::setInt(int i)
{
 _i = i;
}

//--
int  MessageAgentIA::getInt(void) const
{
 return _i;
}

//--
ostream& operator<<(ostream& os, const MessageAgentIA& aM)
{
 aM.display(os);
 return os;
}

//--
void MessageAgentIA::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 Message::display(os);

 // Affichage des attributs de la classe MessageAgentIA

 os << "La valeur de l'int est : " << _i << endl;
}

//--
bool MessageAgentIA::isEqualTo(const MessageAgentIA& aM) const
{
 (void)aM; // Pour eviter un warning si pas utilise

 // ### : Test des attributs de la classe MessageAgentIA

 if (_i != aM._i) return false;

 if (!(Message::isEqualTo(aM))) return false;
 return true;
}

//--
void MessageAgentIA::_copy(const MessageAgentIA& aM)
{
 (void)aM; // Pour eviter un warning si pas utilise

 // ### : Affectation des attributs de la classe MessageAgentIA

 _i = aM._i;
}

//--
void MessageAgentIA::_destroy(void)
{
 // Destruction des attributs de la classe MessageAgentIA
 // rien !
}

