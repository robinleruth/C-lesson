#include "include.h"

void lancerToutAllegro()
{
    allegro_init();
    install_keyboard();
    install_mouse();
    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,LARGEUR,HAUTEUR,0,0)!=0)
    {
        allegro_message("probleme mode graphique : %s", allegro_error);
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    clear_to_color(screen,makecol(255,255,255));
}

BITMAP* creation_calque()
{
    BITMAP* image;
    image = create_bitmap(LARGEUR,HAUTEUR);
    clear_to_color(image,makecol(255,0,255));
    return image;
}

void InitialiserCalques()
{
    calque_batiment = creation_calque();
    calque_grille = creation_calque();
    calque_routes = creation_calque();
    calque_ressources = creation_calque();
    buffer = create_bitmap(LARGEUR, HAUTEUR);
}

void afficher_route(int x, int y, int** grille, BITMAP **bibroute)
{
    int route_disposition=0 ;
    if(x>0 && x < TAILLE_X)
    {
        if(grille[x-1][y]==ROUTE) route_disposition+=8;

        if(grille[x+1][y]==ROUTE) route_disposition+=2;
    }

    if(y>0 && y < TAILLE_Y)
    {
        if(grille[x][y-1]==ROUTE) route_disposition+=1;

        if(grille[x][y+1]==ROUTE) route_disposition+=4;
    }
    blit(bibroute[route_disposition],calque_routes,0,0,x*20, y*20,WIDTH,HEIGHT);
}

void remplissage_calque_route(int** grille, t_routes** routes, int nbroutes, BITMAP **bibroute)
{
    clear_to_color(calque_routes,makecol(255,0,255));
    int i;
    for(i=0; i<nbroutes; i++)
    {
        if(routes[i] != NULL)
            afficher_route(routes[i]->coord->x,routes[i]->coord->y,grille, bibroute);
    }
}


void dessin_matrice(BITMAP*calque)
{
    int i;
    for(i=0; i<TAILLE_X; i++)
    {
        line(calque,i*20,0,i*20,HAUTEUR,0);
    }
    for(i=0; i<TAILLE_Y; i++)
    {
        line(calque,0,i*20,LARGEUR,i*20,0);
    }
}

void AfficherBatiments(BITMAP **tab, t_batiments *batiments)
{
    int i;
    for(i=0; i < batiments->tailleTableau; i++)
    {
        if(batiments->habitations[i] != NULL)
        {
            switch(batiments->habitations[i]->stade)
            {
            case TERRAIN_VAGUE:
                blit(tab[TERRAIN_VAGUE], calque_batiment, 0, 0, batiments->habitations[i]->coord->x*20, batiments->habitations[i]->coord->y*20, LONGUEUR_BATIMENTS, LARGEUR_BATIMENTS);
                break;
            case CABANE:
                blit(tab[CABANE], calque_batiment, 0, 0, batiments->habitations[i]->coord->x*20, batiments->habitations[i]->coord->y*20, LONGUEUR_BATIMENTS, LARGEUR_BATIMENTS);
                break;
            case MAISON:
                blit(tab[MAISON], calque_batiment, 0, 0, batiments->habitations[i]->coord->x*20, batiments->habitations[i]->coord->y*20, LONGUEUR_BATIMENTS, LARGEUR_BATIMENTS);
                break;
            case IMMEUBLE:
                blit(tab[IMMEUBLE], calque_batiment, 0, 0, batiments->habitations[i]->coord->x*20, batiments->habitations[i]->coord->y*20, LONGUEUR_BATIMENTS, LARGEUR_BATIMENTS);
                break;
            case GRATTE_CIEL:
                blit(tab[GRATTE_CIEL], calque_batiment, 0, 0, batiments->habitations[i]->coord->x*20, batiments->habitations[i]->coord->y*20, LONGUEUR_BATIMENTS, LARGEUR_BATIMENTS);
                break;
            }
        }
    }
}

void AfficherRessources(t_chateaux *chat, t_centrales *elec)
{
    int i;
    for(i=0; i<chat->tailleTableauChateau; i++)
    {
        if(chat->chateaux[i] != NULL)
        {
            blit(chat->image, calque_ressources, 0, 0, chat->chateaux[i]->coord->x*20, chat->chateaux[i]->coord->y*20, LONGUEUR_RESSOURCE, LARGEUR_RESSOURCE);
        }
    }
    for(i=0; i<elec->tailleTableauCentrale; i++)
    {
        if(elec->centrales[i] != NULL)
        {
            blit(elec->image, calque_ressources, 0, 0, elec->centrales[i]->coord->x*20, elec->centrales[i]->coord->y*20, LARGEUR_RESSOURCE, LONGUEUR_RESSOURCE);
        }
    }
}

void affichage_global(BITMAP*herbe, int modeaffichage,BITMAP* pointeur)
{
    int i,j;
    for(i=0; i<TAILLE_X; i++)
    {
        for(j=0; j<TAILLE_Y; j++)
        {
            blit(herbe,buffer,0,0,i*20,j*20,LARGEUR,HAUTEUR);
        }
    }

    if(modeaffichage>=8)
    {
        masked_blit(calque_grille,buffer,0,0,0,0,LARGEUR,HAUTEUR);
        modeaffichage-=8;
    }
    if(modeaffichage>=4)
    {
        masked_blit(calque_ressources, buffer, 0, 0, 0, 0, LARGEUR, HAUTEUR);
        modeaffichage-=4;
    }
    if(modeaffichage>=2)
    {
        masked_blit(calque_batiment, buffer, 0, 0, 0, 0, LARGEUR, HAUTEUR);
        modeaffichage-=2;
    }
    if(modeaffichage>=1)
    {
        masked_blit(calque_routes,buffer,0,0,0,0,LARGEUR,HAUTEUR);
    }
    masked_blit(pointeur,buffer,0,0,mouse_x,mouse_y,LARGEUR,HAUTEUR);
    blit(buffer,screen,0,0,0,0,LARGEUR,HAUTEUR);
}

void choixmodeaffichage(int* mode)
{
    if(key[KEY_G])
    {
        if(*mode>=8)
        {
            *mode-=8;
        }
        else *mode+=8;
    }
    if(key[KEY_S])
    {
        if(((*mode)%8)%4>=2)
        {
            * mode-=2;
        }
        else *mode+=2;
    }
    if(key[KEY_D])
    {
        if((*mode)%8>=4)
        {
            *mode-=4;
        }
        else *mode+=4;
    }
    if(key[KEY_F])
    {
        if((((*mode)%8)%4)%2>=1)
        {
            *mode-=1;
        }
        else *mode+=1;
    }
}
