#include "include.h"

t_routes** initialiser_routes()
{
    int i;

    t_routes** route=(t_routes**)malloc(10*sizeof(t_routes*));

    for(i=0; i<10; i++)
    {
        route[i] = malloc(sizeof(t_routes));
        if(route[i] == NULL) exit(EXIT_FAILURE);

    }
    return route;
}

t_structRoute *AllouerStructRoute()
{
    t_structRoute *tmp = NULL;

    tmp = malloc(1*sizeof(t_structRoute));
    if(tmp == NULL) exit(EXIT_FAILURE);

    tmp->routes = initialiser_routes();
    tmp->nbroute = 0;
    tmp->bibliroute = ChargerImage("route");

    return tmp;
}

t_routes** ajouter_route(int *nbroutes, t_routes** routes, int** grille,int x, int y)
{
    int i;
    if((*nbroutes%10==0)&&(*nbroutes!=0))
    {
        routes=(t_routes**)realloc(routes, (*nbroutes+10)*sizeof(t_routes)) ;
        for(i=*nbroutes; i<*nbroutes+10; i++)
        {
            routes[i] = malloc(1*sizeof(t_routes));
        }
    }

    //if(routes[*nbroutes] == NULL) exit(EXIT_FAILURE);
    routes[*nbroutes]->coord = malloc(sizeof(t_position));
    routes[*nbroutes]->coord->x=x/20;
    routes[*nbroutes]->coord->y=y/20;
    grille[x/20][y/20]=ROUTE ;
    *nbroutes = *nbroutes + 1;
    return routes;
}

void SupprimerRoute(t_routes *route)
{
    free(route);
    route = NULL;
}

void SupprimerTableauRoutes(t_routes **routes, int tailleActuelle)
{
    int i;
    for(i=0; i<tailleActuelle; i++)
    {
        if(routes[i] != NULL)
        {
            SupprimerRoute(routes[i]);
        }
    }
    free(routes);
    routes = NULL;
}


void SupprimerRouteSelectionnee(t_routes **tab, int x,int y, int tailleActuelle, int **matrice)
{
    int i;
    int vrai = 0;
    for(i=0; i<tailleActuelle; i++)
    {
        if(tab[i] != NULL)
        {
            vrai = VerifierRouteSelectionne(tab[i], x, y);
            if(vrai == 1) break;
        }
    }

    if(vrai)
    {
        RemettreCaseLibreRoute(matrice, tab[i]);
        SupprimerRoute(tab[i]);
    }
    tab[i] = NULL;
}

int VerifierRouteSelectionne(t_routes *route, int x,int y)
{
    if(route->coord->x == x/20 && route->coord->y == y/20) return 1;
    else return 0;
}

void RemettreCaseLibreRoute(int **matrice, t_routes* route)
{
    matrice[route->coord->x][route->coord->y] = -1;
}
