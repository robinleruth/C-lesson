#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "gestion.h"
#include "liste.h"

void DeterminerCoordonneesAleatoires(int *x, int *y)
{
    *x = rand()%(ABSCISSE_MAX - 1);
    *y = rand()%(ORDONNEE_MAX - 1);
}

void AfficherElements(Liste *liste, int matrice[ABSCISSE_MAX][ORDONNEE_MAX], int *nbrePommes, int score)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }
    int i, j;
    CreerPomme(liste, matrice, nbrePommes); // on positionne une pomme aléatoirement sur la map
    for(j=0; j<ORDONNEE_MAX; j++)
    {
        for(i=0; i<ABSCISSE_MAX; i++)
        {
            if(matrice[i][j] == SNAKE)
            {
                coloration(15,3);
                printf("*");
                coloration(15,0);
            }
            else if (matrice[i][j] == POMME)
            {
                coloration(15,3);
                printf("o");
                coloration(15,3);
            }
            else if(matrice[i][j] == BORDURE_DROITE)
            {
                coloration(15,13);
                printf("|");
                coloration(15,3);
            }
            else if(matrice[i][j] == BORDURE_BASSE)
            {
                coloration(15,13);
                printf("_");
                coloration(15,3);
            }
            else if(matrice[i][j] == BORDURE_HAUTE)
            {
                coloration(15,13);
                printf("_");
                coloration(15,3);
            }
            else if(matrice[i][j] == BORDURE_GAUCHE)
            {
                coloration(15,13);
                printf("|");
                coloration(15,3);
            }
            else
            {
                coloration(0,3);
                printf(" ");
                coloration(15,0);
            }
        }
        printf("\n");
    }
}

void GererEvenement(Liste *liste, char *direction, int matrice[ABSCISSE_MAX][ORDONNEE_MAX])
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }
    int x1, y1;
    if(kbhit()) // on regarde si une touche a été pressée
    {
        *direction = getch(); // on la lit
        switch(*direction)
        {
        case 'c':
            system("cls");
            break;
        case GAUCHE:
            if(liste->direction != DROITE)
            {
                x1 = liste->premier->x - 1;
                AjouterElementDebut(liste, &x1, &liste->premier->y, matrice);
                SupprimerElementFin(liste, matrice);
                liste->direction = GAUCHE;
            }
            break;
        case HAUT:
            if(liste->direction != BAS)
            {
                y1 = liste->premier->y - 1;
                AjouterElementDebut(liste, &liste->premier->x, &y1, matrice);
                SupprimerElementFin(liste, matrice);
                liste->direction = HAUT;
            }
            break;
        case BAS:
            if(liste->direction != HAUT)
            {
                y1 = liste->premier->y +1;
                AjouterElementDebut(liste, &liste->premier->x, &y1, matrice);
                SupprimerElementFin(liste, matrice);
                liste->direction = BAS;
            }
            break;
        case DROITE:
            if(liste->direction != GAUCHE)
            {
                x1 = liste->premier->x + 1;
                AjouterElementDebut(liste, &x1, &liste->premier->y, matrice);
                SupprimerElementFin(liste, matrice);
                liste->direction = DROITE;
            }
            break;
        case 'q':
            system("cls");
            break;
        }
    }
}

void InstructionAutonome(Liste *liste, char *direction, int matrice[ABSCISSE_MAX][ORDONNEE_MAX])
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }
    int x1, y1;
    switch(liste->direction)
    {
    case GAUCHE:
        x1 = liste->premier->x - 1;
        AjouterElementDebut(liste, &x1, &liste->premier->y, matrice);
        SupprimerElementFin(liste, matrice);
        break;
    case HAUT:
        y1 = liste->premier->y - 1;
        AjouterElementDebut(liste, &liste->premier->x, &y1, matrice);
        SupprimerElementFin(liste, matrice);
        break;
    case BAS:
        y1 = liste->premier->y +1;
        AjouterElementDebut(liste, &liste->premier->x, &y1, matrice);
        SupprimerElementFin(liste, matrice);
        break;
    case DROITE:
        x1 = liste->premier->x + 1;
        AjouterElementDebut(liste, &x1, &liste->premier->y, matrice);
        SupprimerElementFin(liste, matrice);
        break;
    }
}

void GestionCollision(char *c, int *x, int *y, int matrice[ABSCISSE_MAX][ORDONNEE_MAX])
{
    if(*x >= ABSCISSE_MAX - 1)
    {
        *c = PERDU;
    }
    else if(*x < 1)
    {
        *c = PERDU;
    }

    if(*y >= ORDONNEE_MAX - 1)
    {
        *c = PERDU;
    }
    else if(*y < 1)
    {
        *c = PERDU;
    }
    switch(*c)
    {
    case HAUT:
        if(matrice[*x-1][*y] == SNAKE)
        {
            *c = PERDU;
        }
        break;
    case BAS:
        if(matrice[*x+1][*y] == SNAKE)
        {
            *c = PERDU;
        }
        break;
    case GAUCHE:
        if(matrice[*x][*y-1] == SNAKE)
        {
            *c = PERDU;
        }
        break;
    case DROITE:
        if(matrice[*x][*y+1] == SNAKE)
        {
            *c = PERDU;
        }
        break;
    }
}

void CreerPomme(Liste *liste, int matrice[ABSCISSE_MAX][ORDONNEE_MAX], int *nbrePommes)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }
    int i = 0, j = 0;
    int x, y;
    int compteur = 0;
    for(j=0; j<ORDONNEE_MAX; j++)
    {
        for(i=0; i<ABSCISSE_MAX; i++)
        {
            if(matrice[i][j] == POMME)
            {
                compteur++;
            }
        }
    }
    if(compteur == 0)
    {
        x = rand()%(ABSCISSE_MAX - 5) +2;
        y = rand()%(ORDONNEE_MAX - 5)+2;
        matrice[x][y] = POMME;
        *nbrePommes = *nbrePommes + 1;
    }
}

void NouvelElement(Liste *liste, char *direction, int matrice[ABSCISSE_MAX][ORDONNEE_MAX])
{
    int x1, y1;
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }
    switch(*direction)
    {
    case GAUCHE:
        x1 = liste->premier->x - 1;
        AjouterElementDebut(liste, &x1, &liste->premier->y, matrice);
        break;
    case HAUT:
        y1 = liste->premier->y - 1;
        AjouterElementDebut(liste, &liste->premier->x, &y1, matrice);
        break;
    case BAS:
        y1 = liste->premier->y +1;
        AjouterElementDebut(liste, &liste->premier->x, &y1, matrice);
        break;
    case DROITE:
        x1 = liste->premier->x + 1;
        AjouterElementDebut(liste, &x1, &liste->premier->y, matrice);
        break;
    }
}

void gotoligcol( int lig, int col )
{
// ressources
    COORD mycoord;

    mycoord.X = col;
    mycoord.Y = lig;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );
}
