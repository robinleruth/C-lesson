#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"

Liste *initialisation()
{
    Liste *liste = malloc(sizeof(*liste));
    Element *element = malloc(sizeof(*element));

    if((liste == NULL) || (element == NULL))
    {
        printf("Erreur d'allocation de la mémoire : ");
        exit(EXIT_FAILURE);
    }

    element->nombre = 0;
    element->suivant = NULL;
    liste->premier = element;

    return liste;
}

void insertion(Liste *liste, int nvNombre)
{
    /* Création d'un nouvel élément*/
    Element *nouveau = malloc(sizeof(*nouveau));
    if((liste == NULL) || (nouveau == NULL))
    {
        printf("Erreur d'allocation de mémoire : ");
        exit(EXIT_FAILURE);
    }

    /* Insertion du nouvel élément en début de liste */
    nouveau->nombre = nvNombre;
    nouveau->suivant = liste->premier;
    liste->premier = nouveau;
}

void suppression(Liste *liste)
{
    if(liste == NULL)
    {
        printf("Le pointeur est NULL");
        exit(EXIT_FAILURE);
    }

    if(liste != NULL)
    {
        Element *aSupprimer = liste->premier;
        liste->premier = liste->premier->suivant;
        free(aSupprimer);
    }
}

void AfficherListe(Liste *liste)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Element *actuel = liste->premier;

    while(actuel != NULL)
    {
        printf("%d -> ", actuel->nombre);
        actuel = actuel->suivant;
    }
    printf("NULL");
}
