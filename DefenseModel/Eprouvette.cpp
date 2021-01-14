#include "Eprouvette.h"

#include <vector>
#include <tuple>
#include "Decor.h"

//--
Eprouvette::Eprouvette( Label* l, size_t size) : Object2D()
{
    addDecor(this);
    _l = l;
    _size = size;
    setColor("black");
    setLocation(120, -90, 0);
    square(_size,0);

    _start=false;
}

//--
Eprouvette::Eprouvette(const Eprouvette& anE) : Object2D(anE)
{
    addDecor(this);
    _copy(anE);
}

//--
Eprouvette& Eprouvette::operator=(const Eprouvette& anE)
{
    if (this != &anE)
    {
    Object2D::operator=(anE);
    _destroy();
    _copy(anE);
    }
    return *this;
}

//--
Eprouvette::~Eprouvette(void)
{
    _destroy();
    removeDecor(this);
}

//--
void Eprouvette::onKeyPress(const char * key)
{
    if (strcmp(key,"H")==0 || strcmp(key,"h")==0) event_H();
    else
    if (strcmp(key,"S")==0 || strcmp(key,"s")==0) event_S();
    else
    if (strcmp(key,"C")==0 || strcmp(key,"c")==0) event_C();
    else
    if (strcmp(key,"0")==0) event_0();
    else
    if (strcmp(key,"1")==0) event_1();
    else
    if (strcmp(key,"2")==0) event_2();
}

void Eprouvette::setHostAgtIA(AgentIA* agtIA)
{
    _hostAgtIA = agtIA;
    cout << "host changed : " << agtIA->getName() << endl;
}

// Type Ac 
vector<int> Eprouvette::getTypeAcHost(void){
    return _typeAcHost;
}

void Eprouvette::setTypeAcHost(int type){
    _typeAcHost.push_back(type);
}

void Eprouvette::clearTypeAcHost(void){
    _typeAcHost.clear();
}

// Type Ag
int Eprouvette::getTypeAgHost(void){
    return _typeAgHost;
}

void Eprouvette::setTypeAgHost(int type){
    _typeAgHost = type;
}

void Eprouvette::clearTypeAgHost(void){
    _typeAgHost = NULL;
}

// Ac Immature
void Eprouvette::saveAcImmaturePosHost(double x, double y){
    _acImmaturePosHost.push_back(make_tuple(x, y));
}

void Eprouvette::setAcImmaturePosHost(vector<tuple<double,double>> positions){
    _acImmaturePosHost = positions;
}

vector<tuple<double,double>> Eprouvette::getAcImmaturePosHost(void){
    return _acImmaturePosHost;
}

// Ac Mature
void Eprouvette::saveAcMaturePosHost(double x, double y){
    _acMaturePosHost.push_back(make_tuple(x, y));
}

void Eprouvette::setAcMaturePosHost(vector<tuple<double,double>> positions){
    _acMaturePosHost = positions;
}

vector<tuple<double,double>> Eprouvette::getAcMaturePosHost(void){
    return _acMaturePosHost;
}

// Ac Memoire
void Eprouvette::saveAcMemoirePosHost(double x, double y){
    _acMemoirePosHost.push_back(make_tuple(x, y));
}

void Eprouvette::setAcMemoirePosHost(vector<tuple<double,double>> positions){
    _acMemoirePosHost = positions;
}

vector<tuple<double,double>> Eprouvette::getAcMemoirePosHost(void){
    return _acMemoirePosHost;
}

// Clear all vector<tuple<int,int> of Ac : Immature, Mature, Memoire
void Eprouvette::clearAcPosHost(void){
    _acImmaturePosHost.clear();
    _acMaturePosHost.clear();
    _acMemoirePosHost.clear();
}

// Ag
void Eprouvette::saveAgPosHost(double x, double y){
    _agPosHost.push_back(make_tuple(x, y));
}

void Eprouvette::setAgPosHost(vector<tuple<double,double>> positions){
    _agPosHost = positions;
}

vector<tuple<double,double>> Eprouvette::getAgPosHost(void){
    return _agPosHost;
}

// Clear vector<tuple<int,int>> Ag
void Eprouvette::clearAgPosHost(void){
    _agPosHost.clear();
}

void Eprouvette::vizualisation(const char* name, Environnement *env, AgentIA* agtIA)
{
    _l->setText(name, env);

    vector<Agent*> allAc;
    vector<Agent*> allAg;

    if (_hostAgtIA != NULL){
        getAllAgents("Ac", allAc);
        getAllAgents("Ag", allAg);

        //Avant de changer d'éprouvette, il faut sauvegarder l'état courant de l'agentIA
        //remise à 0 des compteurs
        int nbAcImmature = 0;
        int nbAcMature = 0;
        int nbAcMemoire = 0;
        int nbAg = 0;
        
        for (Agent* ac : allAc){
            Ac* newAc = (Ac *) ac;
            switch(newAc->getType()){
                case 0:
                    nbAcImmature++;
                    saveAcImmaturePosHost(newAc->getX(), newAc->getY());
                    break;
                case 1:
                    nbAcMature++;
                    saveAcMaturePosHost(newAc->getX(), newAc->getY());
                    break;
                case 2:
                    nbAcMemoire++;
                    saveAcMemoirePosHost(newAc->getX(), newAc->getY());
                    break;
                default:
                    cout << "Error of wrong type " << endl;
                    break;
            };
        }

        // cout << "NbAcImmature : " << nbAcImmature << endl;
        // cout << "NbAcMature : " << nbAcMature << endl;
        // cout << "NbAcMemoire : " << nbAcMemoire << endl;
        nbAg = (int) allAg.size();

        
        for (Agent* ag : allAg){
            Ag* newAg = (Ag*) ag;
            saveAgPosHost(newAg->getX(), newAg->getY());
        }

        _hostAgtIA->setNbAcImmature(nbAcImmature);
        _hostAgtIA->setNbAcMature(nbAcMature);
        _hostAgtIA->setNbAcMemoire(nbAcMemoire);
        _hostAgtIA->setNbAg(nbAg);

        _hostAgtIA->setAgPos(this->getAgPosHost());
        _hostAgtIA->setAcImmaturePos(this->getAcImmaturePosHost());
        _hostAgtIA->setAcMaturePos(this->getAcMaturePosHost());
        _hostAgtIA->setAcMemoirePos(this->getAcMemoirePosHost());
    }

    // delete all Ac et Ag

    for (auto& ac : allAc) delete ac;
    for (auto& ag : allAg) delete ag; 


    // update l'host
    this->setHostAgtIA(agtIA);

    // clear vector type AgHost
    this->clearTypeAgHost();
    // clear vector type AcHost
    this->clearTypeAcHost();

    // clear anciennes  positions des Ag et Ac
    this->clearAgPosHost();
    this->clearAcPosHost();

    // update types des Ag
    this->setTypeAgHost(_hostAgtIA->getTypeAg());

    // update positions des Ag si ils existaient avant
    this->setAgPosHost(_hostAgtIA->getAgPos());

    // update positions des Ac si ils existaient avant
    this->setAcImmaturePosHost(_hostAgtIA->getAcImmaturePos());
    this->setAcMaturePosHost(_hostAgtIA->getAcMaturePos());
    this->setAcMemoirePosHost(_hostAgtIA->getAcMemoirePos());

    // Depuis le nouveau host AgentIA
    // Créer le nombre correspondant d'ac et d'ag 
    if ((int)_hostAgtIA->getNbAcImmature() !=0) {
        for (int i=0; i < _hostAgtIA->getNbAcImmature(); i++){
            if ((int)this->getAcImmaturePosHost().size() != 0){
                // utilisation constructeur Ac avec sa position
                Ac* acImmature = new Ac(this->getAcImmaturePosHost().at(i), 0);
                acImmature->displayAc();
                this->setTypeAcHost(0);
        }
        else {
            Ac* acImmature = new Ac(0);
            acImmature->displayAc();
            this->setTypeAcHost(0);
        }
        }
    }
    if ((int)_hostAgtIA->getNbAcMature() !=0) {
        for (int i=0; i < _hostAgtIA->getNbAcMature(); i++){
            if ((int)this->getAcMaturePosHost().size() != 0){
                // utilisation constructeur Ac avec sa position
                Ac* acMature = new Ac(this->getAcMaturePosHost().at(i), 1);
                acMature->displayAc();
                this->setTypeAcHost(1);
        }
        else {
            Ac* acMature = new Ac(1);
            acMature->displayAc();
            this->setTypeAcHost(1);
        }
        }
    }
    if ((int)_hostAgtIA->getNbAcMemoire() !=0) {
        for (int i=0; i < _hostAgtIA->getNbAcMemoire(); i++){
            if ((int)this->getAcMemoirePosHost().size() != 0){
                // utilisation constructeur Ac avec sa position
                Ac* acMemoire = new Ac(this->getAcMemoirePosHost().at(i) ,2);
                acMemoire->displayAc();
                this->setTypeAcHost(2);
            }
        else {
            Ac* acMemoire = new Ac(2);
            acMemoire->displayAc();
            this->setTypeAcHost(2);
        }
        }
    }
    if ((int)_hostAgtIA->getNbAg() !=0) {
        for (int i=0; i < _hostAgtIA->getNbAg(); i++){
            if ((int)this->getAgPosHost().size() != 0){
                // utilisation constructeur Ag avec sa position et le type
                Ag* ag = new Ag(this->getTypeAgHost() ,this->getAgPosHost().at(i));
                ag->displayAg();
            }
            else {
                // Première création de cette Ag donc pas de position pré-enregistré
                Ag* ag = new Ag(this->getTypeAgHost());
                ag->displayAg();
            } 
        }
    }
}

void Eprouvette::event_H(void)
{
    cout << endl;
    cout << "---------------------------------------" << endl;
    cout << "Touches disponibles sur une Eprouvette :" << endl;
    cout << "---------------------------------------" << endl;
    cout << "c/C : Creation Ac                      " << endl;
    cout << "g/G : Creation Ag                      " << endl;
    cout << "s/S : start/stop de tous les Ac        " << endl;
    cout << "h/H : Help sur l'eprouvette !          " << endl;
    cout << "---------------------------------------" << endl;
}

void Eprouvette::event_S(void)
{
    vector<Agent*> v;
    getAllAgents("Ac",v);
    size_t i;
    if (_start)
    {
        for(i=0;i<v.size();i++)
        {
            Ac* ac=(Ac*)v[i];
            ac->stop();
        }
            _start=false;
        }
    else
    {
        for(i=0;i<v.size();i++)
        {
            Ac* ac=(Ac*)v[i];
            ac->start();
        }
        _start=true;
    }
}


void Eprouvette::event_C(void)
{
 Ac * agt = new Ac(0);
 cout << "Creation de " << agt->getName() << endl;
 agt->displayAc();
}

void  Eprouvette::event_0(void){
     Ag * agt = new Ag(0);
    cout << "Creation de " << agt->getName() << " de type DoS " << endl;
    agt->displayAg();
}

void  Eprouvette::event_1(void){
     Ag * agt = new Ag(1);
    cout << "Creation de " << agt->getName() << " de type brute-force " << endl;
    agt->displayAg();
}

void  Eprouvette::event_2(void){
    Ag * agt = new Ag(2);
    cout << "Creation de " << agt->getName() << " de type R2L " << endl;
    agt->displayAg();
}

//--
bool operator==(const Eprouvette& anE1, const Eprouvette& anE2)
{
 return anE1.isEqualTo(anE2);
}

//--
bool operator!=(const Eprouvette& anE1, const Eprouvette& anE2)
{
 return !(anE1==anE2);
}

//--
ostream& operator<<(ostream& os, const Eprouvette& anE)
{
 anE.display(os);
 return os;
}

//--
void Eprouvette::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 Object2D::display(os);

 // Affichage des attributs de la classe Eprouvette
 // Exemple : os << _at;

 os << "Taille eprouvette : " << _size;
}

//--
bool Eprouvette::isEqualTo(const Eprouvette& anE) const
{
 (void)anE; // Pour eviter un warning si pas utilise

 // Test des attributs de la classe Eprouvette
 // Exemple : if (_at != anE._at) return false;

 if (!(Object2D::isEqualTo(anE)))        return false;
 if (_size != anE._size)                 return false;
 return true;
}

//--
int Eprouvette::getSize(void) const
{
 return _size;
}

//--
void Eprouvette::_copy(const Eprouvette& anE)
{
 (void)anE; // Pour eviter un warning si pas utilise

 // Affectation des attributs de la classe Eprouvette
 // Exemple : _at = anE._at;

 _size       = anE._size;
}

//--
void Eprouvette::_destroy(void)
{
 // Destruction des attributs de la classe Eprouvette
 // Exemple : delete _at;
}
