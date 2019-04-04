#include <stdio.h>
#include <stdlib.h>
#include "include.h"

int DeterminerNombreDeScore(FILE *fp)
{
    int compteur = 0;
    char c = 0;
    rewind(fp);
    while(!feof(fp))
    {
        c = fgetc(fp);
        if(c == '\n')
        {
            compteur++;
        }
    }
    return compteur;
}

void ClasserTableau(int tableau[], int tailleTableau)
{
    int i = 0, j = 0;
    int temp;
    for(i=0; i<tailleTableau; i++)
    {
        for(j=0; j<tailleTableau - 1; j++)
        {
            if(tableau[j] < tableau[j+1])
            {
                temp = tableau[j];
                tableau[j] = tableau[j+1];
                tableau[j+1] = temp;
            }
        }
    }
}

void AfficherRegles()
{
    FILE *fp = NULL;
    fp = fopen("Règles du Jeu.txt", "r");
    if(fp == NULL)
    {
        printf("erreur fichier");
    }
    else
    {
        while(!feof(fp))
        {
            printf("%c", fgetc(fp));
        }
        fclose(fp);
    }
}

void RegarderScore()
{
    FILE *fp = NULL;
    int compteur = 0;
    char c;
    fp = fopen("Meilleurs Scores.txt", "r");
    if(fp == NULL)
    {
        printf("Erreur lecture de fichier");
    }
    else
    {
        printf("Vos meilleurs scores sont : \n\n");
        printf("1 : ");
        while(c != EOF)
        {
            c = fgetc(fp);
            printf("%c", c);
            if(c =='\n')
            {
                if(compteur < 10)
                    printf("%d : ", compteur + 1);
                compteur++;
            }
            if(compteur > 10)
            {
                c = EOF;
            }
        }
        fclose(fp);
    }
}

void AddScore(int score)
{
    int *tab = NULL;
    int nbreDeScore = 0;
    int i;
    FILE *fp = NULL;
    fp = fopen("Meilleurs scores.txt", "r+");
    if(fp == NULL)
    {
        printf("Erreur ouverture fichier");
    }
    else
    {
        fseek(fp, 0, SEEK_END);
        fprintf(fp, "\n%d\n", score);
        nbreDeScore = DeterminerNombreDeScore(fp);
        if(nbreDeScore > 0)
        {
            tab = malloc(nbreDeScore*sizeof(int));
            if(tab == NULL)
            {
                exit(EXIT_FAILURE);
            }
            InitialiserTableau(tab, nbreDeScore);
            rewind(fp);
            for(i=0;i<nbreDeScore;i++)
            {
                fscanf(fp, "%d", &tab[i]);
            }
            ClasserTableau(tab, nbreDeScore);
        }
        fclose(fp);
    }

    fp = fopen("Meilleurs Scores.txt", "w");
    if(fp == NULL)
    {
        printf("erreur d'ouverture");
    }
    else
    {
        for(i=0;i<nbreDeScore;i++)
        {
            fprintf(fp, "%d\n", tab[i]);
        }
        fclose(fp);
    }
    free(tab);
}

void InitialiserTableau(int tab[], int tailleTableau)
{
    int i;
    for(i=0;i<tailleTableau;i++)
    {
        tab[i] = 0;
    }
}
