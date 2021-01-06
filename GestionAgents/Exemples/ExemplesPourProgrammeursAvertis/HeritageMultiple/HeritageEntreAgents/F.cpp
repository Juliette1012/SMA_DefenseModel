#include "F.h"
#include "MessageInt.h"

//--
F::F(int e, int f) : E(e), _f(f)
{
 newAgent();
}

//--
F::F(const F& aF) : E(aF)
{
 newAgent();
 _copy(aF);
}

//--
F& F::operator=(const F& aF)
{
 if (this != &aF)
 {
  E::operator=(aF);
  _destroy();
  _copy(aF);
 }
 return *this;
}

//--
F::~F(void)
{
 _destroy();
}

//--
void F::live(double dt)
{
 (void)dt;

 // "Comportement" d'un Agent de la classe F

 if (_cycle % 5 == 0) { MessageInt m(_f);
                        broadcastMessage(m);
 }

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

  delete message;
  }

 cout << "<<--------------------------------------------------------" << endl;

 _cycle++;
}

//--
bool operator==(const F& aF1, const F& aF2)
{
 return aF1.isEqualTo(aF2);
}

//--
bool operator!=(const F& aF1, const F& aF2)
{
 return !(aF1==aF2);
}

//--
void F::setF(int f)
{
  _f = f;
}

//--
int  F::getF(void) const
{
 return _f;
}

//--
ostream& operator<<(ostream& os, const F& aF)
{
 aF.display(os);
 return os;
}

//--
void F::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 E::display(os);

 // Affichage des attributs de la classe F

 os << "F::La valeur interne est _f:" << _f << endl;
}

//--
bool F::isEqualTo(const F& aF) const
{
 (void)aF; // Pour eviter un warning si pas utilise

 // Test des attributs de la classe F

 if (_f != aF._f) return false;

 if (!(E::isEqualTo(aF))) return false;
 return true;
}

//--
void F::_copy(const F& aF)
{
 (void)aF; // Pour eviter un warning si pas utilise

 // Affectation des attributs de la classe F

 _f = aF._f; 
}

//--
void F::_destroy(void)
{
 // Destruction des attributs de la classe F
 // rien !
}

