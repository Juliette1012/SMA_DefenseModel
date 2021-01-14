#include "AgentCMA.h"
#include "MessageAgentLMA.h"
#include <math.h>

//--
AgentCMA::AgentCMA(void) : Agent2D()
{
 newAgent();

 _squareSize = 15.0;                             // Taille du AgentCMA

 square(_squareSize,2);
 setColor("red");

}

//--
AgentCMA::AgentCMA(const AgentCMA& anI) : Agent2D(anI)
{
 newAgent();
 _copy(anI);
}

//--
AgentCMA& AgentCMA::operator=(const AgentCMA& anI)
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
AgentCMA::~AgentCMA(void)
{
 _destroy();
}

void AgentCMA::onKeyPress(const char * key)
{
 if (strcmp(key,"d")==0 || strcmp(key,"D")==0) delete this;
 else
 if (strcmp(key,"r")==0 || strcmp(key,"R")==0) event_R();
 else
 Agent2D::onKeyPress(key);
}

//--
void AgentCMA::live(double dt)
{
 (void)dt; // Pour eviter un warning si pas utilise

 // "Comportement" d'un Agent de la classe AgentCMA
    string agentName = getName();
    string className = getClass();
    string prefixe   = "["+agentName+"]";
    (void)dt; // Pour eviter un warning si pas utilise

    // "Comportement" d'un Agent de la classe AgentLMA
    while (getNbMessages()){
        MessageAgentLMA* message = (MessageAgentLMA*)getNextMessage();
        Agent* emitter = message->getEmitter();
        string emitterName = emitter->getName();

        // cout << prefixe << " I receive a message from : " << emitterName
        //         << " with value : " << message->getInt() << endl;

        if ((int)_riskStatusAgentsLMA.size() < 3){
            _riskStatusAgentsLMA.push_back(message->getInt());
            _nameAgentsLMA.push_back(emitterName);
        }

        else {
            if (_nameAgentsLMA.at(0) == emitterName and (message->getInt() != _riskStatusAgentsLMA.at(0))){
                _riskStatusAgentsLMA.at(0) = message->getInt();
            }
            if (_nameAgentsLMA.at(1) == emitterName and (message->getInt() != _riskStatusAgentsLMA.at(1))){
                _riskStatusAgentsLMA.at(1) = message->getInt();
            }

            if (_nameAgentsLMA.at(2) == emitterName and (message->getInt() != _riskStatusAgentsLMA.at(2))){
                    _riskStatusAgentsLMA.at(2) = message->getInt();
            }
        }

        int compteur = 0;
        for (auto& risk : _riskStatusAgentsLMA){
            compteur += risk;
        }

        if (_riskStatusGlobalCMA != compteur ){
            _riskStatusGlobalCMA = compteur;
            cout << "risk global : " << _riskStatusGlobalCMA << endl;
        }


        delete message;
    }
}

void AgentCMA::event_R(void){
    cout << "Le risk status global est : " << this->getRiskStatus() << endl;
}
int AgentCMA::getRiskStatus(void){
    return _riskStatusGlobalCMA;
}

//--
bool operator==(const AgentCMA& anI1, const AgentCMA& anI2)
{
 return anI1.isEqualTo(anI2);
}

//--
bool operator!=(const AgentCMA& anI1, const AgentCMA& anI2)
{
 return !(anI1==anI2);
}

//--
ostream& operator<<(ostream& os, const AgentCMA& anI)
{
 anI.display(os);
 return os;
}

//--
void AgentCMA::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 Agent2D::display(os);

 // ### : Affichage des attributs de la classe AgentCMA
 // Exemple : os << _at;
}

//--
void AgentCMA::_copy(const AgentCMA& anI)
{
 (void)anI; // Pour eviter un warning si pas utilise

 // Affectation des attributs de la classe AgentCMA
 // Exemple : _at = anI._at;

 _squareSize = anI._squareSize;
}

//--
void AgentCMA::_destroy(void)
{
 // Destruction des attributs de la classe AgentCMA
 // Exemple : delete _at;
}
