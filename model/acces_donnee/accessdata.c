#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "../data/struct.h"
#include "../id_vers_cat/ID_vers_CAT.h"
#include "accessdata.h"

#define TAILLE_LIGNE 5000
#define JSON "model/data/FR_category_id.json"

/**
  nomf -> fichier CSV a ouvrir. La fonction ne peut que lire une seule version de FRvideo.CSV au 18/12/18
  tabVideo -> poiteur de retour qui pointera sur le tableau de VIDEO
  nbElem -> valeur de retour qui contiendra le nombre d'element du tableau tabVideo
**/
void csvToVideo(char * nomf, VIDEO * tabVideo, int nbElem){
  //initialisation des valeur de retour; permet d'enlever les Warning
  tabVideo = NULL;
  nbElem = 0;
  FILE * f = NULL;
  f = fopen(nomf, "r");
  if(f!=NULL){
    char * ret; //Valeur de retour de la lecture de la ligne -> si ret == NULL alors la lecture est arrivée au bout du fichier
    char * rest; //Reste de la ligne après un strtok_r
    int idCat;
    int nbLigne = compNbLines(f);
    VIDEO * tab = malloc(sizeof(VIDEO)*nbLigne); //Tableau qui contiendra toutes les vidéos
    char * ligne = malloc(sizeof(char)*TAILLE_LIGNE); //Ligne lue. Definie très grande pour contenir beaucoup de caractère mais réutilisé à chaque ligne
    char * att = malloc(sizeof(char)*128); //variable stockant le resultat de la lecture d'un ATTribut
    fgets(ligne, sizeof(char)*TAILLE_LIGNE, f); //lecture de la ligne, la première ligne étant l'en-tête du CSV, on passe
    ret = fgets(ligne, sizeof(char)*TAILLE_LIGNE, f); //lecture de la première ligne de valeur

    for(int i = 0; ret != NULL ; i++){
      /* lecture dans la structure */

      //vid_id
      getChamp(ligne,att);

      //trending_date
      getChamp(ligne,att);

      //title
      getChamp(ligne,att);
      strcpy(tab[i].titre,att);

      //channel_title
      getChamp(ligne,att);
      strcpy(tab[i].chaine,att);

      //category_id
      getChamp(ligne,att);
      idCat = atoi(att);
      ID_vers_CAT(idCat, att, JSON);
      strcpy(tab[i].categorie,att);

      //publish_time
      getChamp(ligne,att);

      //tags
      strcpy(tab[i].motcles,strtok_r(ligne,",",&rest));
      strcpy(ligne,rest);

      //views
      getChamp(ligne,att);
      tab[i].vues = atoi(att);

      //likes
      getChamp(ligne,att);
      tab[i].likes = atoi(att);

      //dislikes
      getChamp(ligne,att);
      tab[i].dislikes = atoi(att);

      //comment_count
      getChamp(ligne,att);
      tab[i].commentaires = atoi(att);

      ret = fgets(ligne, sizeof(char)*TAILLE_LIGNE, f);//lecture de la ligne suivante
    }
    //Preparation des valeurs de retour
    tabVideo = tab;
    nbElem = nbLigne;
    free(tab);
    free(att);
    fclose(f);
  }
  else{
    printf("%s%s%s\n", "Le fichier \"", nomf, "\" n'est pas trouvé");
  }
}

/**
  Fontion permettant d'obtenir la première valeur (attribut) de la ligne
  Retourne la ligne sans l'attribut lu et l'attribut lu est retourné dans att
  ligne -> in : ligne où lire l'attribut ; out : reste de la ligne sans l'attribut lu et le caractère séparateur qui le suis
  att -> in : PAS DE CONDITION ; out : attribut lu
**/
void getChamp(char * ligne, char * att){
  char * rest;
  strtok_r(ligne,",",&rest);
  strcpy(att,ligne);
  if(att != NULL && *att == '"'){ //Si l'attribut lu commence par une virgule, l'attribut doit finir par => ",
    int len = strlen(att); //On calcul sa longueur pour determiner la position du dernier caractère
    while(att[len-1] != '"'){ //Si le dernier char n'est pas un guillement
      strcat(att,strtok_r(NULL,",",&rest)); //On lit jusqu'à la prochaine virgule en concatenant les chaines
      len = strlen(att);//On cherche a nouveau le dernier caractère (un guillemet)
    } //attribut fini par un guillemet
    att[len-1] = '\0'; //On supprime le dernier caractère
  }
  strcpy(ligne,rest);
}

/**
  Permet de compter ne nombre de ligne du fichié passé
**/
int compNbLines(FILE * file){
  int i = 0;
  char ch[TAILLE_LIGNE];
  char * ret;
  do{
    ret = fgets(ch,TAILLE_LIGNE,file);
    i++;
  }while(ret != NULL);
  fseek(file,0,SEEK_SET);
  return i-1;
}
