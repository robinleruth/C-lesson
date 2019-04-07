#ifndef INCLUDE_H_INCLUDED
#define INCLUDE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <math.h>
#include <string.h>


#define ATKSPEED 10
#define BONUS_BOOST 0
#define BONUS_GROSSIR 1
#define BONUS_RETRECIR 2
#define BONUS_ADD 3
#define ENGRENAGE 4
#define SCIE 5


#define NB_SPRITE_PERSO 4
#define PERSO_BAS 0
#define PERSO_HAUT 1
#define PERSO_GROS_BAS 2
#define PERSO_GROS_HAUT 3

#define NB_NIVEAU 3
#define NB_BONUS 6

#define NBR_SCORE 10
#define TAILLE_NOM 5

#define NBR_SCORE 10
#define TAILLE_NOM 5
typedef struct player
{
    BITMAP *sprite[4];
    int taille;
    int x,y; // position
    float vit_x, vit_y, vit_angle;
    int angle;
    int numero;
    int vivant;
}t_player;

typedef struct liste
{
    t_player *element;
    struct liste *suivant;
}t_liste;

typedef struct menu
{
    BITMAP *image;
    int quitter;
    int jouer;
    int regarderScore;
    int regles;
}t_menu;

typedef struct decor
{
    BITMAP *image[3];
    int x,y;
}t_decor;

typedef struct bonus
{
    BITMAP *image;
    int x,y;
    int type;
    int angle;
    int vivant;
}t_bonus;

typedef struct maCollec
{
    t_bonus **bonus;
    int nbBonus;
    int niveau;
}t_collec;

typedef struct joueur
                 { char  pseudo[TAILLE_NOM] ;
                   int score;
                   int niveau;
                 }t_joueur ;
  t_joueur joueur[NBR_SCORE] ;
  t_joueur temporaire[NBR_SCORE+1];

#include "jeu.h"
#include "ouverture.h"
#include "menu.h"
#include "bonus.h"
#include "score.h"
#include "liste.h"

#endif // INCLUDE_H_INCLUDED
