#ifndef ROUTE_H_INCLUDED
#define ROUTE_H_INCLUDED

#include "include.h"


t_routes** ajouter_route(int* nbroutes, t_routes** routes, int** grille,int x, int y);

t_routes** initialiser_routes();

t_structRoute *AllouerStructRoute();

void SupprimerRoute(t_routes *route);

void SupprimerTableauRoutes(t_routes **routes, int tailleActuelle);

void SupprimerRouteSelectionnee(t_routes **tab, int x, int y, int tailleTableau, int **matrice);

int VerifierRouteSelectionne(t_routes *route, int x, int y);

void RemettreCaseLibreRoute(int **matrice, t_routes*);

#endif // ROUTE_H_INCLUDED

