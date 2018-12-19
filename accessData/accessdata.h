/**
  nomf -> fichier CSV a ouvrir. La fonction ne peut que lire une seule version de FRvideo.CSV au 18/12/18
  tabVideo -> poiteur de retour qui pointera sur le tableau de VIDEO
  nbElem -> valeur de retour qui contiendra le nombre d'element du tableau tabVideo
**/
void csvToVideo(char * nomf, VIDEO * tabVideo, int nbElem);

/**
  Fontion permettant d'obtenir la première valeur (attribut) de la ligne
  Retourne la ligne sans l'attribut lu et l'attribut lu est retourné dans att
  ligne -> in : ligne où lire l'attribut ; out : reste de la ligne sans l'attribut lu et le caractère séparateur qui le suis
  att -> in : PAS DE CONDITION ; out : attribut lu
**/
void getChamp(char * ligne, char * att);

/**
  Permet de compter ne nombre de ligne du fichié passé
**/
int compNbLines(FILE * file);
