#include<stdio.h>
#include<stdlib.h>

int main (void){
	
	FILE *f = NULL;
	FILE *id_propres = NULL;
	char ligne[500], le_ID[100];
	int i = 0, y = 0, nb_id = 0, test_EOF, id;
	int ok = 0;
	char c;
	
	f = fopen("FR_category_id.json", "r");
	
	if (f == NULL)//Test d'ouverture du fichier
		{
			printf("Echec ouverture : fichier /FR_category_id.json/ impossible à ouvrir ou inexistant\n");
			return -1;
		}
	
	id_propres = fopen("IDs.txt", "r");//TEST du fichier IDs (Existant?->Ecraser?) ET Ecriture du titre des colones:"ID,Dénomination\n"
	
	if (id_propres != NULL)//Si le fichier existe déja, demande d'écrasement
		{
			fclose(id_propres);
			printf("Warning ! Le fichier /IDs.txt/ existe déja.\n");
			
			do{
				printf("Voulez vous le remplacer ? [o/n]");
				c = getc(stdin);
				getc(stdin);
				}while( c!='o' && c!='n' );
						
			if (c == 'n')
				{
					printf("Création du fichier anulée.\n");
					return 2;
				}
			else
				{
					id_propres = fopen("IDs.txt", "w");
					fprintf(id_propres,"ID,Dénomination\n");
				}
			
		}
	else
		{
			id_propres = fopen("IDs.txt", "w");
			fprintf(id_propres,"ID,Dénomination\n");
		}
		
	fclose(id_propres);
	
	do{//On compte le nombre d'ID présents dans le fichier en cherchant la chaine "id" qui apparais une fois par ID
		
		test_EOF = fscanf(f,"%s",ligne);
		
		if (ligne[0]=='"' && ligne [1]=='i' && ligne [2]=='d' && ligne [3]=='"')
			{
				nb_id++;
			}
		
		}while(test_EOF != -1);
	
	//ICI nb_id corespond au nombre d'ID présent dans le fichier//
	
	fseek(f, 0, SEEK_SET);//Replace au début du fichier
	
	//----------------------------------------------------------------//
	
	for (id = 0 ; id < nb_id ; id++)
		{
			i = 0;
			y = 0; 
			ok = 0;
			
			do{//Recherche de la ligne numéro ID
				
				fscanf(f,"%s",ligne);
				
				}while(ligne[0]!='"' || ligne [1]!='i' || ligne [2]!='d' || ligne [3]!='"');
				
			fscanf(f,"%s",ligne);//Ici ligne contient : "ID", ou ID est un entier corespondant à l'id
			
			while (ligne[y] != '\0')//Création de l'ID propre 
				{
					if (ligne[y] != '"' && ligne[y] != ',')
						le_ID[y-1] = ligne[y];
						le_ID[y]='\0';
					y++;
				}

			//ICI le_ID contient le numéro du ID//
			
			do{//Recherche du titre de l'ID
				
				fscanf(f,"%s",ligne);

				}while(ligne[0]!='"' || ligne [1]!='t' || ligne [2]!='i' || ligne [3]!='t' || ligne [4]!='l');
				
			y = 0;
			
			while(le_ID[y]!='\0')//Ajout de la virgule pour séparer le numéro et la dénomination
				y++;
			le_ID[y]=',';
			y++;
			
			fscanf(f,"%s",ligne);
			
			while(ok!=1)//Ajout de la dénomination
				{
					for( i = 0 ; ligne[i] != '\0' ; i++)
						{
							if (ligne[i] != '"' && ligne[i] != ',')
								{
									le_ID[y] = ligne[i];
									le_ID[y+1] = '\0';
									y++;
								}
						}
					
					if (ligne[i-1] == ',')
						ok++;
					else
						fscanf(f,"%s",ligne);
				}
			
			le_ID[y] = '\n';
			le_ID[y+1] = '\0';
			//printf("%s\n",le_ID);		
			//ICI le_ID contient N°ID,NOM_CATEGORIE\n//

			id_propres = fopen("IDs.txt", "a");
			
			if (id_propres == NULL)//Test d'ouverture du fichier
				{
					printf("Echec ecriture : fichier /IDs.txt/ impossible à ouvrir\nLe ID suivant n'a pas été écrit : %s", le_ID);
				}
			else
				{
					fprintf(id_propres, "%s", le_ID);//Ecriture du Id dans le fichier
					fclose(id_propres);
				}
	
	}
	
	//----------------------------------------------------------------//
	
	fclose(f);
	
	printf("Création du fichier /Numéro->ID/ Terminée avec succès!\n");
	
	return 0;
}
