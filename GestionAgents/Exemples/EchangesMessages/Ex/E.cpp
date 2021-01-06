#include "E.h"
#include "MessageInt.h"

//--
E::E(int e) : Agent(),
              _cycle(0), _e(e)
{
 newAgent();
 setSensitivity("MessageInt",true);
}

//--
E::E(const E& anE) : Agent(anE)
{
 newAgent();
 _copy(anE);
}

//--
E& E::operator=(const E& anE)
{
 if (this != &anE)
 {
  Agent::operator=(anE);
  _destroy();
  _copy(anE);
 }
 return *this;
}

//--
E::~E(void)
{
 _destroy();
}

//--
void E::live(double dt)
{
 (void)dt;

 // "Comportement" d'un Agent de la classe E

 string agentName = getName();
 string className = getClass();
 string prefixe   = "["+agentName+"]";

 cout << ">>--------------------------------------------------------" << endl;
 cout << prefixe << " My name class is " <<  className << endl;

 while (getNbMessages())
 {
  MessageInt*  message = (MessageInt*)getNextMessage();

  Agent*       emitter = message->getEmitter();
  string   emitterName = "(NULL)";

  if (exist(emitter)) emitterName = emitter->getName();

  cout << prefixe << " I receive a message from : " << emitterName
                  << " with value : " << message->getInt() << endl;

  cout << prefixe << " => I reply to " << emitterName
                  << " with value "    << _e << endl;

  MessageInt m(_e);
  sendMessageTo(m,emitter);

  delete message;
 }

 cout << "<<--------------------------------------------------------" << endl;

 _cycle++;
}

//--
bool operator==(const E& anE1, const E& anE2)
{
 return anE1.isEqualTo(anE2);
}

//--
bool operator!=(const E& anE1, const E& anE2)
{
 return !(anE1==anE2);
}

//--
void E::setE(int e)
{
  _e = e;
}

//--
int  E::getE(void) const
{
 return _e;
}

//--
ostream& operator<<(ostream& os, const E& anE)
{
 anE.display(os);
 return os;
}

//--
void E::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 Agent::display(os);

 // Affichage des attributs de la classe E

 os << "E::La valeur de _cycle:" << _cycle << endl;
 os << "E::La valeur de _e:"     << _e << endl;
}

//--
bool E::isEqualTo(const E& anE) const
{
 (void)anE; // Pour eviter un warning si pas utilise

 // Test des attributs de la classe E

 if (_cycle != anE._cycle) return false;
 if (_e != anE._e)         return false;

 if (!(Agent::isEqualTo(anE))) return false;
 return true;
}

//--
void E::_copy(const E& anE)
{
 (void)anE; // Pour eviter un warning si pas utilise

 // ### : Affectation des attributs de la classe E

 _cycle = anE._cycle;
 _e     = anE._e;
}

//--
void E::_destroy(void)
{
 // Destruction des attributs de la classe E
 // rien !
}
