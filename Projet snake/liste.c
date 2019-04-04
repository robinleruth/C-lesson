#include <stdio.h>
#include <stdlib.h>
#include "liste.h"
#include "gestion.h"

Liste *InitialisationListe(int *abscisse, int *ordonnee, int matrice[ABSCISSE_MAX][ORDONNEE_MAX])
{
    Liste *liste = malloc(sizeof(*liste));
    Element *element = malloc(sizeof(*element));
    if(liste == NULL || element == NULL)
    {
        exit(EXIT_FAILURE);
    }
    element->x = *abscisse;
    element->y = *ordonnee;
    element->suivant = NULL,
    liste->premier = element;
    liste->nbreElement = 1;
    matrice[element->x][element->y] = SNAKE;
    return liste;
}
/*
void SupprimerElementDebut(Liste *liste)
{
    if(liste == NULL || liste->premier == NULL)
    {
        exit(EXIT_FAILURE);
    }
    Element *aSupprimer = liste->premier;
    liste->premier = liste->premier->suivant;
    free(aSupprimer);
    liste->nbreElement--;
}
*/
void AjouterElementFin(Liste * liste, int *abscisse, int *ordonnee, int matrice[ABSCISSE_MAX][ORDONNEE_MAX])
{
    Element *nouveau = malloc(sizeof(*nouveau));
    int compteur = 0;
    if(liste == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }
    Element *actuel = liste->premier;
    while(compteur < liste->nbreElement - 1)
    {
        actuel = actuel->suivant;
        compteur++;
    }
    nouveau->x = *abscisse;
    nouveau->y = *ordonnee;
    nouveau->suivant = NULL;
    actuel->suivant = nouveau;
    matrice[nouveau->x][nouveau->y] = SNAKE;
    liste->nbreElement++;
}

void SupprimerListe(Liste *liste)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }
    Element *actuel = liste->premier;
    while(actuel != NULL)
    {
        Element *aSupprimer = actuel;
        actuel = actuel->suivant;
        free(aSupprimer);
    }
    free(liste);
}

void MettreSnakeMatrice(Liste *liste, int matrice[ABSCISSE_MAX][ORDONNEE_MAX])
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }
    Element *actuel = liste->premier;
    while(actuel != NULL)
    {
        matrice[actuel->x][actuel->y] = SNAKE;
        actuel = actuel->suivant;
    }
}

void AjouterElementDebut(Liste *liste, int *abscisse, int *ordonnee, int matrice[ABSCISSE_MAX][ORDONNEE_MAX])
{
    Element *nouveau = malloc(sizeof(*nouveau));
    if(liste == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }
    nouveau->x = *abscisse;
    nouveau->y = *ordonnee;
    nouveau->suivant = liste->premier;
    liste->premier = nouveau;
    liste->nbreElement++;
    matrice[nouveau->x][nouveau->y] = SNAKE;
}

void SupprimerElementFin(Liste *liste, int matrice[ABSCISSE_MAX][ORDONNEE_MAX])
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }
    Element *temp = liste->premier;
    int compteur = 0;
    while(compteur < liste->nbreElement - 2)
    {
        temp = temp->suivant;
        compteur++;
    }
    matrice[temp->suivant->x][temp->suivant->y] = 0;
    Element *aSupprimer = temp->suivant;
    temp->suivant = NULL;
    free(aSupprimer);
    liste->nbreElement--;
}
