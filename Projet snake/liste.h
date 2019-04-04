#ifndef LISTE_H_INCLUDED
#define LISTE_H_INCLUDED

#include "include.h"

Liste *InitialisationListe(int *abscisse, int *ordonnee, int matrice[ABSCISSE_MAX][ORDONNEE_MAX]);
void AjouterElementFin(Liste * liste, int *abscisse, int *ordonnee, int matrice[ABSCISSE_MAX][ORDONNEE_MAX]);
void SupprimerListe(Liste *liste);
void SupprimerElementFin(Liste *liste, int matrice[ABSCISSE_MAX][ORDONNEE_MAX]);
void AjouterElementDebut(Liste *liste, int *abscisse, int *ordonnee, int matrice[ABSCISSE_MAX][ORDONNEE_MAX]);

#endif // LISTE_H_INCLUDED
