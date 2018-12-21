#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "../data/struct.h"
#include "../id_vers_cat/ID_vers_CAT.h"
#include "accessdata.h"
#include "../../vue/affichage_VIDEO.h"


#define TAILLE_LIGNE 5000
#define JSON "model/data/FR_category_id.json"

/**
  nomf -> fichier CSV a ouvrir. La fonction ne peut que lire une seule version de FRvideo.CSV au 18/12/18
  tabVideo -> poiteur de retour qui pointera sur le tableau de VIDEO
  nbElem -> valeur de retour qui contiendra le nombre d'element du tableau tabVideo
**/
void csvToVideo(char * nomf, VIDEO * tab, int nbElem){
  //initialisation des valeur de retour; permet d'enlever les Warning
  nbElem = 0;
  FILE * f = NULL;
  f = fopen(nomf, "r");
  if(f!=NULL){
    char * ret; //Valeur de retour de la lecture de la ligne -> si ret == NULL alors la lecture est arrivée au bout du fichier
    char * rest; //Reste de la ligne après un strtok_r
    //int idCat;
    int nbLigne = compNbLines(f);
    char * ligne = malloc(sizeof(char)*TAILLE_LIGNE); //Ligne lue. Definie très grande pour contenir beaucoup de caractère mais réutilisé à chaque ligne
    char * att = malloc(sizeof(char)*128); //variable stockant le resultat de la lecture d'un ATTribut
    fgets(ligne, sizeof(char)*TAILLE_LIGNE, f); //lecture de la ligne, la première ligne étant l'en-tête du CSV, on passe
    ret = fgets(ligne, sizeof(char)*TAILLE_LIGNE, f); //lecture de la première ligne de valeur

    for(int i = 0; ret != NULL ; i++){
      /* lecture dans la structure */
      ////printf("vidid\n");
      //vid_id
      getChamp(ligne,att);
      ////printf("trend\n");
      //trending_date
      getChamp(ligne,att);
////printf("title\n");
      //title
      getChamp(ligne,att);
      strcpy(tab[i].titre,att);
      //printf("titre : %s\n", tab[i].titre);
////printf("chan\n");
      //channel_title
      getChamp(ligne,att);
      strcpy(tab[i].chaine,att);
      ////printf("cat\n");
      //category_id
      getChamp(ligne,att);
      //strcpy(tab[i].categorie,att);
      tab[i].categorie = atoi(att);
      ////printf("%d\n", idCat);
      //ID_vers_CAT(idCat, att, JSON);
      //strcpy(tab[i].categorie,idCat);
////printf("pubtime\n");
      //publish_time
      getChamp(ligne,att);
      //printf("tags %s\n", ligne);
      //tags
      strcpy(tab[i].motcles,strtok_r(ligne,",",&rest));
      strcpy(ligne,rest);
      //printf("view %s\n", ligne);
      //views
      getChamp(ligne,att);
      tab[i].vues = atoi(att);
      //printf("-->%d %d\n", tab[i].vues, atoi(att));
      //likes
      getChamp(ligne,att);
      tab[i].likes = atoi(att);
      ////printf("dis\n");
      //dislikes
      getChamp(ligne,att);
      tab[i].dislikes = atoi(att);
      ////printf("comment\n\n\n");
      //comment_count
      getChamp(ligne,att);
      tab[i].commentaires = atoi(att);
      //printf("%d\n", tab[i].vues);
      //affichage_VIDEO(tab+i);
      ret = fgets(ligne, sizeof(char)*TAILLE_LIGNE, f);//lecture de la ligne suivante
    }
    //Preparation des valeurs de retour
    nbElem = nbLigne;
    free(att);
    fclose(f);
  }
  else{
    //printf("Le fichier \"%s\" n'est pas trouvé\n", nomf);
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
