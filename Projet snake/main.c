/*
*************Projet du SNAKE*****************
Réalisé par Robin LERUTH ING1 TD2
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "include.h"

int main(int argc, char *argv[])
{
    /* Déclaration de Variables */
    char c;
    int matrice[ABSCISSE_MAX][ORDONNEE_MAX] = {{0}}; // Déclaration du terrain
    int x = 0, y = 0; //Les premières coordonnées de la tête
    int nbreDePommes = 0, temp = nbreDePommes;
    int score, nbreDeTours = 0;
    Liste *snake = NULL; // Liste chainée représentant les parties du snake
    Menu menu; // La structure menu
    int i;
    InitialiserMenu(&menu);

    srand(time(NULL));
    while(menu.quitter == 0) // La boucle du menu !
    {
        system("color 3F");
        InitialiserMenu(&menu);
        ChoisirOption(&menu);// cf decor.c
        system("cls");
        if(menu.jouer == 1) //si on a choisit de jouer
        {
            nbreDePommes = 0;
            temp = nbreDePommes;
            for(i=3;i>0;i--) // Petit compteur
            {
                printf("Vous allez jouer dans %d seconde(s)", i);
                Sleep(1000);
                system("cls");
            }
            score = 0;
            InitialiserMatrice(matrice); // On initialise toutes les caes à 0
            system("color 0F");
            DeterminerCoordonneesAleatoires(&x, &y); // On détermine les premières coordonnées de la tête du snake
            snake = InitialisationListe(&x, &y, matrice); // On met en place la liste chainée (cf liste.c)
            x--;
            AjouterElementFin(snake, &x, &y, matrice); // Le snake commence avec 2 éléments !
            ParametrerTerrain(matrice); // On met les bordures du terrain
            snake->direction = DROITE; // Le snake commence à aller à droite
            c = DROITE;
            while(c != 'q' && c != PERDU) // Boucle de jeu
            {
                /* Ces fonctions se trouvent pour la plupart dans gestion.c */
                gotoligcol(0,0); // on rafraichit le terrain
                AfficherElements(snake, matrice, &nbreDePommes, score); // on affiche le snake/les pommes/les bordures
                InstructionAutonome(snake, &c, matrice);
                if(temp != nbreDePommes) // si on a mangé une pomme, le snake grossit
                {
                    NouvelElement(snake, &c, matrice);
                    temp++;
                }
                GererEvenement(snake, &c, matrice); // on lit la touche
                GestionCollision(&c, &snake->premier->x, &snake->premier->y, matrice); //On a perdu si on touche les bords ou sa queue
                nbreDeTours++;
                score = (snake->nbreElement*nbreDeTours)/10;
                AfficherScoreEcran(score);
                AfficherNbreDePommesEcran(nbreDePommes - 1);
            }
            SupprimerListe(snake);
            if(c == PERDU)
            {
                system("cls");
                printf("Vous avez perdu !\n\n");
            }
            system("cls");
            printf("Vous avez mange %d pommes et fait un score de : %d !\n\n", nbreDePommes - 1, score);
            printf("\n");
            system("PAUSE");
            AddScore(score);
            menu.jouer = 0;
            system("cls");
        }
        else if(menu.regarderScore == 1)
        {
            RegarderScore();
            printf("\n");
            system("PAUSE");
            system("cls");
            menu.regarderScore = 0;
        }
        else if(menu.regleDuJeu == 1)
        {
            AfficherRegles();
            printf("\n");
            system("PAUSE");
            system("cls");
            menu.regleDuJeu = 0;
        }
    }



    return EXIT_SUCCESS;
}
