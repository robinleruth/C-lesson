#ifndef LISTE_H_INCLUDED
#define LISTE_H_INCLUDED

t_liste *NouvelElementDebut(t_liste *ancre);
t_liste *NouvelElementFin(t_liste *ancre);
t_liste *SupprimerElementDebut(t_liste *ancre);
t_liste *SupprimerElementFin(t_liste *ancre);
t_liste *RechercherElement(t_liste *ancre, int numeroCherche);
t_liste *SupprimerElementRecherche(t_liste *ancre, int numeroCherche);
int DeterminerNombreElement(t_liste *ancre);
t_liste *DeterminerNumero(t_liste *ancre);
 t_liste *SupprimerListe(t_liste *ancre);

#endif // LISTE_H_INCLUDED
