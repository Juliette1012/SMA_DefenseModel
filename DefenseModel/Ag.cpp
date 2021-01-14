#include "Ag.h"
#include "Eprouvette.h"

//--
Ag::Ag() : ImAgent()
{
    newAgent();
}

Ag::Ag(tuple<double, double> position) : ImAgent()
{
    newAgent();
    double x = get<0>(position);
    double y = get<1>(position);
    this->setX(x);
    this->setY(y);
}

Ag::Ag(string type) : ImAgent()
{
    newAgent();
    _type = type;
}

//--
Ag::Ag(const Ag& anA) : ImAgent(anA)
{
    newAgent();
    _copy(anA);
}

//--
Ag& Ag::operator=(const Ag& anA)
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
Ag::~Ag(void)
{
    _destroy();
}

//--
void Ag::onKeyPress(const char * key)
{
 if (strcmp(key,"h")==0 || strcmp(key,"H")==0) event_H();
 else
 ImAgent::onKeyPress(key);
}

void Ag::event_H(void)
{
    cout << endl;
    cout << "-------------------------------" << endl;
    cout << "Touches disponibles sur un Ag :" << endl;
    cout << "-------------------------------" << endl;
    cout << "d/D : destruction              " << endl;
    cout << "h/H : Help sur l'Ag !          " << endl;
    cout << "-------------------------------" << endl;
}

void Ag::displayAg()
{ 
    extern Eprouvette* eprouvette;
    this->setColor("red");  
    square(0.7,1);
    attachTo(*eprouvette);
}


//--
void Ag::live(double dt)
{
    (void)dt; // Pour eviter un warning si pas utilise

    // "Comportement" d'un Agent de la classe Ag

    size_t alea = randomMinMax(1,300);
    if (alea == 1) { 
                    Ag * agt = new Ag(*this);

                    double oldTheta = agt->getTheta();
                    size_t maxAlea = 8;
                    alea = randomMinMax(1,maxAlea);
                    agt->setTheta((alea-1)*2*M_PI/maxAlea);
                    //_host->setNbAg(_host->getNbAg() + 1);
                    Ag *firstAg;
                    do
                    {
                    firstAg = (Ag*)agt->viewFirst("Ag",2*M_PI,_squareSize);
                    if (firstAg) {
                        agt->translate(_squareSize,0);
                    }
                    } while (firstAg);
                    
                    agt->setTheta(oldTheta);
    }
}


//--
bool operator==(const Ag& anA1, const Ag& anA2)
{
 return anA1.isEqualTo(anA2);
}

//--
bool operator!=(const Ag& anA1, const Ag& anA2)
{
 return !(anA1==anA2);
}

//--
ostream& operator<<(ostream& os, const Ag& anA)
{
 anA.display(os);
 return os;
}

//--
void Ag::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 ImAgent::display(os);

 // ### : Affichage des attributs de la classe Ag
 // Exemple : os << _at;
}

//--
bool Ag::isEqualTo(const Ag& anA) const
{
 (void)anA; // Pour eviter un warning si pas utilise

 // ### : Test des attributs de la classe Ag
 // Exemple : if (_at != anA._at) return false;

 if (!(ImAgent::isEqualTo(anA))) return false;
 return true;
}

//--
void Ag::_copy(const Ag& anA)
{
 (void)anA; // Pour eviter un warning si pas utilise

 // ### : Affectation des attributs de la classe Ag
 // Exemple : _at = anA._at;
}

//--
void Ag::_destroy(void)
{
 // ### : Destruction des attributs de la classe Ag
 // Exemple : delete _at;
}

