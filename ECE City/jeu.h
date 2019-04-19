#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

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

int **AllouerMatrice();

void InitialiserMatrice(int **matrice);

void SupprimerMatrice(int **matrice);

t_jeu *AllouerStructPrincipale();

void SupprimerJeu(t_jeu *pt);

//Ajoute un élément en mémoire selon la valeur de la variable jeu->choixmenu
void AjouterElement(t_jeu *jeu);

char** matrice_adjacence(int**grille);

int dijkstra (char**adjacencePoids, int point_depart, int point_arrivee);

int CaseLibreBatiment(int **matrice, int x, int y);

int CaseLibreRoute(int **matrice, int x, int y);

int CaseLibreChateau(int **, int , int);

int CaseLibreCentrale(int **, int , int);

int** creation_carte_route(int** grille);
#endif // JEU_H_INCLUDED
