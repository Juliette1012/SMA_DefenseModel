#include <iostream>

using namespace std;

#include "LibImages.h"

#include "fill.h"

int main(void)
{
                      // Attention, parfois avec xfig, l'export en "image"
  Image im("f.ppm");  // donne des formes "trouees" ==> augmenter l'epaisseur
                      // du trait

  XAffichage *Fim    = new XAffichage(im.getNbRow(),im.getNbCol());

  Fim->Afficher(im);
  Fim->XEvenement(im);

  cout << "q: quitter" << endl;

  floodFillScanlineStack(im,
                         im.getNbRow()/2, // Ici la forme est au
                         im.getNbCol()/2, // centre de l'image !
                         0, 255);

  while (1)
    {
     char cim;

     Fim->Afficher(im);
     cim=Fim->XEvenement(im);
     cim = tolower(cim);

     if (cim=='q') break;
    }

 delete(Fim);

 return(0);
}
