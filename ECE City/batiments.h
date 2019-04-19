#ifndef BATIMENTS_H_INCLUDED
#define BATIMENTS_H_INCLUDED

typedef struct batiments
{
    struct habitation **habitations;
    int nb_habitation;
    int tailleTableau;
    BITMAP **imagesBatiments;
} t_batiments;


t_batiments *AllouerBatiments();

/* Alloue et met à 0 le **tab*/
struct habitation **AllouerTableauHabitation();

// Mets toutes les cases à 0
void InitialiserTableauHabitation(struct habitation **tab);

// Realloc le tableau avec 3/2 cases supplémentaires
struct habitation **AugmenterTailleTableau(struct habitation **tab, int *tailleActuelle, int nbHab);

// Ajoute une habitation et, si plus de places, augmente la taille du tab
struct habitation **AjouterHabitation(struct habitation **tab, int *tailleActuelle, int *nbHab, int **grille);

// Retourne le nombre de pointeurs différents de NULL
int RecupererNbHabitation(struct habitation **tab, int tailleActuelle);

// Tout plein de malloc
void SupprimerTableauHabitation(struct habitation **tab, int tailleActuelle);

// Charge les images des différents stade
BITMAP **ChargerImage(char*);

void SupprimerBatimentsSelectionne(t_habitation**, int, int, int, int**);

int VerifierBatimentSelectionne(t_habitation *, int, int);

void RemettreCaseLibreBatiments(int **matrice, t_habitation *hab);


#endif // BATIMENTS_H_INCLUDED

