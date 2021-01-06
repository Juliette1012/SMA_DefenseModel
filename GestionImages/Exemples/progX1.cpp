#include <iostream>
#include <stdio.h>

using namespace std;

#include "LibImages.h"

#include "traitement.h"

int main(void)
{
  ImageRVB imUn("../Images/Lena/lena24FullColor.ras");
  Image    imDeux("../Images/Lena/lena24FullColor.ras");

  ImageRVB im1(imUn.getNbRow(),imUn.getNbCol());
  Image    im2(imDeux.getNbRow(),imDeux.getNbCol());;

  XAffichage *Fim1    = new XAffichage(im1.getNbRow(),im1.getNbCol());
  Fim1->setLabel("im1");
  XAffichage *Fim2    = new XAffichage(im2.getNbRow(),im2.getNbCol());
  Fim2->setLabel("im2");

  int  indSauvegardeIm1=1;
  int  indSauvegardeIm2=1;
  char nomSauvegarde[2048];

  int  seuil = 127, oldSeuil = -1;

  Fim1->Afficher(im1);
  Fim1->XEvenement(im1);

  Fim2->Afficher(im2);
  Fim2->XEvenement(im2);

  cout << "s: sauvegarder" << endl;
  cout << "q: quitter" << endl;
  cout << "+/-: augmentation/dimunition du seuil" << endl;

  while (1)
    {
     char cim1, cim2;

     if (oldSeuil!=seuil) { seuillage(imDeux,im2,seuil);
                            seuillageRVB(imUn,im1,seuil);
                            oldSeuil=seuil;
     }

     Fim1->Afficher(im1);
     cim1=Fim1->XEvenement(im1);
     cim1 = tolower(cim1);

     Fim2->Afficher(im2);
     cim2=Fim2->XEvenement(im2);
     cim2 = tolower(cim2);

     if (cim1=='s') {
       snprintf(nomSauvegarde,sizeof(nomSauvegarde),
                "../Resultats/ImageIim1_%d.ppm",indSauvegardeIm1);
       im1.saveImage(nomSauvegarde);
       indSauvegardeIm1++;
     }

     if (cim2=='s') {
       snprintf(nomSauvegarde,sizeof(nomSauvegarde),
                "../Resultats/ImageIim2_%d.ppm",indSauvegardeIm2);
       im2.saveImage(nomSauvegarde);
       indSauvegardeIm2++;
     }

     if (cim1=='+' || cim2=='+') seuil = (seuil==255 ? 255 : seuil+1);
     if (cim1=='-' || cim2=='-') seuil = (seuil==0 ? 0 : seuil-1);

     if (cim1=='q' || cim2=='q') break;
    }

 delete(Fim1);
 delete(Fim2);

 return(0);
}
