/*----------------------------------------------------------------------------
  prg.cpp
----------------------------------------------------------------------------*/

#include "Agent2D.h"
#include "AgentCMA.h"
#include "AgentLMA.h"
#include "AgentIA.h"
#include "Environnement.h"
#include "Label.h"
#include "Ag.h"
#include "Eprouvette.h"

Eprouvette *eprouvette = NULL; // variable globale

/*-------- Application -----------------------------------------------------*/
/*---- application specific data ----*/

#include "AppliData.h"

void deleteAppliData(AppliData *data)
{
  /*
  for (auto &obj : data->obj)
  {
    delete obj;
  }
  for (auto &objIA : data->objIA)
  {
    delete objIA;
  }*/
  delete (data->obj); 
  delete (data->eprouvette);
  delete (data->env);
  delete (data->sched);
  delete (data);
}

void help(void)
{
  cout << "*********************************************" << endl;
  cout << "help" << endl;
  cout << "----" << endl;
  cout << "Actions clavier AVEC objet selectionne:" << endl;
  cout << "- n : obtenir le nom d'un Agent2D" << endl;
  cout << "- p : obtenir le nom de l'environnement d'un Agent2D" << endl;
  cout << "- v : visualiser la défense (éprouvette) de l'agent2D" << endl;
  cout << "Actions clavier SANS objet selectionne:" << endl;
  cout << "- h : help" << endl;
  cout << "- a : autoscale (oui/non)" << endl;
  cout << "-' ': pause     (oui/non)" << endl;
  cout << "- q : quitter" << endl;
  cout << "*********************************************" << endl;
}

int main(void)
{

  AppliData *data;

  /*---- initialize graphic window ----*/

  graphic_init("My Defense Model", "-*-helvetica-*-r-normal--14-*");
  graphic_setWidth(2000);
  graphic_setHeight(600);
  graphic_setBackground("white");

  /*---- initialize application specific data ----*/
  data = (AppliData *)malloc(sizeof(AppliData));
  data->sched = new Scheduler;
  data->sched->setRealTimeMode(true);

  /*---- initialize the CMA Agent  ----*/
  data->obj = new AgentCMA();

  /*---- initialize Networks Segment ----*/
  /*---- initialize LMA Agents ----*/
  /*---- initialize IA Agents ----*/
  /*---- initialize Environment Vizualisation ----*/
  data->env = new Environnement("Vizualisation defense", 120, -90, 75, 75, "white");
  Label *l = new Label(data->env);
  eprouvette = data->eprouvette = new Eprouvette(l, 70);

  // Network Segment A
  data->env = new Environnement("Network Segment A", 130, 50, 130, 150, "pink");
  new Label(data->env);
  data->obj = new AgentLMA(80, 50, data->env);

  data->obj = new AgentIA(130, 100, data->env, data->eprouvette);
  data->obj = new AgentIA(170, 30, data->env, data->eprouvette);
  data->obj = new AgentIA(100, -10, data->env, data->eprouvette);

  // Network Segment B
  data->env = new Environnement("Network Segment B", -90, -60, 120, 120, "purple");
  new Label(data->env);
  data->obj = new AgentLMA(-50, -50, data->env);

  data->obj = new AgentIA(-130, -100, data->env, data->eprouvette);
  data->obj = new AgentIA(-50, -100, data->env, data->eprouvette);
  data->obj = new AgentIA(-140, -20, data->env, data->eprouvette);

  // Network Segment C
  data->env = new Environnement("Network Segment C", -110, 80, 170, 100, "cyan");
  new Label(data->env);
  data->obj = new AgentLMA(-100, 50, data->env);

  data->obj = new AgentIA(-100, 110, data->env, data->eprouvette);
  data->obj = new AgentIA(-180, 70, data->env, data->eprouvette);
  data->obj = new AgentIA(-40, 80, data->env, data->eprouvette);

  /*----- help display ----*/
  help();

  /*---- Get all agentsIA of data->obj in the vector allAgtIA----*/
  vector<Agent*> allAgtIA;
  getAllAgents("AgentIA", allAgtIA);

  /*----- initialize random Ag in AgentIA ----*/
  // faire un type d'attaque random et nbre d'Ag qui attaque
  // Il(s) attaquent sur un AgentIA random également
  new Ag("Dos", (AgentIA*) allAgtIA.at(0)); // type, AgentIA

  /*----- initialize specific data -----*/

  data->autoscale = 0;
  data->pause = 0;

  /*---- run the graphic application ----*/
  graphic_run(data);

  return (0);
}

void graphic_mainLoop(void *userData)
{
  AppliData *data = (AppliData *)userData;
  if (!data->pause)
  {
    data->sched->cycle(); // Lancement d'un cycle de l'ordonnanceur
  }
  if (data->autoscale)
  {
    graphic_autoscale();
  }
}

void graphic_selectCallback(Agent2D *agt2d,
                            void *userData)
{
  AppliData *data = (AppliData *)userData;
  (void)agt2d;
  (void)data;

  if (agt2d == NULL)
    return; // No sens !

  agt2d->onSelection();
}

void graphic_keyPressCallback(Agent2D *agt2d,
                              const char *key,
                              void *userData)
{
  AppliData *data = (AppliData *)userData;
  (void)data;

  if (agt2d == NULL) // Interaction clavier SANS objet selectionne
  {
    /*
 if(!strcmp(key,"Left"))
  {
  graphic_mouseDragCallback(data->obj,
                            -0.5,0.0,userData); // simulate mouse drag
  }
 else if(!strcmp(key,"Right"))
  {
  graphic_mouseDragCallback(data->obj,
                            0.5,0.0,userData); // simulate mouse drag
  }*/
    if (!strcmp(key, "h") || !strcmp(key, "H"))
    {
      help();
    }
    else if (!strcmp(key, "a") || !strcmp(key, "A"))
    {
      data->autoscale = 1 - data->autoscale;
    }
    else if (!strcmp(key, " "))
    {
      data->pause = 1 - data->pause;
    }
    else if (!strcmp(key, "q") || !strcmp(key, "Q") || !strcmp(key, "\x1b")) // Esc
    {
      deleteAppliData(data);
      exit(0);
    }
    else
    {
      fprintf(stderr, "Viewer key <%s>\n", key);
    }
    return;
  }

  //  ET donc ici, interaction clavier AVEC un objet selectionne

  if (!strcmp(key, "n") || !strcmp(key, "N"))
  {
    cout << agt2d->getName() << endl;
    return;
  }

  agt2d->onKeyPress(key);
}

void graphic_mouseDragCallback(Agent2D *agt2d,
                               double dx,
                               double dy,
                               void *userData)
{
  AppliData *data = (AppliData *)userData;
  (void)data;

  agt2d->onMouseDrag(dx, dy); // Par defaut : deplacement de l'Agent2D a la souris
}
