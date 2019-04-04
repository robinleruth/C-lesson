#include "include.h"

// BUFFER d'affichage
BITMAP *page;
BITMAP *bufferCollision;

// Regroupe les initialisations d'allegro, mode graphique, clavier, souris
void lancerToutAllegro(int largeur, int hauteur)
{
    allegro_init();
    install_keyboard();
    install_mouse();

    /// OUVERTURE MODE GRAPHIQUE (ouverture fenêtre allegro)
    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,largeur,hauteur,0,0)!=0)
    {
        allegro_message("probleme mode graphique : %s", allegro_error);
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    show_mouse(screen); // Affiche pointeur de souris en mode allegro

    // CREATION DU BUFFER D'AFFICHAGE à la taille de l'écran
    page=create_bitmap(SCREEN_W,SCREEN_H);
    bufferCollision = create_bitmap(SCREEN_W, SCREEN_H);
    clear_bitmap(page);
    clear_bitmap(bufferCollision);
}

// Fonctionne comme load_bitmap sauf qu'il ne prend pas NULL en 2ème paramètre
// et qu'il termine le programme (avec message) en cas d'échec
//    Exemple de fonction wrapper (emballage d'une fct par une autre fct)
BITMAP *chargerImage(char *nomFichierImage)
{
    BITMAP *bmp;
    bmp=load_bitmap(nomFichierImage,NULL);
    if (bmp==NULL)
    {
        allegro_message("pas pu trouver/charger %s",nomFichierImage);
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    printf("Image charg\202e : %s\n", nomFichierImage);
    return bmp;
}

void InitialiserDecor(t_decor *decor)
{
    decor->x = 0;
    decor->y = 0;
}

void ChargerSpritesDebut(t_player *player)
{
    player->sprite[PERSO_BAS] = chargerImage("images/persoBas.bmp");
    player->sprite[PERSO_HAUT] = chargerImage("images/persoHaut.bmp");
    player->sprite[PERSO_GROS_BAS] = NULL;
    player->sprite[PERSO_GROS_HAUT] = NULL;
}

void ChargerSprites(t_player *player, t_player *exemple)
{
    player->sprite[PERSO_BAS] = exemple->sprite[PERSO_BAS];
    player->sprite[PERSO_HAUT] = exemple->sprite[PERSO_HAUT];
    player->sprite[PERSO_GROS_BAS] = exemple->sprite[PERSO_GROS_BAS];
    player->sprite[PERSO_GROS_HAUT] = exemple->sprite[PERSO_GROS_HAUT];
}

void ChargerToutesImages(t_decor *fond, t_decor *obstacle, t_menu *menu, BITMAP *tableau[NB_BONUS])
{
    int i;
    char nf[200];
    for(i=0;i<NB_NIVEAU;i++)
    {
        sprintf(nf, "images/Fond%d.bmp", i);
        fond->image[i] = chargerImage(nf);
    }
    InitialiserDecor(fond);
    for(i=0;i<NB_NIVEAU;i++)
    {
        sprintf(nf, "images/Obstacle%d.bmp", i);
        obstacle->image[i] = chargerImage(nf);
    }
    for(i=0;i<NB_BONUS;i++)
    {
        sprintf(nf, "images/bonus%d.bmp", i);
        tableau[i] = chargerImage(nf);

    }
    InitialiserDecor(obstacle);
    menu->image = chargerImage("images/FondMenu.bmp");
}
