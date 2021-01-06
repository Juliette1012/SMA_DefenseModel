#ifndef  _DECOR_H_
#define  _DECOR_H_

#include <set>
#include "Object2D.h"

using namespace std;

typedef set<Object2D*> Decor;

extern Decor decor;       // Contient uniquement des Object2D pas des Agent2D !

extern void addDecor(Object2D* obj2d);    // Ajouter un element du decor
extern void removeDecor(Object2D* obj2d); // Enlever un element du decor
extern bool isInDecor(Object2D* obj2d); // Testet si un objet est dans le decor

#endif //_DECOR_H_
