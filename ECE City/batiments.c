#include "include.h"

t_batiments *AllouerBatiments()
{
    t_batiments *bat = NULL;

    bat = malloc(1*sizeof(t_batiments));
    if(bat == NULL) exit(EXIT_FAILURE);

    bat->habitations = AllouerTableauHabitation();
    bat->nb_habitation = 0;
    bat->tailleTableau = NB_HABITATION_INITIAL;
    bat->imagesBatiments = ChargerImage("stade");

    return bat;
}

t_habitation **AllouerTableauHabitation()
{
    t_habitation **tab = NULL;

    tab = malloc(NB_HABITATION_INITIAL*sizeof(t_habitation*));
    if(tab == NULL) exit(EXIT_FAILURE);

    InitialiserTableauHabitation(tab);

    return tab;
}

void InitialiserTableauHabitation(struct habitation **tab)
{
    int i;

    for(i=0; i<NB_HABITATION_INITIAL; i++)
    {
        tab[i]=NULL;
    }
}


t_habitation **AugmenterTailleTableau(struct habitation **tab, int *tailleActuelle, int nbHab)
{
    int i;
    tab = realloc(tab, *tailleActuelle*3/2*sizeof(t_habitation**));
    *tailleActuelle = *tailleActuelle*3/2;
    for(i= nbHab ; i <= *tailleActuelle; i++)
    {
        tab[i] = NULL;
    }

    return tab;
}

int RecupererNbHabitation(t_habitation **tab, int tailleActuelle)
{
    int compteur = 0;
    int i;

    for(i=0; i<tailleActuelle; i++)
    {
        if(tab[i] != NULL) compteur++;
    }

    return compteur;
}

t_habitation **AjouterHabitation(struct habitation **tab, int *tailleActuelle, int *nbHab, int **grille)
{
    int i = 0;
    int j, g;

    while(tab[i] != NULL && i < *tailleActuelle)
    {
        i++;
    }
    if(i == *tailleActuelle)
    {
        tab = AugmenterTailleTableau(tab, tailleActuelle, *nbHab);
        tab[i] = CreerHabitation();
        *nbHab = *nbHab + 1;
    }
    else
    {
        tab[i] = CreerHabitation();
        *nbHab = *nbHab + 1;
    }
    for(j=0; j<CASE_BATIMENTS; j++)
    {
        for(g=0; g<CASE_BATIMENTS; g++)
        {
            grille[tab[i]->coord->x+j][tab[i]->coord->y+g] = HABITATION;
        }
    }
    return tab;
}

void SupprimerTableauHabitation(t_habitation **tab, int tailleActuelle)
{
    int i;
    for(i=0; i<tailleActuelle; i++)
    {
        if(tab[i] != NULL)
        {
            SupprimerHabitation(tab[i]);
        }
    }
    free(tab);
}

BITMAP **ChargerImage(char* type)
{
    int i,taille;
    char chemin[30];
    BITMAP **tab;
    if(strcmp(type,"route")==0) taille=NB_ROUTE;
    if(strcmp(type,"stade")==0) taille=NB_STADE;
    tab=(BITMAP**)malloc(taille*sizeof(BITMAP*));
    if(tab==NULL) exit(EXIT_FAILURE);

    for(i=0; i<taille; i++)
    {
        sprintf(chemin,"images/%s%d.bmp",type,i);
        tab[i]=load_bitmap(chemin,NULL);
    }
    return tab;
}

void SupprimerBatimentsSelectionne(t_habitation **tab, int x, int y, int tailleTableau, int** matrice)
{
    int i;
    int vrai = 0;
    for(i=0; i<tailleTableau; i++)
    {
        if(tab[i] != NULL)
        {
            vrai = VerifierBatimentSelectionne(tab[i], x, y);
            if(vrai == 1) break;
        }
    }

    if(vrai)
    {
        RemettreCaseLibreBatiments(matrice, tab[i]);
        SupprimerHabitation(tab[i]);
    }
    tab[i] = NULL;
}

int VerifierBatimentSelectionne(t_habitation *hab, int x, int y)
{
    int i, j;
    int vrai = 0;

    for(i=0; i<CASE_BATIMENTS; i++)
    {
        for(j=0; j<CASE_BATIMENTS; j++)
        {
            if(hab->coord->x == x/20 - i && hab->coord->y == y/20 - j)
                vrai = 1;
        }
    }

    return vrai;
}

void RemettreCaseLibreBatiments(int **matrice, t_habitation *hab)
{
    int i, j;
    for(i=0; i<CASE_BATIMENTS; i++)
    {
        for(j=0; j<CASE_BATIMENTS; j++)
        {
            matrice[hab->coord->x+i][hab->coord->y+j] = -1;
        }
    }
}
