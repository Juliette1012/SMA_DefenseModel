#include "AgentIA.h"
#include "Eprouvette.h"
#include <math.h>
#include "Ag.h"
#include "Ac.h"

//--
AgentIA::AgentIA(void) : Agent2D()
{
    newAgent();

    _squareSize = 10.0; // Taille du AgentIA

    square(_squareSize, 2);
    setColor("black");

    int posX = randomMinMax(0, 100);
    int posY = randomMinMax(0, 100);

    setPosition(posX, posY);
}

AgentIA::AgentIA(int x, int y, Environnement *env, Eprouvette *eprouvette) : Agent2D()
{
    newAgent();

    _eprouvette = eprouvette;
    _squareSize = 10.0; // Taille du AgentIA
    _env = env;
    attachTo(*env);

    square(_squareSize, 2);
    setColor("black");

    setPosition(x, y);

    _nbAcImmature = 10;
    _nbAcMature = 0;
    _nbAcMemoire = 0;
    _nbAg = 0;
}

//--
AgentIA::AgentIA(const AgentIA &anI) : Agent2D(anI)
{
    newAgent();
    _copy(anI);
}

//--
AgentIA &AgentIA::operator=(const AgentIA &anI)
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
AgentIA::~AgentIA(void)
{
    _destroy();
}

void AgentIA::onKeyPress(const char *key)
{
    if (strcmp(key, "d") == 0 || strcmp(key, "D") == 0)
        delete this;
    if (strcmp(key, "p") == 0 || strcmp(key, "P") == 0)
    {
        cout << getName() << " from " << getEnv()->getName() << endl;
    }
    if (strcmp(key, "V") == 0 || strcmp(key, "v") == 0)
    {
        const char *name = getName().c_str();
        getEprouvette()->vizualisation(name, getEnv(), this);

    }
    else
        Agent2D::onKeyPress(key);
}

//--
void AgentIA::live(double dt)
{
    (void)dt; // Pour eviter un warning si pas utilise

    // "Comportement" d'un Agent de la classe AgentIA
}

Environnement *AgentIA::getEnv(void)
{
    return _env;
}

Eprouvette *AgentIA::getEprouvette(void)
{
    return _eprouvette;
}

//--
void AgentIA::setPosition(int x, int y)
{
    _x = x;
    _y = y;
    setLocation(_x, _y, 0);
}

void AgentIA::setAg(Ag *ag)
{
    if (ag != NULL){
        _Ag.push_back(ag);
        cout << "\nAdd an Ag: "<< ag << " to " << getName() << endl;
    } 
}

void AgentIA::setAc(Ac *ac)
{
    if (ac != NULL){
        _Ac.push_back(ac);
        //cout << "\nAdd an Ac: " << ac << " to " << getName() << endl;
    }
}


vector<Ag *> AgentIA::getAg(void)
{
    return _Ag;
}

vector<Ac *> AgentIA::getAc(void)
{
    return _Ac;
}

int AgentIA::getNbAcImmature(void){
    return _nbAcImmature;
}

int AgentIA::getNbAcMature(void){
    return _nbAcMature;
}

int AgentIA::getNbAcMemoire(void){
    return _nbAcMemoire;
}

int AgentIA::getNbAg(void){
    return _nbAg;
}

void AgentIA::setNbAg(int nbAg){
    cout << "Set with the number : " << nbAg << endl;
    _nbAg = nbAg;
    cout << "setNbAg of " << this->getName() << " : " << _nbAg << "\n\n";
}

void AgentIA::setNbAcImmature(int nbAcImmature){
    _nbAcImmature = nbAcImmature;
}

void AgentIA::setNbAcMature(int nbAcMature){
    _nbAcMature = nbAcMature;
    
}

void AgentIA::setNbAcMemoire(int nbAcMemoire){
    _nbAcMemoire = nbAcMemoire;
}

//--
bool operator==(const AgentIA &anI1, const AgentIA &anI2)
{
    return anI1.isEqualTo(anI2);
}

//--
bool operator!=(const AgentIA &anI1, const AgentIA &anI2)
{
    return !(anI1 == anI2);
}

//--
ostream &operator<<(ostream &os, const AgentIA &anI)
{
    anI.display(os);
    return os;
}

//--
void AgentIA::display(ostream &os) const
{
    (void)os; // Pour eviter un warning si pas utilise

    Agent2D::display(os);

    // ### : Affichage des attributs de la classe AgentIA
    // Exemple : os << _at;
}

//--
void AgentIA::_copy(const AgentIA &anI)
{
    (void)anI; // Pour eviter un warning si pas utilise

    // Affectation des attributs de la classe AgentIA
    // Exemple : _at = anI._at;

    _squareSize = anI._squareSize;
}

//--
void AgentIA::_destroy(void)
{
    // Destruction des attributs de la classe AgentIA
    // Exemple : delete _at;
}
