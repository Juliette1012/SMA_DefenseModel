#include <iostream>             // Fichier ex.cpp

using namespace std;

#include "LibImages.h"

int main(void)
{
 ImageRVB im("../Images/Lena/lena24FullColor.ras");

 XAffichage *Fim = new XAffichage(im.getNbRow(),im.getNbCol());
 Fim->setLabel("lena24FullColor.ras");

 while (1)
 {
  char cim;

  Fim->Afficher(im);
  cim=Fim->XEvenement(im);
  cim = tolower(cim);

  if (cim=='q')  break;
 }

 delete(Fim);

 return 0;
}
