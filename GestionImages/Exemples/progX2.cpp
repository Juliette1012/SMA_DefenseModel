#include <iostream>
#include <stdio.h>

using namespace std;

#include "LibImages.h"

int main(void)
{
  ImageRVB im;

  XAffichage *Fim;

  int nbRow=300;
  int nbCol=600;
  int l=0,c=0;
  octet valR=0;
  octet valV=100;
  octet valB=200;

  int  indSauvegardeIm=1;
  char nomSauvegarde[2048];

  im.setImageSize(nbRow,nbCol);

  Image& R = im.getR();
  Image& V = im.getV();
  Image& B = im.getB();

  for(l=0;l<nbRow;l++)
  {
   for(c=0;c<nbCol;c++)
   {
    R[l][c] = valR;      // On peut aussi
    V[l][c] = valV;      // im.writePix(l,c,valR,valV,valB);
    B[l][c] = valB;      // ...
   }
   if (valR==255) valR=0;
   else           valR++;
   if (valV==255) valV=0;
   else           valV++;
   if (valB==255) valB=0;
   else           valB++;
  }

  Fim = new XAffichage(nbRow,nbCol);

  Fim->Afficher(im);

  printf("q: quitter\n");
  printf("s: sauver\n");

  while (1)
    {
     char cim;

     Fim->Afficher(im);
     cim=Fim->XEvenement(im);
     if (cim=='s' || cim=='S') {
       snprintf(nomSauvegarde,sizeof(nomSauvegarde),
                "../Resultats/ImageI%d.ras",indSauvegardeIm);
       im.saveImage(nomSauvegarde);
       indSauvegardeIm++;
     }

     if (cim=='q' || cim=='Q') break;
    }

 delete(Fim);

 return(0);
}
