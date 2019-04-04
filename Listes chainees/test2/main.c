#include <stdio.h>
#include <stdlib.h>
#include "liste_chainee.h"

int main(int argc, char *argv[])
{
    Liste *maListe = InitialisationListeChainee();
    int i;
    int nombreDElement = 0;
    int val;
    printf("Combien d'élément voulez-vous saisir? ");
    scanf("%d", &nombreDElement);
    if(nombreDElement > 0)
    {
        for(i=0;i<nombreDElement;i++)
        {
            printf("\nSaisissez l'entier %d : ", i+1);
            scanf("%d", &val);
            InsertionElementFin(maListe, val);
        }
        SuppressionPremierElement(maListe);
    AfficherListe(maListe);
    SuppressionDeListe(maListe);
    }


    return EXIT_SUCCESS;
}
