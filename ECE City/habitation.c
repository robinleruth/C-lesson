#include "include.h"

t_habitation *CreerHabitation()
{
    t_habitation *hab = NULL;

    hab = malloc(1*sizeof(t_habitation));
    if(hab == NULL) exit(EXIT_FAILURE);

    hab->coord = malloc(sizeof(t_position));
    if(hab->coord == NULL) exit(EXIT_FAILURE);

    hab->coord->x = mouse_x/20;
    hab->coord->y = mouse_y/20;
    hab->population = 0;
    hab->stade = 0;
    hab->temps_initial = time(NULL);
    hab->eau=0;
    hab->elec=0;

    return hab;
}

void SupprimerHabitation(t_habitation* hab)
{
    free(hab);
    hab = NULL;
}

void ChangerStade(t_habitation *hab, int etat)
{
    if(etat)
        hab->stade++;
    else
    {
        if(hab->stade != RUINE)
        {
            hab->stade--;
        }
    }
    switch(hab->stade)
    {
    case TERRAIN_VAGUE:
        hab->population = 0;
        break;
    case CABANE:
        hab->population = 10;
        break;
    case MAISON:
        hab->population = 50;
        break;
    case IMMEUBLE:
        hab->population = 100;
        break;
    case GRATTE_CIEL:
        hab->population = 1000;
        break;
    }
}
