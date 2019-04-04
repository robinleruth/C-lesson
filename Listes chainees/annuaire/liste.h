#ifndef LISTE_H_INCLUDED
#define LISTE_H_INCLUDED

Liste *Initialisation();
void AjoutPersonne(Liste *liste, const char *nom, const char *prenom, const int age);
void SupprimerPremierePersonne(Liste *liste);
void SupprimerListe(Liste *liste);
void AfficherListe(Liste *liste);
void clean(char *str);
void purger();
void ObtenirNom(char *str);
void ObtenirPersonne(char *nom, char *prenom, int *age);
void DeterminerNbreElement(Liste *liste);
void SupprimerDernierePersonne(Liste *liste);

#endif // LISTE_H_INCLUDED
