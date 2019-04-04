snake: liste.o fichier.o gestion.o decor.o
	gcc liste.o fichier.o gestion.o decor.o -o snake
liste.o : liste.c liste.h include.h
	gcc -c liste.c
fichier.o : fichier.c fichier.h include.h
	gcc -c fichier.c
gestion.o : gestion.c gestion.h include.h
	gcc -c gestion.c
decor.o : decor.c decor.h include.h
	gcc -c decor.c


