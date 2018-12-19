/* Cette fonction retourne la moyenne de vue des vidéo du tablea de vidéo passé en paramètre
 * Crée le 19/12/2018 / Dernière modification le 19/12/2018 par JulienDOL
 * 
 * Fonction crée dans le cadre du projet S1/S2 d'Algorithmique ITII1, étude de Base de Donées en C
 * Projet par ROBIN Tangui et DOL julien	*/
 
 /*Retour 
  * 
  * -1 si echec
  *  la moyenne si OK
  * 
  * */
 
 #include "../data/struct.h"
 
 float moyenne_vues (VIDEO *V, int nb){
	 
	 float moy = 0;
	 int i;
	 
	 if (nb<=0)
		return -1.0;
	 
	 for ( i = 0 ; i < nb ; i++)
		{
			moy+=V[i].vues;
			moy/=2;
		}
	 
	 return moy;
 }
