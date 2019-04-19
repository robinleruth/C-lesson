#ifndef INCLUDE_H_INCLUDED
#define INCLUDE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "allegro.h"

extern BITMAP * calque_batiment;
extern BITMAP * calque_grille;
extern BITMAP * calque_routes;
extern BITMAP * calque_ressources;
extern BITMAP * buffer;

#define TAILLE_X 45
#define TAILLE_Y 35
#define WIDTH 1024
#define HEIGHT 768
#define NB_HABITATION_INITIAL 10
#define NB_CHATEAU_INITIAL 10
#define NB_CENTRALE_INITIAL 10
#define NB_STADE 5
#define NB_ROUTE 16

//Stade habitation
#define RUINE 0
#define TERRAIN_VAGUE 0
#define CABANE 1
#define MAISON 2
#define IMMEUBLE 3
#define GRATTE_CIEL 4

#define LARGEUR 900
#define HAUTEUR 700

#define RIEN 0
#define ROUTE 1
#define HABITATION 2
#define CENTRALE 3
#define CHATEAU_EAU 4
#define CASERNE 5

#define QTE_EAU 5000
#define QTE_ELEC 5000

#define INFINI 1000

#define LONGUEUR_BATIMENTS 60
#define LARGEUR_BATIMENTS 60
#define LONGUEUR_RESSOURCE 80
#define LARGEUR_RESSOURCE 120

#define CASE_BATIMENTS 3
#define CASE_RESSOURCES_X 4
#define CASE_RESSOURCES_Y 6

typedef struct position
{
    int x;
    int y;
} t_position;

typedef struct habitation
{
    t_position* coord;
    int population;
    int stade;
    int temps_initial;
    int eau;
    int elec;
} t_habitation;

typedef struct batiments
{
    struct habitation **habitations;
    int nb_habitation;
    int tailleTableau;
    BITMAP **imagesBatiments;
} t_batiments;


typedef struct eau
{
    t_position *coord;
    int qtEau;
} t_eau;

typedef struct chateau
{
    t_eau **chateaux;
    int nb_chateaux;
    int tailleTableauChateau;
    BITMAP *image;
} t_chateaux;

typedef struct elec
{
    t_position *coord;
    int qtElec;
} t_elec;

typedef struct centrale
{
    t_elec **centrales;
    int nb_centrales;
    int tailleTableauCentrale;
    BITMAP *image;
} t_centrales;

typedef struct routes
{
    struct position* coord;
} t_routes;

typedef struct structRoute
{
    t_routes **routes;
    int nbroute;
    BITMAP **bibliroute;
} t_structRoute;

typedef struct jeu
{
    int **matrice;
    t_batiments *batiments;
    t_structRoute *ensembleRoutes;
    t_chateaux *chateaux;
    t_centrales *centrales;
    int choix_menu;
    int mode;
} t_jeu;

#include "route.h"
#include "habitation.h"
#include "batiments.h"
#include "graphe.h"
#include "ressources.h"
#include "jeu.h"
#include "affichage.h"
#include "allegro.h"

#endif // INCLUDE_H_INCLUDED

