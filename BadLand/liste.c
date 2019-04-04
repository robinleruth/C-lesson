#include "include.h"

t_liste *NouvelElementDebut(t_liste *ancre)
{
    //on crée un nouvel élément
    t_liste *nouv = (t_liste*)malloc(sizeof(t_liste));

    //On blinde
    if(nouv == NULL)
    {
        exit(EXIT_FAILURE);
    }
    t_player *nvElement = CreerElement(ancre->element);
    //On donne à l'élement un numéro
    nvElement->numero = DeterminerNombreElement(ancre) + 1;

    nouv->element = nvElement;

    nouv->suivant = ancre;

    return nouv;
}

t_liste *NouvelElementFin(t_liste *ancre)
{
    t_liste *nouv = (t_liste*)malloc(sizeof(t_liste));
    t_player *nvElement = NULL;
    if(nouv == NULL)
    {
        exit(EXIT_FAILURE);
    }

    //On fait pointer le suivant sur NULL car c'est le pointeur de fin de liste chaînée !
    nouv->suivant = NULL;

    ///Si il n'y a pas d'élement, alors on retourne celui-ci et son adresse sera l'ancre de la liste ;)
    if(ancre == NULL)
    {
        nvElement = (t_player*)malloc(sizeof(t_player));
        if(nvElement == NULL)
        {
            exit(EXIT_FAILURE);
        }
        ///S'il n'y a pas de perso, on le crée
        ///Il faut initialiser le sprite dans le main par contre
        nvElement->x = 200;
        nvElement->y = 200;
        nvElement->vit_x = 10;
        nvElement->vit_y = 0;
        nvElement->numero = 1;
        nvElement->vivant = 1;
        nvElement->angle = 0;
        nvElement->vit_angle= 0;
        nouv->element = nvElement;
        return nouv;
    }


    else
    {
        ///S'il y en a déjà un, on en crée un à l'image du premier
        nvElement = CreerElement(ancre->element);
        //Sinon on parcout la liste jusqu'à la fin et on rajoute l'élement
        t_liste *temp = ancre;
        while(temp->suivant != NULL)
        {
            temp = temp->suivant;
        }
        nvElement->numero = DeterminerNombreElement(ancre) + 1;
        nouv->element = nvElement;
        temp->suivant = nouv;
        return ancre;
    }
}

//On l'utilisera pas ici, ça ne va pas être utile je pense
t_liste *SupprimerElementDebut(t_liste *ancre)
{
    if(ancre != NULL)
    {
        t_liste *temp = ancre;
        ancre = ancre->suivant;
        free(temp->element);
        free(temp);
        return ancre;
    }
    else
        return NULL;
}

//On n'utilisera pas celui-là non plus, ce qui nous intéresse est de supprimer une structure avec un numéro
t_liste *SupprimerElementFin(t_liste *ancre)
{
    if(ancre == NULL)
        return NULL;

    if(ancre->suivant == NULL)
    {
        free(ancre);
        return NULL;
    }

    t_liste *tmp = ancre;
    t_liste *ptmp = ancre;

    while(tmp->suivant != NULL)
    {
        ptmp = tmp;
        tmp = tmp->suivant;
    }
    ptmp->suivant = NULL;
    free(tmp->element);
    free(tmp);
    return ancre;
}

t_liste *RechercherElement(t_liste *ancre, int numeroCherche)
{
    if(ancre==NULL)
        return NULL;

    t_liste *tmp = ancre;

    while(tmp != NULL)
    {
        if(tmp->element->numero == numeroCherche) // Si le numéro correspond
        {
            return tmp;
        }
        tmp = tmp->suivant;
    }
    return NULL;
}

///On va utiliser ça !
t_liste *SupprimerElementRecherche(t_liste *ancre, int numeroCherche)
{
    t_liste *tmp = NULL;
    t_liste *ptmp = NULL;
    if(ancre == NULL)
        return NULL;
    else if(DeterminerNombreElement(ancre) == 1)
    {
        SupprimerElementFin(ancre);
        return NULL;
    }
    else if(numeroCherche == 1)
    {
        tmp = SupprimerElementDebut(ancre);
        return tmp;
    }
    else
    {
        tmp = RechercherElement(ancre, numeroCherche); // On recherche l'élément
        ///A TESTER
        ptmp = ancre;

        if(tmp != NULL)
        {
            if(ptmp == tmp)
            {
                ptmp->suivant = tmp->suivant;
                free(tmp->element);
                free(tmp);
                return ptmp->suivant;
            }
            else
            {
                while(ptmp->suivant != tmp)
                {
                    ptmp = ptmp->suivant;
                }
                ptmp->suivant = tmp->suivant;
                free(tmp->element);
                free(tmp);
            }

        }
        return ancre;
    }
}

int DeterminerNombreElement(t_liste *ancre)
{
    if(ancre == NULL)
        return 0;

    return DeterminerNombreElement(ancre->suivant) + 1; ///Récursif
}

t_liste *DeterminerNumero(t_liste *ancre)
{
    t_liste *temp = ancre;
    int compteur = 1;
    while(temp != NULL)
    {
        temp->element->numero = compteur;
        temp = temp->suivant;
        compteur++;
    }
    return ancre;
}
t_liste *SupprimerListe(t_liste *ancre)
{
    if(ancre == NULL) return NULL;
    t_liste *tmp = ancre;
    t_liste *aSupprimer = NULL;
    while(tmp != NULL)
    {
        aSupprimer = tmp;
        tmp = tmp->suivant;
        free(aSupprimer);
    }
    return NULL;
}
