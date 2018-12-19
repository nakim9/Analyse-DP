/* Cette fonction affiche certains paramètres de la vidéo
 * Crée le 16/12/2018 / Dernière modification le 16/12/2018 par JulienDOL
 * 
 * Fonction crée dans le cadre du projet S1/S2 d'Algorithmique ITII1, étude de Base de Donées en C
 * Projet par ROBIN Tangui et DOL julien	*/
 
 #include<stdio.h>
 #include "struct.h"
 
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
	 printf("Catégorie :         %s\n",V->categorie);
	 printf("Nombre de vues :    %d\n",V->vues);
	 printf("Nombre de Like :    %d\n",V->likes);
	 printf("Nombre de DisLike : %d\n",V->dislikes);
 }
