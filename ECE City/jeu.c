#include "include.h"

int **AllouerMatrice()
{
    int **tab = NULL;
    int i;
    tab = (int**)malloc(TAILLE_X*sizeof(int*));
    if(tab == NULL) exit(EXIT_FAILURE);
    for(i=0; i<TAILLE_X; i++)
    {
        tab[i] = (int*)malloc(TAILLE_Y*sizeof(int));
        if(tab[i] == NULL) exit(EXIT_FAILURE);
    }
    InitialiserMatrice(tab);

    return tab;
}

void InitialiserMatrice(int **matrice)
{
    int i, j;

    for(i=0; i<TAILLE_X; i++)
    {
        for(j=0; j<TAILLE_Y; j++)
        {
            matrice[i][j] = -1;
        }
    }
}

t_jeu *AllouerStructPrincipale()
{

    t_jeu *pt = NULL;
    pt = malloc(1*sizeof(t_jeu));
    if(pt == NULL) exit(EXIT_FAILURE);
    pt->matrice = AllouerMatrice();
    pt->batiments = AllouerBatiments();
    pt->ensembleRoutes = AllouerStructRoute();
    pt->chateaux = AllouerChateaux();
    pt->centrales = AllouerCentrales();
    pt->choix_menu = RIEN;
    return pt;
}

void SupprimerMatrice(int **tab)
{
    int i;
    for(i=0; i<TAILLE_X; i++)
    {
        free(tab[i]);
    }
    free(tab);
}

void SupprimerJeu(t_jeu *pt)
{
    SupprimerMatrice(pt->matrice);
    SupprimerTableauHabitation(pt->batiments->habitations, pt->batiments->tailleTableau);
    free(pt->batiments);
    SupprimerTableauCentrale(pt->centrales->centrales, pt->centrales->nb_centrales);
    free(pt->centrales);
    SupprimerTableauChateauDeau(pt->chateaux->chateaux, pt->chateaux->nb_chateaux);
    free(pt->chateaux);
    SupprimerTableauRoutes(pt->ensembleRoutes->routes, pt->ensembleRoutes->nbroute);
    free(pt->ensembleRoutes);

    free(pt);
    pt = NULL;
}

void AjouterElement(t_jeu *jeu)
{
    switch(jeu->choix_menu)
    {
    case RIEN:
        break;
    case ROUTE:
        if(CaseLibreRoute(jeu->matrice, mouse_x/20, mouse_y/20))
            jeu->ensembleRoutes->routes = ajouter_route(&jeu->ensembleRoutes->nbroute, jeu->ensembleRoutes->routes, jeu->matrice, mouse_x, mouse_y);
        jeu->choix_menu = RIEN;
        break;
    case HABITATION:
        if(CaseLibreBatiment(jeu->matrice, mouse_x/20, mouse_y/20))
        {
            jeu->batiments->habitations = AjouterHabitation(jeu->batiments->habitations, &jeu->batiments->tailleTableau, &jeu->batiments->nb_habitation, jeu->matrice);
        }
        jeu->choix_menu = RIEN;
        break;
    case CENTRALE:
        if(CaseLibreCentrale(jeu->matrice, mouse_x/20, mouse_y/20))
            jeu->centrales->centrales = AjouterCentrale(jeu->centrales->centrales, &jeu->centrales->tailleTableauCentrale, &jeu->centrales->nb_centrales, jeu->matrice);
        jeu->choix_menu = RIEN;
        break;
    case CHATEAU_EAU:
        if(CaseLibreChateau(jeu->matrice, mouse_x/20, mouse_y/20))
            jeu->chateaux->chateaux = AjouterChateau(jeu->chateaux->chateaux, &jeu->chateaux->tailleTableauChateau, &jeu->chateaux->nb_chateaux, jeu->matrice);
        jeu->choix_menu = RIEN;
        break;
    case CASERNE:
        //if(CaseLibreBatiment(jeu->matrice, mouse_x/20, mouse_y/20))
        jeu->choix_menu = RIEN;
        break;
    }
}

int** creation_carte_route(int** grille)
{
    int i,j;
    int** grille_pond=malloc((TAILLE_X)*sizeof(int*));
    for(i=0; i<TAILLE_X; i++)
    {
        grille_pond[i]=malloc(TAILLE_Y*sizeof(int));
    }
    if(grille_pond==NULL) exit(EXIT_FAILURE);

    for(i=0; i<TAILLE_X; i++)
    {
        for(j=0; j<TAILLE_Y; j++)
        {
            grille_pond[i][j]=0;
            if(grille[i][j]==0) grille_pond[i][j]=0;
            else
            {
                if(i!=0)
                {
                    if(grille[i-1][j]==1) grille_pond[i][j]+=1;
                }
                if(i<TAILLE_Y-1)
                {
                    if(grille[i+1][j]==1) grille_pond[i][j]+=4;
                }
                if(j!=0)
                {
                    if(grille[i][j-1]==1) grille_pond[i][j]+=8;
                }
                if(j<TAILLE_X-1)
                {
                    if(grille[i][j+1]==1) grille_pond[i][j]+=2;
                }


            }
        }
    }
    return grille_pond;
}

char** matrice_adjacence(int**grille)
{
    int i,j,valeur;
    char** matrice;
    matrice=(char**)malloc(TAILLE_Y*TAILLE_X*sizeof(char*));
    for(i=0; i<TAILLE_Y*TAILLE_X; i++)
    {
        matrice[i]=(char*)malloc(TAILLE_Y*TAILLE_X*sizeof(char));
    }
    for(i=0; i<TAILLE_Y*TAILLE_X; i++)
    {
        for(j=0; j<TAILLE_Y*TAILLE_X; j++)
        {
            matrice[i][j]=0;
        }
    }
    for(i=0; i<TAILLE_Y; i++)
    {
        for(j=0; j<TAILLE_X; j++)
        {
            valeur=grille[i][j];
            if(valeur!=-1)
            {
                if(valeur>=8) //A GAUCHE
                {
                    valeur-=8;
                    matrice[TAILLE_X*i+j][(TAILLE_X*i+j)-1]=1;
                }
                if(valeur>=4) //EN BAS
                {
                    valeur-=4;
                    matrice[TAILLE_X*i+j][(TAILLE_X*i+j)+TAILLE_X]=1;
                }
                if(valeur>=2) //A DROITE
                {
                    valeur-=2;
                    matrice[TAILLE_X*i+j][(TAILLE_X*i+j)+1]=1;
                }
                if(valeur>=1) //EN HAUT
                {
                    matrice[TAILLE_X*i+j][(TAILLE_X*i+j)-TAILLE_X]=1;
                }
            }
        }
    }
    return matrice;
}


int dijkstra (char**adjacencePoids, int point_depart, int point_arrivee)
{
/// Variables locales
    int *marques ; /// tableau dynamique indiquant si les sommets sont marqués ou non
    int x, y, xmin ; /// numéros de sommets intermédiaires
    int i;
    int *l;
    int *pred;
    float min ; /// distance minimale du prochain sommet à marquer
    int nb = 0 ; /// nombre de sommets marqués initialisé à 0
/// Allouer le tableau marques de taille « TAILLE_Y*TAILLE_X »
    marques=(int*)malloc(TAILLE_Y*TAILLE_X*sizeof(int));
    l=(int*)malloc(TAILLE_Y*TAILLE_X*sizeof(int));
    pred=(int*)malloc(TAILLE_Y*TAILLE_X*sizeof(int));
/// Initialiser les marquages à 0 et les longueurs minimales à l’INFINI
    for(i=0; i<TAILLE_Y*TAILLE_X; i++)
    {
        marques[i]=0;
        l[i]=INFINI;
    }
/// Initialiser longueur de s nombre de sommets marqués à 0
    l[point_depart] = nb;
/// Tant que les sommets ne sont pas tous marqués
    while (nb<TAILLE_Y*TAILLE_X)
    {
/// Initialiser la longueur minimale à l’INFINI
        min = INFINI ;
/// Pour tous les sommets x non marqués de longueur minimale
/// Stocker le sommet « xmin » de longueur minimale
        for (x=0 ; x<TAILLE_Y*TAILLE_X ; x++)
        {
            if (!marques[x] && l[x]<min)
            {
                xmin = x ;
                min = l[x] ;
            }
        }
/// Marquer le sommet de longueur minimale « xmin » et incrémenter « nb »
        marques[xmin] = 1 ;
        nb++ ;
/// Pour tous les sommets y adjacents à « xmin » et non marqués
/// Chercher la plus petite distance de y à « xmin »
/// Stocker le prédécesseur « xmin » de y
        for (y=0 ; y<TAILLE_Y*TAILLE_X ; y++)
            if (adjacencePoids[xmin][y] && !marques[y] && l[xmin]+adjacencePoids[xmin][y]<l[y])
            {
                l[y] = l[xmin] + adjacencePoids[xmin][y] ;
                pred[y] = xmin ;
            }
    }

    return l[point_arrivee];
}



int CaseLibreBatiment(int **matrice, int x, int y)
{
    int i,j;
    int compteur = 0;
    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            if(matrice[x+i][y+j] != -1)
            {
                compteur++;
            }
        }
    }
    if(compteur == 0) return 1;
    else return 0;
}

int CaseLibreRoute(int **matrice, int x, int y)
{
    if(matrice[x][y] == -1 ) return 1;
    else return 0;
}

int CaseLibreChateau(int **matrice, int x, int y)
{
    int i,j;
    int compteur = 0;
    for(i=0; i<CASE_RESSOURCES_X; i++)
    {
        for(j=0; j<CASE_RESSOURCES_Y; j++)
        {
            if(matrice[x+i][y+j] != -1)
            {
                compteur++;
            }
        }
    }
    if(compteur == 0) return 1;
    else return 0;
}

int CaseLibreCentrale(int **matrice, int x, int y)
{
    int i,j;
    int compteur = 0;
    for(i=0; i<CASE_RESSOURCES_Y; i++)
    {
        for(j=0; j<CASE_RESSOURCES_X; j++)
        {
            if(matrice[x+i][y+j] != -1)
            {
                compteur++;
            }
        }
    }
    if(compteur == 0) return 1;
    else return 0;
}
