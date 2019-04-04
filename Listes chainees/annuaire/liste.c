#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "liste.h"

Liste *Initialisation()
{
    Liste *liste = malloc(sizeof(*liste));
    Personne *personne = malloc(sizeof(*personne));
    if((liste == NULL) || (personne == NULL))
    {
        exit(EXIT_FAILURE);
    }

    strcpy(personne->nom, "");
    strcpy(personne->prenom, "");
    personne->age = 0;
    personne->suivant = NULL;
    liste->premier = personne;
    return liste;
}

void AjoutPersonne(Liste *liste, const char *nom, const char *prenom, const int age)
{
    Personne *nouveau = malloc(sizeof(*nouveau));
    if((liste == NULL) || (nouveau == NULL))
    {
        exit(EXIT_FAILURE);
    }
    strncpy(nouveau->nom, nom, 20);
    strncpy(nouveau->prenom, prenom, 20);
    nouveau->age = age;
    nouveau->suivant = liste->premier;
    liste->premier = nouveau;
}

void SupprimerPremierePersonne(Liste *liste)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }
    Personne *aSupprimer = liste->premier;
    liste->premier = liste->premier->suivant;
    free(aSupprimer);
}

void SupprimerListe(Liste *liste)
{
    if(liste==NULL)
    {
        exit(EXIT_FAILURE);
    }
    Personne *temp = liste->premier;
    while(temp != NULL)
    {
        Personne *aSupprimer = temp;
        temp = temp->suivant;
        free(aSupprimer);
    }
    free(liste);
}

void AfficherListe(Liste *liste)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }
    SupprimerDernierePersonne(liste);
    Personne *actuel = liste->premier;
    while(actuel != NULL)
    {
        printf("%s %s, %d ans", actuel->nom, actuel->prenom, actuel->age);
        printf(" -> \n");
        actuel = actuel->suivant;
    }
    printf("NULL");
}

void purger()
{
    char c;
    while((c = getchar() != '\n') && (c != EOF));
}

void clean(char *str)
{
    char *p = strchr(str, '\n');

    if(p)
    {
        *p = 0;
    }
    else
    {
        purger();
    }
}

void ObtenirNom(char *str)
{
    do
    {
        fgets(str, 20, stdin);
        clean(str);
        if(str[0] == '\0')
        {
            printf("\nEntrez un nom valide : ");
        }
    }while(str[0] == '\0');
}

void ObtenirPersonne(char *nom, char *prenom, int *age)
{
    printf("\nEntrez le nom : ");
    ObtenirNom(nom);
    printf("\nEntrez le prenom : ");
    ObtenirNom(prenom);
    printf("\nSaisissez l'age : ");
    scanf("%d", age);
    purger();
}

void DeterminerNbreElement(Liste *liste)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }
    int compteur = 0;
    Personne *temp = liste->premier;
    while(temp != NULL)
    {
        temp = temp->suivant;
        compteur++;
    }

    liste->nbreElement = compteur;
}

void SupprimerDernierePersonne(Liste *liste)
{
    if((liste == NULL) || (liste->premier == NULL))
    {
        exit(EXIT_FAILURE);
    }
    Personne *temp = liste->premier;
    DeterminerNbreElement(liste);
    int compteur = 0;
    while(compteur < liste->nbreElement - 2)
    {
        temp = temp->suivant;
        compteur++;
    }
    Personne *aSupprimer = temp->suivant;
    temp->suivant = NULL;
    free(aSupprimer);
}
