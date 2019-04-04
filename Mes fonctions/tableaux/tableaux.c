#include <stdio.h>
#include <stdlib.h>

#include "tableaux.h"

void afficheTableau(int tableau[], int tailleTableau)
{
    int i;
    for(i=0;i<tailleTableau;i++)
    {
        printf("La case numero %d contient : %d\n", i+1, tableau[i]);
    }
}

int sommeTableau(int tableau[], int tailleTableau)
{
    int i;
    int somme = 0;
    for(i=0;i<tailleTableau;i++)
    {
        somme = somme + tableau[i];
    }
    return somme;
}

float moyenneTableau(int tableau[], int tailleTableau)
{
    int i;
    float moy;
    float somme = 0;
    for(i=0;i<tailleTableau;i++)
    {
        somme = somme + tableau[i];
    }
    moy = somme/i;
    return moy;
}

void copieTableau(int tableauOriginal[], int tableauCopie[], int tailleTableau)
{
    int i;
    for(i=0;i<tailleTableau;i++)
    {
        tableauCopie[i] = tableauOriginal[i];
    }
}


void maximumTableau(int tableau[], int tailleTableau, int valeurMax)
{
    int i;
    for(i=0;i<tailleTableau;i++)
    {
        if (tableau[i]>valeurMax)
        {
            tableau[i] = 0;
        }
    }
}


void ordonnerTableau(int tableau[], int tailleTableau)
{
    int i;
    int j;
    int c;

    j = 0;
    do
    {
        for(i=0; i<tailleTableau-1; i++)
        {
            if (tableau[i]>tableau[i+1])
            {
                c=tableau[i];
                tableau[i]=tableau[i+1];
                tableau[i+1]=c;
            }
        }
        j++;
    }while(j<tailleTableau);
}

int rechercheMini(int tableau[], int tailleTableau)
{
    int i;
    int inter = tableau[0];
    int minimum = tableau[0];
    for(i=0;i<tailleTableau-1;i++)
    {
        if (tableau[i]<tableau[i+1])
        {
            inter = tableau[i];
        }
        if(minimum>inter)
        {
            minimum=inter;
        }
    }
    return minimum;
}

void initialiserTableau(int tableau[], int tailleTableau)
{
    int i;
    for(i=0;i<tailleTableau;i++)
    {
        tableau[i]=0;
    }
}

void remplirTableau(int tableau[], int tailleTableau)
{
    int i;
    for(i=0;i<tailleTableau;i++)
    {
        printf("\nSaisissez l'entier %d : ", i+1);
        scanf("%d", &tableau[i]);
    }
}

void inverserTableau(const int tableau[], int inverse[], int tailleTableau)
{
    int i;
    for(i=0;i<tailleTableau;i++)
    {
        inverse[i] = tableau[tailleTableau-i-1];
    }
}

void initialiserPointeur(char *tableau[], int tailleTableau)
{
    int i;
    for(i=0;i<tailleTableau;i++)
    {
        tableau[i] = NULL;
    }
}
