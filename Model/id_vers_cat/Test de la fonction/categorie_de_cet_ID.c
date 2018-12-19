#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main (void){
	//---//
	int LE_ID = 35;
	char LA_Categorie[64];
	char chemin_fichier[32];
	scanf("%s",chemin_fichier);
	//---//Paramètres de la fonction 
	
	FILE *f = NULL;
	char ligne[32], num_ID[4];
	int test_EOF, find_ID = 0,i,y, TEST_ligne_OK = 0;
	
	f = fopen(chemin_fichier, "r");
	
	if (f == NULL)
		{
			printf("Ouverture du fichier /%s/ impossible ou le fichier est inexistant",chemin_fichier);
			return -1;
		}
	
	fscanf(f, "%s", ligne);//La première ligne ne nous interesse pas
	
	do{//On parcours du fichier jusqu'à la fin
		
		test_EOF = fscanf(f,"%s",ligne);
		
		//Test de la conformité de la ligne avant son traitement
		for(i=0 ; ligne[i]!='\n' || i < 100 ; i++)
			{
				if ( ligne[i] == ',' || ligne[i] == '\n')
					{
						TEST_ligne_OK++;
					}
			}
		
		if (TEST_ligne_OK != 2)
			{
				//printf("%d", TEST_ligne_OK);
				printf("Fichier éroné! Impossible de le lire. (Source du problème Ligne NC)");
				return -3;//La ligne n'est pas valide
			}
		else
			TEST_ligne_OK = 0;//La ligne est valide

		for(i = 0 ; ligne[i]!=',' ; i++)
			{
				num_ID[i] = ligne[i];
			}
			
		num_ID[i] = '\0';
		/*
		for (y = 0 ; num_ID[y] != '\0' ; y++)//Test de num_ID -> bien constitué de nombres !!Ne fonctionne pas!!
			{
				if ((num_ID[y] < '0' || num_ID[y] > '9') && num_ID[y] != '\0')
					{
						printf("Fichier éroné! Impossible de le lire. (Source du problème ID NC)");
						return -3;//La ID lu n'est pas valide (pas que des "entiers")
					}
			}*/
		
		find_ID = atoi(num_ID);

		//ICI find_ID est le numero de l'ID lorque l'on parcours le fichier//
		
		if (find_ID == LE_ID)//Si l'ID correspond à celui du fichier 
			{
				i++;
				y=0;
				while(ligne[i] != '\0')
					{
						LA_Categorie[y] = ligne[i];
						y++;
						i++;
					}
				LA_Categorie[y] = '\0';
				printf("%s",LA_Categorie);
				fclose(f);
				return 0;//Fin la catégorie a été trouvée
			}
		
		}while(test_EOF > -1);
	
	//Si test_EOF == -2 la categorie n'a pas été trouvée
	printf("La catégorie corespondant a l'ID %d n'a pas été trouvée!", LE_ID);
	
	fclose(f);
	
	return -2;
}
