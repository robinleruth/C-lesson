#ifndef GESTION_H_INCLUDED
#define GESTION_H_INCLUDED

#include "include.h"

void DeterminerCoordonneesAleatoires(int *x, int *y);
void AfficherElements(Liste *liste, int matrice[ABSCISSE_MAX][ORDONNEE_MAX], int *nbrePommes, int score);
void GererEvenement(Liste *liste, char *direction, int matrice[ABSCISSE_MAX][ORDONNEE_MAX]);
void InstructionAutonome(Liste *liste, char *direction, int matrice[ABSCISSE_MAX][ORDONNEE_MAX]);
void GestionCollision(char *c, int *x, int *y, int matrice[ABSCISSE_MAX][ORDONNEE_MAX]);
void MettreSnakeMatrice(Liste *liste, int matrice[ABSCISSE_MAX][ORDONNEE_MAX]);
void CreerPomme(Liste *liste, int matrice[ABSCISSE_MAX][ORDONNEE_MAX], int *nbrePommes);
int AfficherPomme(int nbreDePommes, int matrice[ABSCISSE_MAX][ORDONNEE_MAX]);
void NouvelElement(Liste *liste, char *direction, int matrice[ABSCISSE_MAX][ORDONNEE_MAX]);
void gotoligcol( int lig, int col );

#endif // GESTION_H_INCLUDED
