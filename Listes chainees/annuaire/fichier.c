#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "liste.h"

void EcrireFichier(Liste *liste, const char *str)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }
    FILE *fp1 = NULL;
    fp1 = fopen(str, "w");
    if(fp1 == NULL)
    {
        printf("Erreur fichier");
    }
    else
    {
        Personne *actuel = liste->premier;
        while(actuel != NULL)
        {
            fprintf(fp1,"%s %s, %d ans \n", actuel->nom, actuel->prenom, actuel->age);
            actuel = actuel->suivant;
        }
        fclose(fp1);
    }
}
