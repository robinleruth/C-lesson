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
    int nbreElement;
    Element *premier;
};

Liste *InitialisationListe();
void AfficherListe(Liste *liste);
void AjouterElementDebut(Liste *liste, int nvNombre);
void SupprimerListe(Liste *liste);
void DeterminerNombreElement(Liste *liste);
void AjouterElementFin(Liste *liste, int nvNombre);
void SupprimerElementFin(Liste *liste);
void SupprimerElementDebut(Liste *liste);

#endif // FONCTIONS_H_INCLUDED
