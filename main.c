#include <stdio.h>
#include <stdlib.h>

#include "model/data/struct.h"
#include "model/acces_donnee/accessdata.h"
#include "model/calcul_moyenne_like_dislike/moyenne_like_dislike.h"
#include "model/calcul_moyenne_vues/moyenne_vues.h"
#include "model/creation_fichier_id/generation_fichier_ID.h"
#include "model/id_vers_cat/ID_vers_CAT.h"
#include "vue/affichage_VIDEO.h"

int main(void) {
  char nomf[128] ="model/data/FRvideos.csv";
  int nbElem = 0;
  VIDEO * tabVideo;
  csvToVideo(nomf,tabVideo,nbElem);
  return 0;
}
