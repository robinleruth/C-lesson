#ifndef HABITATION_H_INCLUDED
#define HABITATION_H_INCLUDED

#include "include.h"

t_habitation *CreerHabitation();

void SupprimerHabitation(t_habitation* hab);

// Toutes les 15 secondes, on change le stade. Etat est la variable qui permet,selon le mode, d'incrémenter ou décrémenter le stade
void ChangerStade(t_habitation *hab, int etat);


#endif // HABITATION_H_INCLUDED

