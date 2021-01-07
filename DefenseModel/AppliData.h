#ifndef _APPLIDATA_H
#define _APPLIDATA_H

#include "Agent2D.h"

typedef struct
{
Scheduler* sched;
Agent2D*  obj;
//vector<AgentIA*> objIA;
Environnement* env;
Eprouvette* eprouvette;
int        autoscale;
int        pause;
} AppliData;

#endif // _APPLIDATA_H
