/*----------------------------------------------------------------------------
  prg.cpp
----------------------------------------------------------------------------*/

#include "Agent2D.h"

/////////////////// Pour la co-existence Agent2D - Object2D ///////////////////
//                                                                           //
#include "Decor.h"           // *** AJOUT ..! ***                            //
#include "Object2D.h"        // *** AJOUT ..! ***                            //
//                                                                           //
// typedef set<Object2D*> Decor;                                             //
//                                                                           //
// extern Decor decor;                      Contient uniquement des Object2D,//
//                                          pas des Agent2D !                //
// extern void addDecor(Object2D* obj2d);                                    //
// extern void removeDecor(Object2D* obj2d);                                 //
// extern bool isInDecor(Object2D* obj2d); ... pour interaction !            //
//                                             voir graphic_selectCallback   //
//                                             et graphic_keyPressCallback   //
//                                             et graphic_mouseDragCallback  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////


/*-------- Application -----------------------------------------------------*/

/*---- application specific data ----*/

#include "AppliData.h"

/*
typedef struct
{
Scheduler* sched;
Agent2D*   agt;
Object2D*  obj;            // *** AJOUT ..! ***
int        autoscale;
int        pause;
} AppliData;
*/

void deleteAppliData(AppliData * data)
{
 removeDecor(data->obj);  // *** AJOUT ..! ***
 delete(data->obj);
 delete(data->agt);
 delete(data->sched);
 delete(data);
}

void help(void)
{
 cout << "*********************************************"<< endl;
 cout << "help"                                         << endl;
 cout << "----"                                         << endl;
 cout << "Actions clavier AVEC objet selectionne:"      << endl;
 cout << "- n : obtenir le nom d'un Agent2D"            << endl;
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
data->sched->setRealTimeMode(true);

/*---- initialize Agent2D  ----*/

data->agt=new Agent2D();
data->agt->square(10,0);
data->agt->setAngularVelocity(1);

data->obj=new Object2D();           // *** AJOUT ..! ***
addDecor(data->obj);                // *** AJOUT ..! ***
data->obj->square(15,0);            // *** AJOUT ..! ***
data->agt->attachTo(*data->obj);    // *** AJOUT ..! ***

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

if (isInDecor((Object2D*)agt2d))                 // *** AJOUT ..! ***
{// Interaction avec les Object2D du decor       // *** AJOUT ..! ***
 Object2D* obj2d=(Object2D*)agt2d;               // *** AJOUT ..! ***
 obj2d->onSelection();                           // *** AJOUT ..! ***
 return;                                         // *** AJOUT ..! ***
}                                                // *** AJOUT ..! ***

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
 if(!strcmp(key,"Left"))
  {
  graphic_mouseDragCallback(data->agt,
                            -0.5,0.0,userData); // simulate mouse drag
  }
 else if(!strcmp(key,"Right"))
  {
  graphic_mouseDragCallback(data->agt,
                            0.5,0.0,userData); // simulate mouse drag
  }
 else if(!strcmp(key,"h")||!strcmp(key,"H"))
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
 else { fprintf(stderr,"Viewer key <%s>\n",key); }
 return;
}
        //  ET donc ici, interaction clavier AVEC un objet selectionne

if (isInDecor((Object2D*)agt2d))                 // *** AJOUT ..! ***
{// Interaction avec les Object2D du decor       // *** AJOUT ..! ***
 Object2D* obj2d=(Object2D*)agt2d;               // *** AJOUT ..! ***
 obj2d->onKeyPress(key);                         // *** AJOUT ..! ***
 return;                                         // *** AJOUT ..! ***
}                                                // *** AJOUT ..! ***

if (!strcmp(key,"n")||!strcmp(key,"N"))
{
 cout << agt2d->getName() << endl;
 return;
}

agt2d->onKeyPress(key);
}

void
graphic_mouseDragCallback(Agent2D * agt2d,
                          double dx,
                          double dy,
                          void * userData)
{
AppliData * data=(AppliData *)userData;
(void)data;

if (isInDecor((Object2D*)agt2d))                 // *** AJOUT ..! ***
{// Interaction avec les Object2D du decor       // *** AJOUT ..! ***
 Object2D* obj2d=(Object2D*)agt2d;               // *** AJOUT ..! ***
 obj2d->onMouseDrag(dx,dy);                      // *** AJOUT ..! ***
 return;                                         // *** AJOUT ..! ***
}                                                // *** AJOUT ..! ***

agt2d->onMouseDrag(dx,dy); // Par defaut : deplacement de l'Agent2D a la souris
}

/*--------------------------------------------------------------------------*/
