#include "include.h"

#define MURCOLL 0
#define ADDCOLL 16776960
#define SPEEDCOLL 16711680
#define MULTIPLIER 255
#define SCIECOLL 65793
#define RETRECIR 65280

///Fonction d'ajout d'un élement dans la liste chainée
t_player *CreerElement(t_player *exemple)
{
    int i;
    t_player *element = (t_player*)malloc(sizeof(t_player));
    if(element == NULL)
    {
        exit(EXIT_FAILURE);
    }
    for(i=0; i<NB_SPRITE_PERSO; i++)
    {
        element->sprite[i] = exemple->sprite[i];
    }
    //Initialisation des champs de la structure
    element->taille = exemple->taille;
    element->x = exemple->x + rand()%(100-30)+30;
    element->y = exemple->y + rand()%(100-30)+30;
    element->vit_x = exemple->vit_x;
    element->vit_y = exemple->vit_y;
    element->vivant = 1;
    //On retourne l'addresse de l'element créé
    return element;
}

int verifColl(t_player * playerSTR, t_decor * colliders, int niveau, t_liste *ancre, t_collec * collec, int *score)
{
    ///Variables de parcours:
    int x,y;
    static int b = 0;
    const int rayon = playerSTR->taille*0.44/2;
    int couleur_haut, couleur_bas;

    ///Collision par secteurs (physique poussée)
    for(x = -rayon ; x < rayon/2 ; x ++)
    {
        //On calcule y en fonction de x (Theoreme de Pythagore):
        y =  sqrt( rayon * rayon - x * x);

        //Verification du pixel sur la partie haute, et basse du cercle:
        couleur_haut = getpixel(bufferCollision, playerSTR->x - colliders->x + playerSTR->taille/2 + x + playerSTR->vit_x, playerSTR->y - colliders->y + playerSTR->taille/2 - y + playerSTR->vit_y);
        couleur_bas  = getpixel(bufferCollision, playerSTR->x - colliders->x + playerSTR->taille/2 + x + playerSTR->vit_x, playerSTR->y - colliders->y + playerSTR->taille/2 + y + playerSTR->vit_y);

        ///Verification des pixels
        if((couleur_haut == MURCOLL ) || ( couleur_bas == MURCOLL ))
        {
            playerSTR->vit_y = - playerSTR->vit_y;
            if(playerSTR->vit_angle < 7) playerSTR->vit_angle += (float)playerSTR->vit_x/2;
            //return 0;
        }
        else if((couleur_haut == ADDCOLL) || ( couleur_bas == ADDCOLL))
        {
            grandirElem(ancre);
            deleteBonus(collec, playerSTR);
            score=score+50;
            return 0;
        }
        else if((couleur_haut == SPEEDCOLL) || ( couleur_bas == SPEEDCOLL))
        {
            accelElem(ancre,20);
            deleteBonus(collec, playerSTR);
            score=score+50;
            return 0;
        }
        else if((couleur_haut == MULTIPLIER) || (couleur_bas == MULTIPLIER))
        {
            b++;
            if(b >100)
            {
                b = 0;
                deleteBonus(collec, playerSTR) ;
                return 0;
            }
            score=score+50;
            deleteBonus(collec, playerSTR) ;
            return 1;
        }
        else if(couleur_haut == SCIECOLL || couleur_bas == SCIECOLL)
        {
            playerSTR->vivant = 0;
            return 0;
        }
        else if(couleur_haut == RETRECIR || couleur_bas == RETRECIR)
        {
            retrecirElem(ancre);
            deleteBonus(collec, playerSTR);
            score=score+50;
            return 0;
        }
    }
    for(x = rayon/2 ; x < rayon ; x ++)
    {
        //On calcule y en fonction de x (Theoreme de Pythagore):
        y =  sqrt( rayon * rayon - x * x);

        //Verification du pixel sur la partie haute, et basse du cercle:
        couleur_haut = getpixel(bufferCollision, playerSTR->x - colliders->x + playerSTR->taille/2 + x + playerSTR->vit_x, playerSTR->y - colliders->y + playerSTR->taille/2 - y + playerSTR->vit_y);
        couleur_bas  = getpixel(bufferCollision, playerSTR->x - colliders->x + playerSTR->taille/2 + x + playerSTR->vit_x, playerSTR->y - colliders->y + playerSTR->taille/2 + y + playerSTR->vit_y);

        ///Verification des pixels
        if((couleur_haut == MURCOLL ) || ( couleur_bas == MURCOLL))
        {
            playerSTR->vit_x = - playerSTR->vit_x * 0.25;
            playerSTR->vit_y = - playerSTR->vit_y;
            if(playerSTR->vit_angle < 7) playerSTR->vit_angle += (float)playerSTR->vit_x/2;
            //return 0;
        }
        else if((couleur_haut == ADDCOLL) || ( couleur_bas == ADDCOLL))
        {

            grandirElem(ancre);
            deleteBonus(collec, playerSTR);
            return 0;
        }
        else if((couleur_haut == SPEEDCOLL) || ( couleur_bas == SPEEDCOLL))
        {
            accelElem(ancre,20);
            deleteBonus(collec, playerSTR);
            return 0;
        }
        else if((couleur_haut == MULTIPLIER) || (couleur_bas == MULTIPLIER))
        {
            b++;
            if(b >100)
            {
                b = 0;
                return 0;
            }
            deleteBonus(collec, playerSTR) ;
            return 1;
        }
        else if(couleur_haut == SCIECOLL || couleur_bas == SCIECOLL)
        {
            playerSTR->vivant = 0;
            return 0;
        }
        else if(couleur_haut == RETRECIR || couleur_bas == RETRECIR)
        {
            retrecirElem(ancre); deleteBonus(collec, playerSTR);
            return 0;
        }
    }
    /*   ____|_
        /    | \
        |    | |   ----> Vect Vitesse X = -Vitesse X sur la partie 1/4 avant (En cas de choc frontal, l'inertie es retournée)
        \____|_/
        |    |
        |
        |--------------> On touche pas a la vitesse X sur les 3/4 arriere (l'inertie est consrvée)
    */
    return 0;
}

///Fonction de suppression des bonus, apres les avoir touchés
void deleteBonus(t_collec * collec, t_player * playerSTR)
{
    //Variable de parcours
    int i;
    //Parcours du tableau de bonus
    for(i=0; i<collec->nbBonus; i++)
    {
        //On verif les coordonnées des bonus
        if((collec->bonus[i]->x - playerSTR->x - playerSTR->taille/2 < 100 )&&
                (collec->bonus[i]->x - playerSTR->x - playerSTR->taille/2 > -100))
            collec->bonus[i]->vivant =0;
    }
}

///Ajout d'acceleration à tout les éléments de la liste
void accelElem (t_liste * ancre, int vitesse)
{
    //Parcours de la liste chainée
    t_liste *tmp = ancre;
    while(tmp != NULL)
    {
        //ajout de vitesse
        tmp->element->vit_x = vitesse;
        tmp = tmp->suivant;
    }
}

///Ajout de taille à tout les éléments de la liste
void grandirElem (t_liste * ancre)
{
    //Parcours de la liste chainée
    t_liste *tmp = ancre;
    while(tmp != NULL)
    {
        //Augmentation de la taille
        if(tmp->element->taille < 155)
            tmp->element->taille +=30;
        tmp = tmp->suivant;
    }
}

///Retrait de taille à tout les éléments de la liste
void retrecirElem (t_liste * ancre)
{
    //Parcours de la liste chainée
    t_liste *tmp = ancre;
    while(tmp != NULL)
    {
        //Augmentation de la taille
        if(tmp->element->taille > 95)
            tmp->element->taille -=30;
        tmp = tmp->suivant;
    }
}

///Fonction de verification de la mort
int verifDeath(t_player * playerSTR, t_decor * foreground)
{
    //On verifie les coordonnées de l'element
    if((playerSTR->x - foreground->x)< playerSTR->taille*(20/125 - 1))
    {
        //Suppression de l'élément
        playerSTR->vivant = 0;
        return playerSTR->numero;
    }
    else return 0;
}

///Fonction de modification de la vitesse et de la position de chaque perso
void movePlayer(int * scrolling, t_player * playerSTR, t_decor * foreground, int keyPressed, int niveau, t_liste *ancre,t_collec * collec, int *booleen, int*score)
{
    //Variable temporaire pour le calcul du scrolling
    int scrolltmp = 0;

    //Ajout de force en fonction de l'appuis ou pas des touches
    if(keyPressed)
    {
        //On donne une attaque au saut si le personnage descend deja tres vite
        if(playerSTR->vit_y > 0)
            playerSTR->vit_y -= ATKSPEED;
        //On ajoute une vitesse en x et y
        if ((playerSTR->y+playerSTR->vit_y>-playerSTR->taille/2) && (playerSTR->y+playerSTR->vit_y<SCREEN_H-playerSTR->taille/2))
            playerSTR->vit_y -= 0.5;
        playerSTR->vit_x += 0.25;
    }
    else
    {
        playerSTR->vit_y = (playerSTR->vit_y + 1)*0.95;
        //Incrementation ou decrementation progressive de la vitesse par rapport à la vitesse de croisiere ( 5 pixel/frame)
        //De plus, on augmente la vitesse su personnage quand il s'apprete à sortir de l'écran
        if       (( playerSTR->vit_x < 5) && (playerSTR->x-foreground->x >50))
            playerSTR->vit_x +=0.25;
        else if  (( playerSTR->vit_x > 5) && (playerSTR->x-foreground->x >50))
            playerSTR->vit_x -=0.25;
        else if  (( playerSTR->vit_x < 8) && (playerSTR->x-foreground->x <50))
            playerSTR->vit_x +=0.25;
    }

    //Verfication des collisions avec le decors
    if(verifColl(playerSTR,foreground, niveau,ancre,collec,score) == 1)
    {
        *booleen = 1;
    }
    else if(verifColl(playerSTR,foreground, niveau,ancre,collec,score) == 2)
    {
        *booleen = 2;
    }

    //Modification de la position en fonction de la vitesse tésultante (avec blindage haut et bas)
    if ((playerSTR->y+playerSTR->vit_y>-playerSTR->taille/2) && (playerSTR->y+playerSTR->vit_y<SCREEN_H-playerSTR->taille/2))
        playerSTR->y += playerSTR->vit_y;
    playerSTR->x += playerSTR->vit_x;

    //Calcul du scrolling sur le personnage courrant
    scrolltmp = (playerSTR->x-foreground->x <100)*5 +
                ((playerSTR->x-foreground->x >= 100) && (playerSTR->x-foreground->x <200))*6 +
                ((playerSTR->x-foreground->x >= 200) && (playerSTR->x-foreground->x <300))*7 +
                ((playerSTR->x-foreground->x >= 300) && (playerSTR->x-foreground->x <400))*8 +
                ((playerSTR->x-foreground->x >= 400) && (playerSTR->x-foreground->x <500))*9 +
                ((playerSTR->x-foreground->x >= 500) && (playerSTR->x-foreground->x <600))*15+
                ((playerSTR->x-foreground->x >= 600) && (playerSTR->x-foreground->x <700))*25+
                ((playerSTR->x-foreground->x >= 700) && (playerSTR->x-foreground->x <800))*50;

    //On garde uniquement la valeur la plus haute du scrolling à chaque tour de boucle
    if (scrolltmp > *scrolling)
        *scrolling = scrolltmp;

    //Modification de l'angle de rotation
    playerSTR->angle += playerSTR->vit_angle;
    playerSTR->vit_angle *= 0.98;
}

///Fonction de verification de perte , à chaque tour de boucle
int Perdu(t_liste *ancre)
{
    if(ancre == NULL)
    {
        return 1;
    }
    else return 0;
}


///Fonction de collision entre les element de la liste chainée
void CollisionJoueur(t_liste *ancre, int taille)
{
    t_liste *temp1 = NULL, *temp2 = NULL; /// 2 pointeurs pour 2 listes !
    int i;
    for(i=0; i<2; i++)
    {

        temp1 = ancre;
        while(temp1 != NULL)
        {
            temp2 = ancre;
            while(temp2 != NULL)
            {
                if(temp1 == temp2) temp2 = temp2->suivant; /// Si les 2 pointent la même chose, on change le 2e
                else
                {
                    ///On compare les 2 coordonnées, si elles se touchent, on les retire !
                    if((temp1->element->x > temp2->element->x)&&(temp1->element->x < temp2->element->x + taille))
                    {
                        if(rand()%2 == 0)
                            temp1->element->x += taille/5;
                        else temp1->element->x -= taille/5;
                    }
                    if((temp1->element->y > temp2->element->y)&&(temp1->element->y < temp2->element->y + taille/2))
                    {
                        if(rand()%2 == 0)
                            temp1->element->y -= taille/5;
                        else temp1->element->y += taille/5;
                    }
                    temp2 = temp2->suivant;
                }

            }
            temp1 = temp1->suivant;
        }
    }
}

///Fonction de reinitialisation du menu
void InitialiserMenu(t_menu *menu)
{
    menu->quitter = 0;
    menu->jouer = 0;
    menu->regarderScore = 0;
}

///Boucle de jeu!
int JouerNiveau(t_decor *fond, t_decor *decor, int niveau, t_liste *exemple, BITMAP *spritesBonus[NB_BONUS])
{
    //Variables
    t_liste *ancre = NULL;
    t_liste *tmp = NULL;
    t_liste *tmp2 = NULL;
    int scroll;
    int keyPressed = 0;
    int i;
    int vrai = 0;
    int pixel_map = 0;
    int numeroDuMort = 0;
    int nbElement = 0;
    int multiplier = 0;
    t_collec *collec = AllouerCollec(spritesBonus, niveau);
    int score =0;
    time_t temps_debut, temps_fin, temps_reel=0;

    //Initialisation des differents élement du programme
    ancre = NouvelElementFin(ancre);
    ChargerSprites(ancre->element, exemple->element);
    ancre->element->taille = 125;
    if(niveau == 0) pixel_map = 12000;
    else if(niveau == 1) pixel_map = 12000;
    else pixel_map = 6000;
    temps_debut=time(NULL);
    //Boucle de jeu
    while(!Perdu(ancre)&&(decor->x< pixel_map  - SCREEN_W ))
    {
        scroll = 0;

        //Affichage du décors
        clear_bitmap(page);
        clear_bitmap(bufferCollision);
        blit(fond->image[niveau], page, fond->x, fond->y, 0,0, SCREEN_W, SCREEN_H);
        masked_blit(decor->image[niveau], page, decor->x, decor->y, 0,0, SCREEN_W, SCREEN_H);
        blit(decor->image[niveau], bufferCollision, decor->x, decor->y, 0,0, SCREEN_W, SCREEN_H);

        //Generation des bonus

        for(i=0; i<collec->nbBonus; i++)
        {
            if(collec->bonus[i]->vivant == 1)
            {
                collec->bonus[i]->angle ++;
                //draw_sprite(page, collec->bonus[i]->image, collec->bonus[i]->x - decor->x, collec->bonus[i]->y);
                rotate_sprite(page,collec->bonus[i]->image, collec->bonus[i]->x - decor->x, collec->bonus[i]->y,itofix(collec->bonus[i]->angle));
                draw_sprite(bufferCollision, collec->bonus[i]->image, collec->bonus[i]->x - decor->x, collec->bonus[i]->y);
            }
        }


        //Lecture de l'entrée clavier par l'utilisateur
        if(key[KEY_SPACE])
            keyPressed = 1;
        else
            keyPressed = 0;

        //Parcours de la liste chainée
        tmp = ancre;
        while(tmp != NULL)
        {
            //Application des forces
            movePlayer(&scroll, tmp->element, decor, keyPressed, niveau,ancre,collec, &multiplier,&score);
            //Affichage des sprites
            if(keyPressed)
                rotate_scaled_sprite(page, tmp->element->sprite[PERSO_HAUT],tmp->element->x - decor->x, tmp->element->y, itofix(tmp->element->angle), ftofix((float)tmp->element->taille/125));
            else
                rotate_scaled_sprite(page, tmp->element->sprite[PERSO_BAS],tmp->element->x - decor->x, tmp->element->y, itofix(tmp->element->angle), ftofix((float)tmp->element->taille/125));
            //textprintf_ex(page, font, tmp->element->x -decor->x, tmp->element->y, makecol(255,255,255), -1, "%d", tmp->element->numero);
            nbElement = DeterminerNombreElement(ancre);
            if((DeterminerNombreElement(ancre)> 1)&&(vrai == 1))
            {
                CollisionJoueur(ancre, ancre->element->taille);
                vrai = 0;
            }
            numeroDuMort = verifDeath(tmp->element, decor);
            if((numeroDuMort == 1)&&(nbElement > 1))
            {
                tmp2 = ancre;
                ancre = ancre->suivant;
                free(tmp2->element);
                free(tmp2);
                tmp = ancre;
                tmp = tmp->suivant;
                ancre = DeterminerNumero(ancre);
            }
            else if(tmp->element->vivant == 0)
            {
                numeroDuMort = tmp->element->numero;
                tmp = tmp->suivant;
                ancre = SupprimerElementRecherche(ancre, numeroDuMort);
                ancre = DeterminerNumero(ancre);
            }
            else
                tmp = tmp->suivant;
        }
        //Blit du buffer sur l'ecran
        blit(page,screen, 0,0,0,0, SCREEN_W, SCREEN_H);


        if(multiplier == 1)
        {
            for(i=0;i<3;i++)
            {
                ancre = NouvelElementFin(ancre);
                tmp = RechercherElement(ancre, DeterminerNombreElement(ancre));
                ChargerSprites(tmp->element, ancre->element);
            }

            multiplier = 0;
            vrai = 1;
        }
        //Apllication du scroll
        decor->x+=scroll;
        fond->x+=scroll/2;
        if(Perdu(ancre))
            keyPressed = 3;

        //Delais entre chaque frame!
        rest(20);
    }
    //Sortie quand le joueur a gagné ou perdu
    ancre = SupprimerListe(ancre);
    LibererCollec(collec);
    if(keyPressed == 3)
        return 0;
    else
    {
         temps_fin=time(NULL);
            temps_reel=temps_fin-temps_debut;
            score=score+1000/sqrt(temps_reel);
            printf("%d",score);
            calculScore(niveau,score);
        if(niveau < 2)

            return niveau +1;



        else
        return -1;
    }
}
