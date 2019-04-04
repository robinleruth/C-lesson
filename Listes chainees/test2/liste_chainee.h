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
    int nbElement;
    Element *premier;
};

Liste *InitialisationListeChainee();
void InsertionElementDebut(Liste *liste, int nvNombre);
void SuppressionPremierElement(Liste *liste);
void AfficherListe(Liste *liste);
void SuppressionDeListe(Liste *liste);
void DeterminerTailleDeListe(Liste *liste);
void InsertionElementFin(Liste *liste, int nvNombre);
void SuppressionDernierElement(Liste *liste);

#endif // FONCTIONS_H_INCLUDED
