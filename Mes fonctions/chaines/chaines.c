#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chaines.h"

void purger()
{
    char c;
    while((c=getchar() != '\n') && (c != EOF));
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

void majuscule(const char *str)
{
    int diff = 'a'-'A';
    char a;

    while(*str) //Tant qu'on n'arrive pas à la fin de la chaine
    {
        a=*str;
        if ((*str>='a')&&(*str<='z'))
        {
            a=*str-diff;
            printf("%c", a);
        }
        else
        {
            printf("%c", a);
        }
        *str++;
    }
}

void minuscule (const char *str)
{
    int diff = 'a'-'A';
    char a;

    while (*str)
    {
        a = *str;
        if((*str>='A')&&(*str<='Z'))
        {
            a = *str + diff;
            printf("%c", a);
        }
        else
        {
            printf("%c", a);
        }
        *str++;
    }
}

void comparaison(const char *str, const char *str1)
{
    int res;
    res = strcmp(str, str1);
    if (res>0)
    {
        printf("\nLa chaine 1 est plus longue que la chaine 2");
    }
    else if (res==0)
    {
        printf("\nLes deux chaines ont la meme longueur");
    }
    else
    {
        printf("\nLa chaine 1 est plus petite que la chaine 2");
    }
}


void compter(const char *str)
{
    printf("\nLa longueur de la chaine est %d", strlen(str));
}


void concat(const char *str, const char *str1)
{
    strcat(str, str1);
    printf("\nLes deux chaînes concaténées sont : %s", str);
}

int voyelle(const char *str)
{
    int i = 0;
    while (*str)
    {
        if (*str==',')
        {
            i++;
        }
        *str++;
    }
    return i;
}

int trouverNombreDeLettres(const char *str)
{
    int compteur = 0;
    while(*str)
    {
        compteur++;
        *str++;
    }
    return compteur;
}

void ordonnerTableauDeChaines(char *tableau[], int tailleTableau)
{
    int i;
    int j;
    char *inter = NULL;
    int res;

    j = 0;
    do
    {
        for(i=0; i<tailleTableau-1; i++)
        {
            res = strcmp(tableau[i], tableau[i+1]);
            if (res>0)
            {
                inter = malloc(strlen(tableau[i]+1));
                if(inter == NULL)
                {
                    printf("Erreur d'allocation de mémoire : /  ");
                    exit(EXIT_FAILURE);
                }
                strcpy(inter, tableau[i]);
                free(tableau[i]);
                tableau[i]=malloc(strlen(tableau[i+1]+1));
                if(tableau[i] == NULL)
                {
                    printf("Erreur d'allocation de mémoire : /  ");
                    exit(EXIT_FAILURE);
                }
                strcpy(tableau[i], tableau[i+1]);
                free(tableau[i+1]);
                tableau[i+1] = malloc(strlen(inter)+1);
                if(tableau[i+1] == NULL)
                {
                    printf("Erreur d'allocation de mémoire : /  ");
                    exit(EXIT_FAILURE);
                }
                strcpy(tableau[i+1], inter);
                free(inter);
            }
        }
        j++;
    }while(j<tailleTableau);
}

void remplirTableauDeChaines(char *tableau[], char *str, int tailleTableau)
{
    int i;
    for(i=0;i<NOMBRE;i++)
    {
        do
        {
            printf("\nEntrez la phrase %d de moins de 100 caractères : ", i+1);
            fgets(str, 100, stdin);
            if(str[0] == '\0')
            {
                printf("\nVous n'avez pas entre une phrase valide.");
            }
        }while(str[0] == '\0');
        clean(str);
        tableau[i]=malloc(strlen(str)+1);
        if(tableau[i] != NULL)
        {
            strcpy(tableau[i], str);
        }
        else
        {
            printf("Erreur : pas assez de mémoire...");
            exit(EXIT_FAILURE);
        }
    }
}

void libererMemoire(char *tableau[], int tailleTableau)
{
    int i;
    for(i=0;i<tailleTableau;i++)
    {
        free(tableau[i]);
    }
}
