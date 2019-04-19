#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDED

#include "include.h"


void lancerToutAllegro();

BITMAP* creation_calque();


void afficher_route(int x, int y, int** grille, BITMAP **bibroute);

void remplissage_calque_route(int** grille, t_routes** routes, int nbroutes, BITMAP **bibroute);

void dessin_matrice(BITMAP* calque);

void AfficherBatiments(BITMAP **tab, t_batiments *batiments);

void InitialiserCalques();

void AfficherRessources(t_chateaux *chat, t_centrales *elec);

void affichage_global(BITMAP*herbe, int modeaffichage,BITMAP* pointeur);

void choixmodeaffichage(int* mode);

#endif // AFFICHAGE_H_INCLUDED
