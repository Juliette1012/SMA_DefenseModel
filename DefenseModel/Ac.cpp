#include "Ac.h"

#include "Decor.h"

Ac::Ac(AgentIA* host, int type) : ImAgent()
{
    newAgent();
    _agentIA = host;
    _cercle = new Object2D();
    _type = type;
    extern Eprouvette* eprouvette;
}

//--
Ac::Ac(const Ac& anA) : ImAgent(anA)
{
    newAgent();
    _copy(anA);
}

//--
Ac& Ac::operator=(const Ac& anA)
{
 if (this != &anA)
 {
  ImAgent::operator=(anA);
  _destroy();
  _copy(anA);
   
 }
 return *this;
}

//--
Ac::~Ac(void)
{
 _destroy();
}

void Ac::deleteDecor(){
    _cercle->noShape();
}

void Ac::displayAc()
{
    square(0.7,1);

    double x,y,t; getLocation(x,y,t);
    _vision = 3.0 * _squareSize;

    addDecor(_cercle);

    _cercle->setLocation(x,y,t);
    _cercle->circle(_vision,0);
    

    _cercle->attachTo(*this);
    attachTo(*_cercle);

    if (_type == 0){
        // Immature
        this->setColor("green");
        _cercle->setColor(this->getColor());
    }
    else if (_type == 1){
        //Mature
        this->setColor("yellow");
        _cercle->setColor(this->getColor());
    }
    else if (_type == 2){
        //Memoire
        this->setColor("orange");
        _cercle->setColor(this->getColor());
    }

    stop();
    //start();    
}


//--
void Ac::onKeyPress(const char * key)
{
 if (strcmp(key,"h")==0 || strcmp(key,"H")==0) event_H();
 else
 if (strcmp(key,"s")==0 || strcmp(key,"S")==0) event_S();
 else
 if (strcmp(key,"v")==0 || strcmp(key,"V")==0)
 {
  if (_cercle->getColor()==NULL) _cercle->circle(_vision,0);
  else _cercle->noShape();
 }
 else
 ImAgent::onKeyPress(key);
}

void Ac::event_H(void)
{
 cout << endl;
 cout << "-------------------------------" << endl;
 cout << "Touches disponibles sur un Ac :" << endl;
 cout << "-------------------------------" << endl;
 cout << "d/D : destruction              " << endl;
 cout << "v/V : visu/non visu cercle     " << endl;
 cout << "s/S : start/stop               " << endl;
 cout << "h/H : Help sur l'Ac !          " << endl;
 cout << "-------------------------------" << endl;
}

void Ac::event_S(void)
{
 if (_start) stop();
 else        start();
}

//--
void Ac::live(double dt)
{
 (void)dt; // Pour eviter un warning si pas utilise

 if (dt!=0.0 && _start) Kinematic(dt);

 // "Comportement" d'un Agent de la classe Ac

 Ag *firstAg;
 
 firstAg = (Ag*)viewFirst("Ag",2*M_PI,0); 
 if (firstAg)
 {
    //Si un agent Ag est detecte alors on devient mature et on attaque
    for (Ac* ac : _agentIA->getAc()){
        ac->setColor("yellow");
        _cercle->setColor(this->getColor());
        this->setType(1); // mature
    }
    double xAg = firstAg->getX();
    double yAg = firstAg->getY();
    if (towards(xAg,yAg) <= _vision)
    {
        //L'agent devient mémoire en détruisant un Ag
        this->setColor("orange");
        _cercle->setColor(this->getColor());
        this->setType(2); // memoire
        //delete firstAg;
        setLinearVelocityX(0);
        //update the agent state
    }
    //cout << _agentIA->getNbAcMature() << endl;
 }
 else setLinearVelocityX(0);

 if (!_start) setLinearVelocityX(0); // Si towards a modifie la vitesse !
}

void Ac::start(void)
{
 _start = true;
}

void Ac::stop(void)
{
 _start = false;
 setLinearVelocityX(0);
}

int Ac::getType(){
    return _type;
}
void Ac::setType(int type){
    _type = type;
}

//--
bool operator==(const Ac& anA1, const Ac& anA2)
{
 return anA1.isEqualTo(anA2);
}

//--
bool operator!=(const Ac& anA1, const Ac& anA2)
{
 return !(anA1==anA2);
}

//--
ostream& operator<<(ostream& os, const Ac& anA)
{
 anA.display(os);
 return os;
}

//--
void Ac::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 ImAgent::display(os);

 // Affichage des attributs de la classe Ac
 // Exemple : os << _at;
 
 cout << getName() << " champ de vision : " << _vision << endl;
}

//--
bool Ac::isEqualTo(const Ac& anA) const
{
 (void)anA; // Pour eviter un warning si pas utilise

 // ### : Test des attributs de la classe Ac
 // Exemple : if (_at != anA._at) return false;

 if (!(ImAgent::isEqualTo(anA))) return false;
 if (_vision  != anA._vision)    return false;
 if (*_cercle != *anA._cercle)   return false; 
 return true;
}

//--
void Ac::_copy(const Ac& anA)
{
 (void)anA; // Pour eviter un warning si pas utilise

 // Affectation des attributs de la classe Ac
 // Exemple : _at = anA._at;

 _vision = anA._vision;

 _cercle = new Object2D(*anA._cercle);
 addDecor(_cercle);

 _cercle->attachTo(*this);
 attachTo(*_cercle);
}

//--
void Ac::_destroy(void)
{
 // Destruction des attributs de la classe Ac
 // Exemple : delete _at;

 removeDecor(_cercle);
 delete _cercle;
}

