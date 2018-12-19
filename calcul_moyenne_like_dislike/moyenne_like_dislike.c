/* Cette fonction ecris la moyenne de like et de dislike d'un tableau de vidéo donné 
 * Crée le 19/12/2018 / Dernière modification le 19/12/2018 par JulienDOL
 * 
 * Fonction crée dans le cadre du projet S1/S2 d'Algorithmique ITII1, étude de Base de Donées en C
 * Projet par ROBIN Tangui et DOL julien	*/
 
 /* Retours :
  * 
  * -1 si echec
  *  0 si OK
  * 
  * */
 
 #include "struct.h"
 
float moyenne_like_dislike (VIDEO *V, int nb, float *likes, float *dislikes){
	 
	 int i;
	 
	 if (nb<=0)
		return -1.0;
		
	*likes = 0.0;
	*dislikes = 0.0;
	 
	 for ( i = 0 ; i < nb ; i++)
		{
			*likes+=V[i].likes;
			*likes/=2.0;
			
			*dislikes+=V[i].dislikes;
			*dislikes/=2.0;
		}
		
	return 0.0;
 }
