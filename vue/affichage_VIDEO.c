/* Cette fonction affiche certains paramètres de la vidéo
 * Crée le 16/12/2018 / Dernière modification le 16/12/2018 par JulienDOL
 *
 * Fonction crée dans le cadre du projet S1/S2 d'Algorithmique ITII1, étude de Base de Donées en C
 * Projet par ROBIN Tangui et DOL julien	*/

 #include<stdio.h>
 #include "../model/data/struct.h"

#define JSON "model/data/FR_category_id.json"

 /*Paramètres affichés
  *
  * Titre
  * Chaine
  * Catégorie
  * Nb vues
  * Nb Like
  * Nb DisLike
  *
  * */

void affichage_VIDEO(VIDEO *V){
	 printf("Titre :             %s\n",V->titre);
	 printf("Chaine :            %s\n",V->chaine);
	 printf("Catégorie :         %d\n",V->categorie);
	 printf("Nombre de vues :    %d\n",V->vues);
	 printf("Nombre de Like :    %d\n",V->likes);
	 printf("Nombre de DisLike : %d\n",V->dislikes);
 }

 void afficheMenu(){
   printf("Que voulez vous faire ?\n");
   printf(" 1. Afficher la moyenne des vues\n");
   printf(" 2. Afficher la moyenne de like et dislikes\n");
   printf(" 0. Sortir\n-> ");
 }

void afficheErreurSaisiMenu(){
   printf("Entrée invalide. Veuillez selectionner une des options proposées\n ->");
 }

void afficheMoyenneVue(float moyenne){
  printf("Les vidéos en tendance ont en moyenne %d vues\n", (int)moyenne);
}

void afficheMoyenneLikeDislike(float moyLike, float moyDislike){
  printf("Les vidéos en tendance ont en moyenne %d \"j'aime\" et %d \"je n'aime pas\"\n", (int) moyLike, (int) moyDislike);
}
