#ifndef HABITATION_H_INCLUDED
#define HABITATION_H_INCLUDED

typedef struct position
{
    int x;
    int y;
} t_position;

typedef struct habitation
{
    t_position* coord;
    int population;
    int stade;
    int temps_initial;
    int eau;
    int elec;
} t_habitation;

t_habitation *CreerHabitation();

void SupprimerHabitation(t_habitation* hab);

// Toutes les 15 secondes, on change le stade. Etat est la variable qui permet,selon le mode, d'incrémenter ou décrémenter le stade
void ChangerStade(t_habitation *hab, int etat);


#endif // HABITATION_H_INCLUDED

