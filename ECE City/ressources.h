#ifndef RESSOURCES_H_INCLUDED
#define RESSOURCES_H_INCLUDED

#include "include.h"

t_eau *CreerChateauDEau();

t_elec *CreerCentrale();

t_eau **AllouerTableauChateauDEau();

t_elec **AllouerTableauCentrale();

void SupprimerChateauDEau(t_eau *ChateauDEau);

void SupprimerTableauChateauDeau(t_eau **tab, int tailleActuelle);

void SupprimerCentrale(t_elec *centrale);

void SupprimerTableauCentrale(t_elec **centrale, int tailleActuelle);

t_eau **AugmenterTailleTableauChateauDEau(t_eau **tab, int *tailleActuelle, int *nbChat);

t_elec **AugmenterTailleTableauCentrales(t_elec **tab, int *tailleActuelle, int *nbCent);

//Allouer le t_eau ** et met le nombre de chateau à 0;
t_chateaux *AllouerChateaux();

//Alloue le t_elec ** et met le nombre de centrales à 0
t_centrales *AllouerCentrales();

t_eau **AjouterChateau(t_eau** tab, int *tailleActuelle, int *nbChat, int **grille);

t_elec **AjouterCentrale(t_elec **tab, int *tailleActuelle, int *nbCentre, int **grille);

BITMAP *ChargerImageChateau();

BITMAP *ChargerImageCentrale();

void SupprimerCentraleSelectionne(t_elec **, int, int, int, int **);

void SupprimerChateauSelectionne(t_eau **, int, int, int, int **);

int VerifierCentraleSelectionne(t_elec *hab, int x, int y);

void RemettreCaseLibreCentrale(int **matrice, t_elec *hab);

int VerifierChateauSelectionne(t_eau *hab, int x, int y);

void RemettreCaseLibreChateau(int **matrice, t_eau *hab);

void gestion_eau(t_eau eau,int**matrice, char** adjascence, t_batiments*batiment);

void gestion_elec(t_elec elec,int**matrice, char** adjascence, t_batiments*batiment);
#endif // RESSOURCES_H_INCLUDED
