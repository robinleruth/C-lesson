#include <stdio.h>
#include <stdlib.h>
#include "liste_chainee.h"

Liste *InitialisationListe()
{
    Liste *liste = malloc(sizeof(*liste));
    Element *element = malloc(sizeof(*element));
    if((liste == NULL) || (element == NULL))
    {
        exit(EXIT_FAILURE);
    }
    element->nombre = 0;
    element->suivant = NULL;
    liste->premier = element;
    liste->nbreElement = 1;
    return liste;
}

void AjouterElementDebut(Liste *liste, int nvNombre)
{
    Element *nouveau = malloc(sizeof(*nouveau));
    if(liste == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }
    nouveau->nombre = nvNombre;
    nouveau->suivant = liste->premier;
    liste->premier = nouveau;
    liste->nbreElement++;
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

void SupprimerListe(Liste *liste)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }
    Element *temp = liste->premier;
    while(temp != NULL)
    {
        Element *aSupprimer = temp;
        temp = temp->suivant;
        free(aSupprimer);
    }
    free(liste);
}

void SupprimerElementDebut(Liste *liste)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }
    Element *aSupprimer = liste->premier;
    liste->premier = liste->premier->suivant;
    free(aSupprimer);
    liste->nbreElement--;
}

void DeterminerNombreElement(Liste *liste)
{
    int compteur = 0;
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }
    Element *temp = liste->premier;
    while(temp != NULL)
    {
        temp = temp->suivant;
        compteur++;
    }
    liste->nbreElement = compteur;
}

void AjouterElementFin(Liste *liste, int nvNombre)
{
    Element *nouveau = malloc(sizeof(*nouveau));
    if(liste == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }
    int compteur = 0;
    Element *temp = liste->premier;
    while(compteur < liste->nbreElement - 1)
    {
        temp = temp->suivant;
        compteur++;
    }
    nouveau->nombre = nvNombre;
    nouveau->suivant = NULL;
    temp->suivant = nouveau;
    liste->nbreElement++;
}

void SupprimerElementFin(Liste *liste)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }
    int compteur = 0;
    Element *temp = liste->premier;
    while(compteur < liste->nbreElement - 2)
    {
        temp = temp->suivant;
        compteur++;
    }
    Element *aSupprimer = temp->suivant;
    temp->suivant = NULL;
    free(aSupprimer);
    liste->nbreElement--;
}
