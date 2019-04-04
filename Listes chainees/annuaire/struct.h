#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

typedef struct Personne Personne;
struct Personne
{
    char nom[20];
    char prenom[20];
    int age;

    Personne *suivant;
};

typedef struct Liste Liste;
struct Liste
{
    int nbreElement;
    Personne *premier;
};

#endif // STRUCT_H_INCLUDED
