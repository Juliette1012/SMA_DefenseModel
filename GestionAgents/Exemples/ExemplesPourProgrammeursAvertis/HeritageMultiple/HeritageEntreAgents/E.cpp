#include "E.h"
#include "MessageInt.h"

//--
E::E(int e) : B(),
              D(),
              _cycle(0), _e(e)
{
 _This = reinterpret_cast<Agent*>(this);

 B::newAgent(_This);
 D::newAgent(_This);

 setSensitivity("MessageInt",true);
}

//--
E::E(const E& anE) : B(anE),
                     D(anE)
{
 _This = (Agent*)(void*)this;

 B::newAgent(_This);
 D::newAgent(_This);
 _copy(anE);
}

//--
E& E::operator=(const E& anE)
{
 if (this != &anE)
 {
  B::operator=(anE);
  D::operator=(anE);
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
void E::newAgent(void)
{
 B::newAgent();
 D::newAgent();
}

//--
void E::newAgent(Agent* This)
{
 B::newAgent(This);
 D::newAgent(This);
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
string E::getName(void) const
{
 return _This->getName(); 
}

//--
string E::getClass(void) const
{
 return _This->getClass(); 
}

//--
bool E::isA(string aClass) const
{
 return _This->isA(aClass); 
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

 B::display(os);
 D::display(os);

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

 if (!(B::isEqualTo(anE))) return false;
 if (!(D::isEqualTo(anE))) return false;
 return true;
}

//--
size_t E::getNbMessages(void) const
{
 return _This->getNbMessages();
}

//--
Message* E::getNextMessage(void)
{
 return _This->getNextMessage();
}

void E::setSensitivity(string aClass,bool yesNo)
{
 _This->setSensitivity(aClass,yesNo);
}

//--
size_t E::sendMessageTo(Message& aM,Agent *dest) const
{
 return _This->sendMessageTo(aM,dest);
}

//--
void   E::broadcastMessage(Message& aM) const
{
 _This->broadcastMessage(aM);
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
