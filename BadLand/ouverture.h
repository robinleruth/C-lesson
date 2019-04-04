#ifndef OUVERTURE_H_INCLUDED
#define OUVERTURE_H_INCLUDED

#include "include.h"
extern BITMAP *page;
extern BITMAP *bufferCollision;
void lancerToutAllegro(int largeur, int hauteur);
BITMAP *chargerImage(char *nomFichierImage);
void InitialiserDecor(t_decor *decor);
void ChargerSpritesDebut(t_player *player);
void ChargerSprites(t_player *player, t_player *exemple);
void ChargerToutesImages(t_decor *fond, t_decor *obstacle, t_menu *menu, BITMAP *tableau[6]);

#endif // OUVERTURE_H_INCLUDED
