#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

#include "include.h"

t_player *CreerElement(t_player *exemple);
int Perdu(t_liste *ancre);
void CollisionJoueur(t_liste *ancre, int taille);
void InitialiserMenu(t_menu *menu);
int verifDeath(t_player * playerSTR, t_decor * foreground);
int JouerNiveau(t_decor *fond, t_decor *decor, int niveau, t_liste *exemple, BITMAP *spritesBonus[5]);
int verifColl(t_player * playerSTR, t_decor * colliders, int niveau, t_liste *ancre,t_collec * collec, int *score);
void grandirElem (t_liste * ancre);
void accelElem (t_liste * ancre, int vitesse);
void deleteBonus(t_collec * collec, t_player * playerSTR);
void movePlayer(int * scrolling, t_player * playerSTR, t_decor * foreground, int keyPressed, int niveau, t_liste *ancre,t_collec * collec, int *booleen, int * score);
void retrecirElem (t_liste * ancre);
#endif // JEU_H_INCLUDED
