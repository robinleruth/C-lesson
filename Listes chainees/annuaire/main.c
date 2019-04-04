#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "liste.h"
#include "fichier.h"

int main(int argc, char *argv[])
{
    Liste *maListe = Initialisation();
    char nom[20];
    char prenom[20];
    int age;
    int nbrePersonne = 0;
    int i;

    printf("Combien de personnes voulez-vous mettre dans %s ? ", argv[1]);
    scanf("%d", &nbrePersonne);
    purger();
    printf("\n");

    if(nbrePersonne > 0)
    {
        i = 0;
        while(i < nbrePersonne)
        {
            ObtenirPersonne(nom, prenom, &age);
            AjoutPersonne(maListe, nom, prenom, age);
            i++;
        }
    }

    AfficherListe(maListe);
    printf("\n");
    EcrireFichier(maListe, argv[1]);

    SupprimerListe(maListe);
    system("PAUSE");
    return EXIT_SUCCESS;
}


