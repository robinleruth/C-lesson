#ifndef INCLUDE_H_INCLUDED
#define INCLUDE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include "struct.h"
#include "jeu.h"
#include "liste.h"
#include "ouverture.h"
#include "menu.h"
#include "bonus.h"
#include "score.h"

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

#endif // INCLUDE_H_INCLUDED
