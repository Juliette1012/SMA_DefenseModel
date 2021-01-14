#include "AgentLMA.h"
#include "MessageAgentIA.h"
#include "MessageAgentLMA.h"
#include <math.h>

//--
AgentLMA::AgentLMA(void) : Agent2D()
{
 newAgent();

 _squareSize = 10.0;                             // Taille du AgentLMA

 square(_squareSize,2);
 setColor("blue");

 int posX = randomMinMax(0, 100);
 int posY = randomMinMax(0, 100);

 setPosition(posX, posY);
 setSensitivity("MessageAgentIA",true);
}

AgentLMA::AgentLMA(int x, int y, Environnement* env) : Agent2D()
{
 newAgent();

 _squareSize = 10.0;  // Taille du AgentLMA
 _env = env;                           
 attachTo(*env);

 square(_squareSize,2);
 setColor("blue");

 setPosition(x, y);
 setSensitivity("MessageAgentIA",true);
}

//--
AgentLMA::AgentLMA(const AgentLMA& anI) : Agent2D(anI)
{
 newAgent();
 _copy(anI);
}

//--
AgentLMA& AgentLMA::operator=(const AgentLMA& anI)
{
 if (this != &anI)
 {
  Agent2D::operator=(anI);
  _destroy();
  _copy(anI);
 }
 return *this;
}

//--
AgentLMA::~AgentLMA(void)
{
 _destroy();
}

void AgentLMA::onKeyPress(const char * key)
{
 if (strcmp(key,"d")==0 || strcmp(key,"D")==0) delete this;
 if (strcmp(key,"p")==0 || strcmp(key,"P")==0) {
     cout << getName() << " from " << getEnv()->getName() << endl;
 }
 else
 Agent2D::onKeyPress(key);
}

//--
void AgentLMA::live(double dt)
{
    string agentName = getName();
    string className = getClass();
    string prefixe   = "["+agentName+"]";
    (void)dt; // Pour eviter un warning si pas utilise

    // Recois de messages de AgentIA contenant le nombre d'Ag en son sein
    while (getNbMessages()){
        MessageAgentIA* message = (MessageAgentIA*)getNextMessage();
        Agent* emitter = message->getEmitter();
        string emitterName = emitter->getName();

        // cout << prefixe << " I receive a message from : " << emitterName
        //         << " with value : " << message->getInt() << endl;

        
        if ((int)_riskStatusAgentsIA.size() < 3){
            _riskStatusAgentsIA.push_back(message->getInt());
            _nameAgentsIA.push_back(emitterName);
        }

        else {
            if (_nameAgentsIA.at(0) == emitterName and (message->getInt() != _riskStatusAgentsIA.at(0))){
                _riskStatusAgentsIA.at(0) = message->getInt();
                cout << _riskStatusAgentsIA.at(0) << endl;
            }
            if (_nameAgentsIA.at(1) == emitterName and (message->getInt() != _riskStatusAgentsIA.at(1))){
                _riskStatusAgentsIA.at(1) = message->getInt();
            }

            if (_nameAgentsIA.at(2) == emitterName and (message->getInt() != _riskStatusAgentsIA.at(2))){
                    _riskStatusAgentsIA.at(2) = message->getInt();
            }
        }

        int compteur = 0;
        for (auto& risk : _riskStatusAgentsIA){
            compteur += risk;
        }
        //_riskStatusGlobalLMA = compteur;
        // Envoi un message au CMA contenant la menace
        //MessageAgentLMA m(_riskStatusGlobalLMA);
        if ((int)_riskStatusAgentsIA.size() == 3 ){
            _riskStatusGlobalLMA = compteur;
            MessageAgentLMA m(_riskStatusGlobalLMA);
            vector<Agent*> AgentCMA;
            getAllAgents("AgentCMA", AgentCMA);

            Agent* newAgentCMA = AgentCMA.at(0);

            sendMessageTo(m,newAgentCMA);
        }
        
        delete message;
    }


}

Environnement* AgentLMA::getEnv(void)
{
 return _env;
}

//--
void AgentLMA::setPosition(int x, int y)
{
 _x = x;
 _y = y;
 setLocation(_x, _y, 0);
}

//--
bool operator==(const AgentLMA& anI1, const AgentLMA& anI2)
{
 return anI1.isEqualTo(anI2);
}

//--
bool operator!=(const AgentLMA& anI1, const AgentLMA& anI2)
{
 return !(anI1==anI2);
}

//--
ostream& operator<<(ostream& os, const AgentLMA& anI)
{
 anI.display(os);
 return os;
}

//--
void AgentLMA::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 Agent2D::display(os);

 // ### : Affichage des attributs de la classe AgentLMA
 // Exemple : os << _at;
}

//--
void AgentLMA::_copy(const AgentLMA& anI)
{
 (void)anI; // Pour eviter un warning si pas utilise

 // Affectation des attributs de la classe AgentLMA
 // Exemple : _at = anI._at;

 _squareSize = anI._squareSize;
}

//--
void AgentLMA::_destroy(void)
{
 // Destruction des attributs de la classe AgentLMA
 // Exemple : delete _at;
}
