#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

typedef struct Element Element;
struct Element
{
    int x;
    int y;
    Element *suivant;
};

typedef struct Liste Liste;
struct Liste
{
    int nbreElement;
    char direction;
    Element *premier;
};

typedef struct Menu Menu;
struct Menu
{
    int jouer;
    int regarderScore;
    int quitter;
    int regleDuJeu;
};

typedef struct Joueur Joueur;
struct Joueur
{
    char nom[20];
    int score;
};

#endif // STRUCT_H_INCLUDED
