#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

typedef struct Element Element;
struct Element
{
    int nombre;
    Element *suivant;
};

typedef struct Liste Liste;
struct Liste
{
    Element *premier;
};

Liste *initialisation();
void insertion(Liste *liste, int nvNombre);
void suppression(Liste *liste);
void AfficherListe(Liste *liste);

#endif // FONCTIONS_H_INCLUDED
