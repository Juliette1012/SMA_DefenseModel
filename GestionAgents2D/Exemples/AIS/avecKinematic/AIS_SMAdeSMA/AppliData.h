#ifndef _APPLIDATA_H
#define _APPLIDATA_H

#include <set>

#include "MAS.h"
#include "Eprouvette.h"

using namespace std;

typedef struct
{
Scheduler*      sched;
Eprouvette*     eprouvette;
int             autoscale;
int             pause;
} AppliData;

#endif // _APPLIDATA_H
