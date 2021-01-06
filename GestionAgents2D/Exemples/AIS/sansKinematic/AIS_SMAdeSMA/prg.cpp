/*----------------------------------------------------------------------------
  prg.cpp
----------------------------------------------------------------------------*/

#include "Agent2D.h"

#include "Eprouvette.h"

#include "AcSMA.h"
#include "AgSMA.h"

Eprouvette *eprouvette = NULL;  // Variable globale: pas joli mais ca marche !

AcSMA* acSMA = NULL;
AgSMA* agSMA = NULL;

/////////////////// Pour la co-existence Agent2D - Object2D ///////////////////
//                                                                           //
#include "Decor.h"                                                           //
#include "Object2D.h"                                                        //
//                                                                           //
// typedef set<Object2D*> Decor;                                             //
//                                                                           //
// extern Decor decor;                      Contient uniquement des Object2D,//
//                                          pas des Agent2D !                //
// extern void addDecor(Object2D* obj2d);                                    //
// extern void removeDecor(Object2D* obj2d);                                 //
// extern bool isInDecor(Object2D* obj2d); ... pour interaction !            //
//                                             voir graphic_keyPressCallback //
//                                             et graphic_mouseDragCallback  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////


/*-------- Application -----------------------------------------------------*/

/*---- application specific data ----*/

#include "AppliData.h"

void deleteAppliData(AppliData * data)
{
 delete(data->eprouvette); eprouvette = NULL;
 delete(data->sched);
 delete(data);
}

void help(void)
{
 cout << "*********************************************"<< endl;
 cout << "help"                                         << endl;
 cout << "----"                                         << endl;
 cout << "Actions clavier AVEC objet selectionne:"      << endl;
 cout << "- p : obtenir le nom d'un Agent2D"            << endl;
 cout << "- d : detruire un Agent2D"                    << endl;
 cout << "- h : help sur l'eprouvettte, un Ac, un Ag"   << endl;
 cout << "Actions clavier SANS objet selectionne:"      << endl;
 cout << "- h : help"                                   << endl;
 cout << "- a : autoscale (oui/non)"                    << endl;
 cout << "-' ': pause     (oui/non)"                    << endl;
 cout << "- q : quitter"                                << endl;
 cout << "*********************************************"<< endl;
}

int
main(void)
{
AppliData * data;

/*---- initialize graphic window ----*/

graphic_init("My Window","-*-helvetica-*-r-normal--14-*");
graphic_setWidth(640);
graphic_setHeight(480);
graphic_setBackground("cyan4");

/*---- initialize application specific data ----*/

data=(AppliData *)malloc(sizeof(AppliData));
data->sched=new Scheduler;
data->sched->setRandomMode(true);
data->sched->setRealTimeMode(false);

/*---- initialize Environment  ----*/

eprouvette = data->eprouvette = new Eprouvette(); 

/*---- initialize Agent2D  ----*/

acSMA = new AcSMA(10);
agSMA = new AgSMA(2);

/*----- initialize specific data -----*/
  
data->autoscale=1;
data->pause=0;

/*---- run the graphic application ----*/

help();

graphic_run(data);
return(0);
}

void
graphic_mainLoop(void * userData)
{
AppliData * data=(AppliData *)userData;
if(!data->pause)
  {
   data->sched->cycle(); // Lancement d'un cycle de l'ordonnanceur
  }
if(data->autoscale)
  {
   graphic_autoscale();
  }
}

void
graphic_selectCallback(Agent2D * agt2d,
                       void * userData)
{
AppliData * data=(AppliData *)userData;
(void)agt2d;(void)data;
 
 if (agt2d==NULL) return; // No sens !

if (isInDecor((Object2D*)agt2d))
{// Interaction avec les Object2D du decor
 Object2D* obj2d=(Object2D*)agt2d;
 obj2d->onSelection();
 return;
}
 
 agt2d->onSelection();
}

void
graphic_keyPressCallback(Agent2D * agt2d,
                         const char * key,
                         void * userData)
{
AppliData * data=(AppliData *)userData;
(void)data;

if (agt2d==NULL)         // Interaction clavier SANS objet selectionne
{
 if(!strcmp(key,"h")||!strcmp(key,"H"))
  {
  help();
  }
 else if(!strcmp(key,"a")||!strcmp(key,"A"))
  {
  data->autoscale=1-data->autoscale;
  }
 else if(!strcmp(key," "))
  {
  data->pause=1-data->pause;
  }
 else if(!strcmp(key,"q")||!strcmp(key,"Q")||!strcmp(key,"\x1b")) // Esc
  {
  deleteAppliData(data);
  exit(0);
  }
 else fprintf(stderr,"Viewer key <%s>\n",key);
 
 return;
}
        //  ET donc ici, interaction clavier AVEC un objet selectionne

if ( // (Object2D*)agt2d==data->atelier ||
    isInDecor((Object2D*)agt2d)
   )                                  // Interaction avec les Object2D du decor
{
 Object2D* obj2d=(Object2D*)agt2d;

 obj2d->onKeyPress(key);

 return;
}

agt2d->onKeyPress(key); // Par defaut : si p affiche le nom de l'Agent2D
}

void
graphic_mouseDragCallback(Agent2D * agt2d,
                          double dx,
                          double dy,
                          void * userData)
{
AppliData * data=(AppliData *)userData;
(void)data;

if ( // (Object2D*)agt2d==data->atelier ||
    isInDecor((Object2D*)agt2d)
   )                                  // Interaction avec les Object2D du decor
{
 Object2D* obj2d=(Object2D*)agt2d;

#if 0
 (void)obj2d;               // Pas d'interaction avec le decor
#else
 obj2d->onMouseDrag(dx,dy); // Interaction avec le decor
#endif

 return;
}

agt2d->onMouseDrag(dx,dy); // Par defaut : deplacement de l'Agent2D a la souris
}

/*--------------------------------------------------------------------------*/
