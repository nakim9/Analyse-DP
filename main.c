#include <stdio.h>
#include <stdlib.h>

#include "model/data/struct.h"
#include "model/acces_donnee/accessdata.h"
#include "model/calcul_moyenne_like_dislike/moyenne_like_dislike.h"
#include "model/calcul_moyenne_vues/moyenne_vues.h"
#include "model/creation_fichier_id/generation_fichier_ID.h"
#include "model/id_vers_cat/ID_vers_CAT.h"
#include "vue/affichage_VIDEO.h"

#define T_AVG 1000

void menu();

void moyenneVues(VIDEO * videos);

void moyenneLikeDislike(VIDEO * videos);

int main(void) {
  char nomf[128] ="model/data/FRvideos.csv";
  FILE * f = fopen(nomf,"r");
  int nbElem = compNbLines(f);
  fclose(f);
  VIDEO * tabVideo = malloc(sizeof(VIDEO)*nbElem);
  csvToVideo(nomf,tabVideo,nbElem);
  for(int i = 0; i <10; i++)
    affichage_VIDEO(tabVideo+i);
  menu(tabVideo);
  return 0;
}

void menu(VIDEO * videos){
  int choixMenu;
  do{
    afficheMenu();
    scanf("%d",&choixMenu);
    while(choixMenu != 0 && choixMenu != 1 && choixMenu != 2 && choixMenu != 3 && choixMenu != 4){
      afficheErreurSaisiMenu();
      scanf("%d",&choixMenu);
    }
    switch (choixMenu) {
      case 1:
      moyenneVues(videos);
      break;

      case 2:
      moyenneLikeDislike(videos);
      break;

      default :
      choixMenu = 0;
    }
  }while(choixMenu != 0);
}

void moyenneVues(VIDEO * videos){
  float moyenne = moyenne_vues(videos,T_AVG);
  afficheMoyenneVue(moyenne);
}

void moyenneLikeDislike(VIDEO * videos){
  float moyLike, moyDislike;
  moyenne_like_dislike(videos,T_AVG, &moyLike, &moyDislike);
  afficheMoyenneLikeDislike(moyLike,moyDislike);
}
