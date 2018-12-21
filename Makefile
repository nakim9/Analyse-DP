CC=gcc
FLAGS=-Wall
EXE=main

all : $(EXE) clean

main: accessdata.o moyenne_vues.o moyenne_like_dislike.o generation_fichier_ID.o ID_vers_CAT.o affichage_VIDEO.o main.o
	$(CC) -o $@ $^

moyenne_vues.o: model/calcul_moyenne_vues/moyenne_vues.c
	$(CC) -o $@ -c $< $(FLAGS)

moyenne_like_dislike.o: model/calcul_moyenne_like_dislike/moyenne_like_dislike.c
	$(CC) -o $@ -c $< $(FLAGS)

generation_fichier_ID.o: model/creation_fichier_id/generation_fichier_ID.c
	$(CC) -o $@ -c $< $(FLAGS)

ID_vers_CAT.o: model/id_vers_cat/ID_vers_CAT.c
	$(CC) -o $@ -c $< $(FLAGS)

accessdata.o: model/acces_donnee/accessdata.c model/id_vers_cat/ID_vers_CAT.c model/data/struct.h
	$(CC) -o $@ -c $< $(FLAGS)

affichage_VIDEO.o: vue/affichage_VIDEO.c
	$(CC) -o $@ -c $< $(FLAGS)

main.o: main.c model/acces_donnee/accessdata.c
	$(CC) -o $@ -c $< $(FLAGS)

clean :
	rm -rf *.o
	rm -rf model/*/*.o
	rm -rf vue/*.o
