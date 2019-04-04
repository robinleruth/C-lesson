#include <stdio.h>
#include <stdlib.h>
#include "liste_chainee.h"

Liste *InitialisationListeChainee()
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

void InsertionElementDebut(Liste *liste, int nvNombre)
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

void SuppressionPremierElement(Liste *liste)
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

void SuppressionDeListe(Liste *liste)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }
    do
    {
        Element *aSupprimer = liste->premier;
        liste->premier = liste->premier->suivant;
        free(aSupprimer);
    }while(liste->premier->suivant != NULL);
    free(liste);
}

void DeterminerTailleDeListe(Liste *liste)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }
    int taille = 0;
    Element *temp = liste->premier;
    while(temp != NULL)
    {
        temp = temp->suivant;
        taille++;
    }
    liste->nbElement = taille;
}

void InsertionElementFin(Liste *liste, int nvNombre)
{
    Element *nouveau = malloc(sizeof(*nouveau));
    if((liste == NULL) || (nouveau == NULL))
    {
        exit(EXIT_FAILURE);
    }
    Element *temp = liste->premier;
    DeterminerTailleDeListe(liste);
    int compteur = 0;
    while(compteur<(liste->nbElement)-1)
    {
        temp = temp->suivant;
        compteur++;
    }
    nouveau->nombre = nvNombre;
    nouveau->suivant = NULL;
    temp->suivant = nouveau;
}

void SuppressionDernierElement(Liste *liste)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }
    DeterminerTailleDeListe(liste);
    int compteur = 0;
    Element *temp = liste->premier;
    while(compteur<(liste->nbElement)-2)
    {
        temp = temp->suivant;
        compteur++;
    }
    Element *aSupprimer = temp->suivant;
    temp->suivant = NULL;
    free(aSupprimer);
}
