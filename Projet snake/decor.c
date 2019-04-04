#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "include.h"


void ParametrerTerrain(int matrice[ABSCISSE_MAX][ORDONNEE_MAX])
{
    int i;
    for(i=0; i<ABSCISSE_MAX; i++)
    {
        matrice[i][ORDONNEE_MAX - 1] = BORDURE_BASSE;
    }
    for(i=0; i<ORDONNEE_MAX; i++)
    {
        matrice[ABSCISSE_MAX - 1][i] = BORDURE_DROITE;
    }
    for(i=0;i<ORDONNEE_MAX;i++)
    {
        matrice[0][i] = BORDURE_GAUCHE;
    }
    for(i=0;i<ABSCISSE_MAX;i++)
    {
        matrice[i][0] = BORDURE_HAUTE;
    }
}

void coloration(int couleurDuTexte, int couleurDeFond)
{
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, couleurDeFond*16+couleurDuTexte);
}
/*
0: noir
1: bleu foncé
2: vert
3: bleu-gris
4: marron
5: pourpre
6: kaki
7: gris clair
8: gris
9: bleu
10: vert fluo
11: turquoise
12: rouge
13: rose fluo
14: jaune fluo
15: blanc
*/

void AfficherScoreEcran(int score)
{
    gotoligcol(23,3);
    coloration(15,0);
    printf("Score : %d", score);
    coloration(15,3);
}

void InitialiserMenu(Menu *menu)
{
    menu->jouer = 0;
    menu->quitter = 0;
    menu->regarderScore = 0;
    menu->regleDuJeu = 0;
}

void ChoisirOption(Menu *menu)
{
    char choix = 0;
    printf("**********BIENVENUE DANS LE SNAKE**********\n\n");
    printf("Que voulez-vous faire?\n");
    printf("Jouer : 1\n");
    printf("Regarder vos meilleurs scores : 2\n");
    printf("Regarder les regles du jeu : 3\n");
    printf("Quitter : 4\n");
    do
    {
        choix = getch();
        switch(choix)
        {
        case '1':
            menu->jouer = 1;
            break;
        case '2':
            menu->regarderScore = 1;
            break;
        case '4':
            menu->quitter = 1;
            break;
        case '3':
            menu->regleDuJeu = 1;
            break;
        default:
            printf("Ce que vous avez entré n'est pas valide..\n");
        }
    }while(choix != '1' && choix != '2' && choix != '3' && choix != '4');

}

void InitialiserMatrice(int matrice[ABSCISSE_MAX][ORDONNEE_MAX])
{
    int i = 0, j = 0;
    for(j=0;j<ORDONNEE_MAX;j++)
    {
        for(i=0;i<ABSCISSE_MAX;i++)
        {
            matrice[i][j] = 0;
        }
    }
}

void AfficherNbreDePommesEcran(int nbrePommes)
{
    gotoligcol(23, 45);
    coloration(15,0);
    printf("Nombre de Pommes mangees : %d", nbrePommes);
    coloration(15,3);
}
