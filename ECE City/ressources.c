#include "include.h"

t_eau *CreerChateauDEau()
{
    t_eau *chateau = NULL;

    chateau = malloc(sizeof(t_eau));
    if(chateau == NULL) exit(EXIT_FAILURE);

    chateau->coord = malloc(sizeof(t_position));
    if(chateau->coord == NULL) exit(EXIT_FAILURE);

    chateau->coord->x = mouse_x/20;
    chateau->coord->y = mouse_y/20;
    chateau->qtEau = QTE_EAU;

    return chateau;
}

t_elec *CreerCentrale()
{
    t_elec *centrale = NULL;

    centrale = malloc(sizeof(t_elec));
    if(centrale == NULL) exit(EXIT_FAILURE);

    centrale->coord = malloc(sizeof(t_position));
    if(centrale->coord == NULL) exit(EXIT_FAILURE);

    centrale->coord->x = mouse_x/20;
    centrale->coord->y = mouse_y/20;
    centrale->qtElec = QTE_ELEC;

    return centrale;
}

t_eau **AllouerTableauChateauDEau()
{
    t_eau **tab = NULL;
    int i;

    tab = malloc(NB_CHATEAU_INITIAL*sizeof(t_eau*));
    if(tab == NULL) exit(EXIT_FAILURE);

    for(i=0; i<NB_CHATEAU_INITIAL; i++)
    {
        tab[i] = NULL;
    }

    return tab;
}

t_elec **AllouerTableauCentrale()
{
    t_elec **tab = NULL;
    int i;

    tab = malloc(NB_CENTRALE_INITIAL*sizeof(t_elec*));
    if(tab == NULL) exit(EXIT_FAILURE);

    for(i=0; i<NB_CENTRALE_INITIAL; i++)
    {
        tab[i] = NULL;
    }

    return tab;
}

void SupprimerChateauDEau(t_eau *ChateauDEau)
{
    free(ChateauDEau);
    ChateauDEau = NULL;
}

void SupprimerTableauChateauDeau(t_eau **tab, int tailleActuelle)
{
    int i;
    for(i=0; i<tailleActuelle; i++)
    {
        SupprimerChateauDEau(tab[i]);
    }
    free(tab);
    tab = NULL;
}

void SupprimerCentrale(t_elec* centrale)
{
    free(centrale);
    centrale = NULL;
}

void SupprimerTableauCentrale(t_elec **centrale, int tailleActuelle)
{
    int i;
    for(i=0; i<tailleActuelle; i++)
    {
        SupprimerCentrale(centrale[i]);
    }
    free(centrale);
    centrale = NULL;
}

t_eau **AugmenterTailleTableauChateauDEau(t_eau **tab, int *tailleActuelle, int *nbChat)
{
    tab = realloc(tab, *tailleActuelle*3/2*sizeof(t_eau**));
    *tailleActuelle = *tailleActuelle*3/2;

    *nbChat = *nbChat + 1;
    return tab;
}

t_elec **AugmenterTailleTableauCentrales(t_elec **tab, int *tailleActuelle, int *nbCent)
{
    tab = realloc(tab, *tailleActuelle*3/2*sizeof(t_elec**));
    *tailleActuelle = *tailleActuelle*3/2;

    *nbCent = *nbCent + 1 ;
    return tab;
}

t_chateaux *AllouerChateaux()
{
    t_chateaux *chatte = NULL;

    chatte = malloc(sizeof(t_chateaux));
    if(chatte == NULL) exit(EXIT_FAILURE);
    chatte->chateaux = AllouerTableauChateauDEau();
    chatte->nb_chateaux = 0;
    chatte->tailleTableauChateau = NB_CHATEAU_INITIAL;
    chatte->image = ChargerImageChateau();

    return chatte;
}

t_centrales *AllouerCentrales()
{
    t_centrales *centre = NULL;

    centre = malloc(sizeof(t_centrales));
    if(centre == NULL) exit(EXIT_FAILURE);

    centre->centrales = AllouerTableauCentrale();
    centre->nb_centrales = 0;
    centre->tailleTableauCentrale = NB_CENTRALE_INITIAL;
    centre->image = ChargerImageCentrale();

    return centre;
}

t_eau **AjouterChateau(t_eau **tab, int *tailleActuelle, int *nbChat, int **grille)
{

    int i = 0;
    int j,g;

    while(tab[i] != NULL)
    {
        i++;
    }

    if(i== *tailleActuelle)
    {
        tab = AugmenterTailleTableauChateauDEau(tab, tailleActuelle, nbChat);
        tab[i+1] = CreerChateauDEau();
        *nbChat = *nbChat + 1 ;
    }

    else
    {
        tab[i] = CreerChateauDEau();
        *nbChat = *nbChat + 1 ;
    }
    for(j=0; j<CASE_RESSOURCES_X; j++)
    {
        for(g=0; g<CASE_RESSOURCES_Y; g++)
        {
            grille[tab[i]->coord->x+j][tab[i]->coord->y+g] = CHATEAU_EAU;
        }
    }
    return tab;

}

t_elec **AjouterCentrale(t_elec **tab, int *tailleActuelle, int *nbCentre, int **grille)
{
    int i = 0;
    int j,g;

    while(tab[i] != NULL)
    {
        i++;
    }

    if(i == *tailleActuelle)
    {
        tab = AugmenterTailleTableauCentrales(tab, tailleActuelle, nbCentre);
        tab[i+1] = CreerCentrale();
        *nbCentre = *nbCentre + 1;

    }
    else
    {
        tab[i] = CreerCentrale();
        *nbCentre = *nbCentre + 1;
    }
    for(j=0; j<CASE_RESSOURCES_Y; j++)
    {
        for(g=0; g<CASE_RESSOURCES_X; g++)
        {
            grille[tab[i]->coord->x+j][tab[i]->coord->y+g] = CENTRALE;
        }
    }
    return tab;
}

BITMAP *ChargerImageChateau()
{
    BITMAP *bit = NULL;

    bit = load_bitmap("images/chateau_d_eau.bmp", NULL);

    return bit;
}

BITMAP *ChargerImageCentrale()
{
    BITMAP *bit = NULL;

    bit = load_bitmap("images/centrale.bmp", NULL);

    return bit;
}

void SupprimerCentraleSelectionne(t_elec **tab, int x, int y, int tailleTableau, int **matrice)
{
    int i;
    int vrai = 0;
    for(i=0; i<tailleTableau; i++)
    {
        if(tab[i] != NULL)
        {
            vrai = VerifierCentraleSelectionne(tab[i], x, y);
            if(vrai == 1) break;
        }
    }

    if(vrai)
    {
        RemettreCaseLibreCentrale(matrice, tab[i]);
        SupprimerCentrale(tab[i]);
    }
    tab[i] = NULL;
}

void SupprimerChateauSelectionne(t_eau **tab , int x, int y , int tailleTableau, int **matrice)
{
    int i;
    int vrai = 0;
    for(i=0; i<tailleTableau; i++)
    {
        if(tab[i] != NULL)
        {
            vrai = VerifierChateauSelectionne(tab[i], x, y);
            if(vrai == 1) break;
        }
    }

    if(vrai)
    {
        RemettreCaseLibreChateau(matrice, tab[i]);
        SupprimerChateauDEau(tab[i]);
    }
    tab[i] = NULL;
}

int VerifierCentraleSelectionne(t_elec *hab, int x, int y)
{
    int i, j;
    int vrai = 0;

    for(i=0; i<CASE_RESSOURCES_Y; i++)
    {
        for(j=0; j<CASE_RESSOURCES_X; j++)
        {
            if(hab->coord->x == x/20 - i && hab->coord->y == y/20 - j)
                vrai = 1;
        }
    }

    return vrai;
}

void RemettreCaseLibreCentrale(int **matrice, t_elec *hab)
{
    int i, j;
    for(i=0; i<CASE_RESSOURCES_Y; i++)
    {
        for(j=0; j<CASE_RESSOURCES_X; j++)
        {
            matrice[hab->coord->x+i][hab->coord->y+j] = -1;
        }
    }
}

int VerifierChateauSelectionne(t_eau *hab, int x, int y)
{
    int i, j;
    int vrai = 0;

    for(i=0; i<CASE_RESSOURCES_X; i++)
    {
        for(j=0; j<CASE_RESSOURCES_Y; j++)
        {
            if(hab->coord->x == x/20 - i && hab->coord->y == y/20 - j)
                vrai = 1;
        }
    }

    return vrai;
}

void RemettreCaseLibreChateau(int **matrice, t_eau *hab)
{
    int i, j;
    for(i=0; i<CASE_RESSOURCES_X; i++)
    {
        for(j=0; j<CASE_RESSOURCES_Y; j++)
        {
            matrice[hab->coord->x+i][hab->coord->y+j] = -1;
        }
    }
}

void gestion_eau(t_eau eau,int**matrice, char** adjascence, t_batiments*batiment)
{
    int i,j,k,mini=0,indice_mini=0;
    int arret=0,arret_maison=0;
    int chemin_min[batiment->nb_habitation];
    for(i=0; i<batiment->nb_habitation; i++)
    {
        chemin_min[i]=0;
    }
    for(i=eau.coord->x; i<(eau.coord->x+CASE_RESSOURCES_X)&&(arret!=1); i++)
    {
        if(matrice[i][eau.coord->y-1]==ROUTE)
        {
            arret=1;
            for(j=0; j<batiment->nb_habitation; j++)
            {
                arret_maison=0;
                for(k=batiment->habitations[j]->coord->x; k<(batiment->habitations[j]->coord->x+CASE_BATIMENTS)&&(arret_maison!=1); k++)
                {
                    if(matrice[k][batiment->habitations[j]->coord->y-1]==ROUTE)
                    {
                        chemin_min[j]=dijkstra(adjascence,i*TAILLE_X+eau.coord->y-1,k*TAILLE_X+batiment->habitations[j]->coord->y-1);
                        arret_maison=1;
                    }
                    if((matrice[k][batiment->habitations[j]->coord->y+CASE_BATIMENTS]==ROUTE)&&(arret_maison!=1))
                    {
                        chemin_min[j]=dijkstra(adjascence,i*TAILLE_X+eau.coord->y-1,k*TAILLE_X+batiment->habitations[j]->coord->y+CASE_BATIMENTS);
                        arret_maison=1;
                    }
                }
                for(k=batiment->habitations[j]->coord->y; k<(batiment->habitations[j]->coord->y+CASE_BATIMENTS)&&(arret_maison!=1); k++)
                {
                    if(matrice[k][batiment->habitations[j]->coord->x-1]==ROUTE)
                    {
                        chemin_min[j]=dijkstra(adjascence,i*TAILLE_X+eau.coord->y-1,(batiment->habitations[j]->coord->x-1)*TAILLE_X+k);
                        arret_maison=1;
                    }
                    if((matrice[k][batiment->habitations[j]->coord->x+CASE_BATIMENTS]==ROUTE)&&(arret_maison!=1))
                    {
                        chemin_min[j]=dijkstra(adjascence,i*TAILLE_X+eau.coord->y-1,(batiment->habitations[j]->coord->x+CASE_BATIMENTS)*TAILLE_X+k);
                        arret_maison=1;
                    }
                }
            }
        }
        if((matrice[i][eau.coord->y+CASE_BATIMENTS]==ROUTE)&&(arret!=1))
        {
            arret=1;
            for(j=0; j<batiment->nb_habitation; j++)
            {
                arret_maison=0;
                for(k=batiment->habitations[j]->coord->x; k<(batiment->habitations[j]->coord->x+CASE_BATIMENTS)&&(arret_maison!=1); k++)
                {
                    if(matrice[k][batiment->habitations[j]->coord->y-1]==ROUTE)
                    {
                        chemin_min[j]=dijkstra(adjascence,i*TAILLE_X+eau.coord->y-1,k*TAILLE_X+batiment->habitations[j]->coord->y-1);
                        arret_maison=1;
                    }
                    if((matrice[k][batiment->habitations[j]->coord->y+CASE_BATIMENTS]==ROUTE)&&(arret_maison!=1))
                    {
                        chemin_min[j]=dijkstra(adjascence,i*TAILLE_X+eau.coord->y-1,k*TAILLE_X+batiment->habitations[j]->coord->y+CASE_BATIMENTS);
                        arret_maison=1;
                    }
                }
                for(k=batiment->habitations[j]->coord->y; k<(batiment->habitations[j]->coord->y+CASE_BATIMENTS)&&(arret_maison!=1); k++)
                {
                    if(matrice[k][batiment->habitations[j]->coord->x-1]==ROUTE)
                    {
                        chemin_min[j]=dijkstra(adjascence,i*TAILLE_X+eau.coord->y-1,(batiment->habitations[j]->coord->x-1)*TAILLE_X+k);
                        arret_maison=1;
                    }
                    if((matrice[k][batiment->habitations[j]->coord->x+CASE_BATIMENTS]==ROUTE)&&(arret_maison!=1))
                    {
                        chemin_min[j]=dijkstra(adjascence,i*TAILLE_X+eau.coord->y-1,(batiment->habitations[j]->coord->x+CASE_BATIMENTS)*TAILLE_X+k);
                        arret_maison=1;
                    }
                }
            }
        }

    }
    for(i=eau.coord->y; i<(eau.coord->y+CASE_RESSOURCES_Y)&&(arret!=1); i++)
    {
        if(matrice[eau.coord->x-1][i]==ROUTE)
        {
            arret=1;
            for(j=0; j<batiment->nb_habitation; j++)
            {
                arret_maison=0;
                for(k=batiment->habitations[j]->coord->x; k<(batiment->habitations[j]->coord->x+CASE_BATIMENTS)&&(arret_maison!=1); k++)
                {
                    if(matrice[k][batiment->habitations[j]->coord->y-1]==ROUTE)
                    {
                        chemin_min[j]=dijkstra(adjascence,i*TAILLE_X+eau.coord->y-1,k*TAILLE_X+batiment->habitations[j]->coord->y-1);
                        arret_maison=1;
                    }
                    if((matrice[k][batiment->habitations[j]->coord->y+CASE_BATIMENTS]==ROUTE)&&(arret_maison!=1))
                    {
                        chemin_min[j]=dijkstra(adjascence,i*TAILLE_X+eau.coord->y-1,k*TAILLE_X+batiment->habitations[j]->coord->y+CASE_BATIMENTS);
                        arret_maison=1;
                    }
                }
                for(k=batiment->habitations[j]->coord->y; k<(batiment->habitations[j]->coord->y+CASE_BATIMENTS)&&(arret_maison!=1); k++)
                {
                    if(matrice[k][batiment->habitations[j]->coord->x-1]==ROUTE)
                    {
                        chemin_min[j]=dijkstra(adjascence,i*TAILLE_X+eau.coord->y-1,(batiment->habitations[j]->coord->x-1)*TAILLE_X+k);
                        arret_maison=1;
                    }
                    if((matrice[k][batiment->habitations[j]->coord->x+CASE_BATIMENTS]==ROUTE)&&(arret_maison!=1))
                    {
                        chemin_min[j]=dijkstra(adjascence,i*TAILLE_X+eau.coord->y-1,(batiment->habitations[j]->coord->x+CASE_BATIMENTS)*TAILLE_X+k);
                        arret_maison=1;
                    }
                }
            }
        }
        if((matrice[eau.coord->x+CASE_BATIMENTS][i]==ROUTE)&&(arret!=1))
        {
            arret=1;
            for(j=0; j<batiment->nb_habitation; j++)
            {
                arret_maison=0;
                for(k=batiment->habitations[j]->coord->x; k<(batiment->habitations[j]->coord->x+CASE_BATIMENTS)&&(arret_maison!=1); k++)
                {
                    if(matrice[k][batiment->habitations[j]->coord->y-1]==ROUTE)
                    {
                        chemin_min[j]=dijkstra(adjascence,i*TAILLE_X+eau.coord->y-1,k*TAILLE_X+batiment->habitations[j]->coord->y-1);
                        arret_maison=1;
                    }
                    if((matrice[k][batiment->habitations[j]->coord->y+CASE_BATIMENTS]==ROUTE)&&(arret_maison!=1))
                    {
                        chemin_min[j]=dijkstra(adjascence,i*TAILLE_X+eau.coord->y-1,k*TAILLE_X+batiment->habitations[j]->coord->y+CASE_BATIMENTS);
                        arret_maison=1;
                    }
                }
                for(k=batiment->habitations[j]->coord->y; k<(batiment->habitations[j]->coord->y+CASE_BATIMENTS)&&(arret_maison!=1); k++)
                {
                    if(matrice[k][batiment->habitations[j]->coord->x-1]==ROUTE)
                    {
                        chemin_min[j]=dijkstra(adjascence,i*TAILLE_X+eau.coord->y-1,(batiment->habitations[j]->coord->x-1)*TAILLE_X+k);
                        arret_maison=1;
                    }
                    if((matrice[k][batiment->habitations[j]->coord->x+CASE_BATIMENTS]==ROUTE)&&(arret_maison!=1))
                    {
                        chemin_min[j]=dijkstra(adjascence,i*TAILLE_X+eau.coord->y-1,(batiment->habitations[j]->coord->x+CASE_BATIMENTS)*TAILLE_X+k);
                        arret_maison=1;
                    }
                }
            }
        }
    }
    while(arret==1)
    {
        mini=chemin_min[0];
        indice_mini=0;
        for(i=0; i<batiment->nb_habitation; i++)
        {
            if(mini>chemin_min[i])
            {
                mini=chemin_min[i];
                indice_mini=i;
            }
        }
        if(mini==INFINI) arret=0;
        chemin_min[indice_mini]=INFINI;
        if((batiment->habitations[indice_mini]->eau<batiment->habitations[indice_mini]->population)&&(arret!=0))
        {
            if(eau.qtEau<=(batiment->habitations[indice_mini]->population-batiment->habitations[indice_mini]->eau))
            {
                arret=0;
                batiment->habitations[indice_mini]->eau=eau.qtEau;
                eau.qtEau=0;
            }
            else
            {
                eau.qtEau-=(batiment->habitations[indice_mini]->population-batiment->habitations[indice_mini]->eau);
                batiment->habitations[indice_mini]->eau=batiment->habitations[indice_mini]->population;
            }
        }
    }
}

void gestion_elec(t_elec elec,int**matrice, char** adjascence, t_batiments*batiment)
{
    int i,j,k,mini=0,indice_mini=0;
    int arret=0,arret_maison=0;
    int chemin_min[batiment->nb_habitation];
    for(i=0; i<batiment->nb_habitation; i++)
    {
        chemin_min[i]=0;
    }
    for(i=elec.coord->x; i<(elec.coord->x+CASE_RESSOURCES_X)&&(arret!=1); i++)
    {
        if(matrice[i][elec.coord->y-1]==ROUTE)
        {
            arret=1;
            for(j=0; j<batiment->nb_habitation; j++)
            {
                arret_maison=0;
                for(k=batiment->habitations[j]->coord->x; k<(batiment->habitations[j]->coord->x+CASE_BATIMENTS)&&(arret_maison!=1); k++)
                {
                    if(matrice[k][batiment->habitations[j]->coord->y-1]==ROUTE)
                    {
                        chemin_min[j]=dijkstra(adjascence,i*TAILLE_X+elec.coord->y-1,k*TAILLE_X+batiment->habitations[j]->coord->y-1);
                        arret_maison=1;
                    }
                    if((matrice[k][batiment->habitations[j]->coord->y+CASE_BATIMENTS]==ROUTE)&&(arret_maison!=1))
                    {
                        chemin_min[j]=dijkstra(adjascence,i*TAILLE_X+elec.coord->y-1,k*TAILLE_X+batiment->habitations[j]->coord->y+CASE_BATIMENTS);
                        arret_maison=1;
                    }
                }
                for(k=batiment->habitations[j]->coord->y; k<(batiment->habitations[j]->coord->y+CASE_BATIMENTS)&&(arret_maison!=1); k++)
                {
                    if(matrice[k][batiment->habitations[j]->coord->x-1]==ROUTE)
                    {
                        chemin_min[j]=dijkstra(adjascence,i*TAILLE_X+elec.coord->y-1,(batiment->habitations[j]->coord->x-1)*TAILLE_X+k);
                        arret_maison=1;
                    }
                    if((matrice[k][batiment->habitations[j]->coord->x+CASE_BATIMENTS]==ROUTE)&&(arret_maison!=1))
                    {
                        chemin_min[j]=dijkstra(adjascence,i*TAILLE_X+elec.coord->y-1,(batiment->habitations[j]->coord->x+CASE_BATIMENTS)*TAILLE_X+k);
                        arret_maison=1;
                    }
                }
            }
        }
        if((matrice[i][elec.coord->y+CASE_BATIMENTS]==ROUTE)&&(arret!=1))
        {
            arret=1;
            for(j=0; j<batiment->nb_habitation; j++)
            {
                arret_maison=0;
                for(k=batiment->habitations[j]->coord->x; k<(batiment->habitations[j]->coord->x+CASE_BATIMENTS)&&(arret_maison!=1); k++)
                {
                    if(matrice[k][batiment->habitations[j]->coord->y-1]==ROUTE)
                    {
                        chemin_min[j]=dijkstra(adjascence,i*TAILLE_X+elec.coord->y-1,k*TAILLE_X+batiment->habitations[j]->coord->y-1);
                        arret_maison=1;
                    }
                    if((matrice[k][batiment->habitations[j]->coord->y+CASE_BATIMENTS]==ROUTE)&&(arret_maison!=1))
                    {
                        chemin_min[j]=dijkstra(adjascence,i*TAILLE_X+elec.coord->y-1,k*TAILLE_X+batiment->habitations[j]->coord->y+CASE_BATIMENTS);
                        arret_maison=1;
                    }
                }
                for(k=batiment->habitations[j]->coord->y; k<(batiment->habitations[j]->coord->y+CASE_BATIMENTS)&&(arret_maison!=1); k++)
                {
                    if(matrice[k][batiment->habitations[j]->coord->x-1]==ROUTE)
                    {
                        chemin_min[j]=dijkstra(adjascence,i*TAILLE_X+elec.coord->y-1,(batiment->habitations[j]->coord->x-1)*TAILLE_X+k);
                        arret_maison=1;
                    }
                    if((matrice[k][batiment->habitations[j]->coord->x+CASE_BATIMENTS]==ROUTE)&&(arret_maison!=1))
                    {
                        chemin_min[j]=dijkstra(adjascence,i*TAILLE_X+elec.coord->y-1,(batiment->habitations[j]->coord->x+CASE_BATIMENTS)*TAILLE_X+k);
                        arret_maison=1;
                    }
                }
            }
        }

    }
    for(i=elec.coord->y; i<(elec.coord->y+CASE_RESSOURCES_Y)&&(arret!=1); i++)
    {
        if(matrice[elec.coord->x-1][i]==ROUTE)
        {
            arret=1;
            for(j=0; j<batiment->nb_habitation; j++)
            {
                arret_maison=0;
                for(k=batiment->habitations[j]->coord->x; k<(batiment->habitations[j]->coord->x+CASE_BATIMENTS)&&(arret_maison!=1); k++)
                {
                    if(matrice[k][batiment->habitations[j]->coord->y-1]==ROUTE)
                    {
                        chemin_min[j]=dijkstra(adjascence,i*TAILLE_X+elec.coord->y-1,k*TAILLE_X+batiment->habitations[j]->coord->y-1);
                        arret_maison=1;
                    }
                    if((matrice[k][batiment->habitations[j]->coord->y+CASE_BATIMENTS]==ROUTE)&&(arret_maison!=1))
                    {
                        chemin_min[j]=dijkstra(adjascence,i*TAILLE_X+elec.coord->y-1,k*TAILLE_X+batiment->habitations[j]->coord->y+CASE_BATIMENTS);
                        arret_maison=1;
                    }
                }
                for(k=batiment->habitations[j]->coord->y; k<(batiment->habitations[j]->coord->y+CASE_BATIMENTS)&&(arret_maison!=1); k++)
                {
                    if(matrice[k][batiment->habitations[j]->coord->x-1]==ROUTE)
                    {
                        chemin_min[j]=dijkstra(adjascence,i*TAILLE_X+elec.coord->y-1,(batiment->habitations[j]->coord->x-1)*TAILLE_X+k);
                        arret_maison=1;
                    }
                    if((matrice[k][batiment->habitations[j]->coord->x+CASE_BATIMENTS]==ROUTE)&&(arret_maison!=1))
                    {
                        chemin_min[j]=dijkstra(adjascence,i*TAILLE_X+elec.coord->y-1,(batiment->habitations[j]->coord->x+CASE_BATIMENTS)*TAILLE_X+k);
                        arret_maison=1;
                    }
                }
            }
        }
        if((matrice[elec.coord->x+CASE_BATIMENTS][i]==ROUTE)&&(arret!=1))
        {
            arret=1;
            for(j=0; j<batiment->nb_habitation; j++)
            {
                arret_maison=0;
                for(k=batiment->habitations[j]->coord->x; k<(batiment->habitations[j]->coord->x+CASE_BATIMENTS)&&(arret_maison!=1); k++)
                {
                    if(matrice[k][batiment->habitations[j]->coord->y-1]==ROUTE)
                    {
                        chemin_min[j]=dijkstra(adjascence,i*TAILLE_X+elec.coord->y-1,k*TAILLE_X+batiment->habitations[j]->coord->y-1);
                        arret_maison=1;
                    }
                    if((matrice[k][batiment->habitations[j]->coord->y+CASE_BATIMENTS]==ROUTE)&&(arret_maison!=1))
                    {
                        chemin_min[j]=dijkstra(adjascence,i*TAILLE_X+elec.coord->y-1,k*TAILLE_X+batiment->habitations[j]->coord->y+CASE_BATIMENTS);
                        arret_maison=1;
                    }
                }
                for(k=batiment->habitations[j]->coord->y; k<(batiment->habitations[j]->coord->y+CASE_BATIMENTS)&&(arret_maison!=1); k++)
                {
                    if(matrice[k][batiment->habitations[j]->coord->x-1]==ROUTE)
                    {
                        chemin_min[j]=dijkstra(adjascence,i*TAILLE_X+elec.coord->y-1,(batiment->habitations[j]->coord->x-1)*TAILLE_X+k);
                        arret_maison=1;
                    }
                    if((matrice[k][batiment->habitations[j]->coord->x+CASE_BATIMENTS]==ROUTE)&&(arret_maison!=1))
                    {
                        chemin_min[j]=dijkstra(adjascence,i*TAILLE_X+elec.coord->y-1,(batiment->habitations[j]->coord->x+CASE_BATIMENTS)*TAILLE_X+k);
                        arret_maison=1;
                    }
                }
            }
        }
    }
    printf("HAB :%d\n",batiment->nb_habitation);
    while(arret==1)
    {
        mini=chemin_min[0];
        indice_mini=0;
        for(i=0; i<batiment->nb_habitation; i++)
        {
            if(mini>chemin_min[i])
            {
                mini=chemin_min[i];
                indice_mini=i;
            }
            printf("chemin[%d]=%d\n",i,chemin_min[i]);
        }
        if(mini==INFINI) arret=0;
        chemin_min[indice_mini]=INFINI;
        if((batiment->habitations[indice_mini]->elec<batiment->habitations[indice_mini]->population)&&(arret!=0))
        {
            if(elec.qtElec<=(batiment->habitations[indice_mini]->population-batiment->habitations[indice_mini]->elec))
            {
                arret=0;
            }
            else
            {
                elec.qtElec-=(batiment->habitations[indice_mini]->population-batiment->habitations[indice_mini]->elec);
                batiment->habitations[indice_mini]->elec=batiment->habitations[indice_mini]->population;
            }
        }
    }
}
