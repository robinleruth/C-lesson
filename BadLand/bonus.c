 #include "bonus.h"

t_collec *AllouerCollec(BITMAP *sprite[NB_BONUS], int niveau)
{
    t_collec *collec = NULL;
    char nf[20];
    FILE *fp = NULL;
    int i;

    collec = (t_collec*)malloc(sizeof(t_collec));
    if(collec == NULL)
    {
        exit(EXIT_FAILURE);
    }

    sprintf(nf, "bonus%d.txt", niveau);
    fp = fopen(nf, "r");
    if(fp != NULL)
    {
        fscanf(fp, "%d", &collec->nbBonus);
        collec->bonus = (t_bonus**)malloc(collec->nbBonus*sizeof(t_bonus*));
        if(collec->bonus == NULL)
        {
            exit(EXIT_FAILURE);
        }

        for(i=0;i<collec->nbBonus;i++)
        {
            collec->bonus[i] = (t_bonus*)malloc(sizeof(t_bonus));
            if(collec->bonus[i] == NULL)
            {
                exit(EXIT_FAILURE);
            }
            fscanf(fp, "%d", &collec->bonus[i]->x);
            fscanf(fp, "%d", &collec->bonus[i]->y);
            fscanf(fp, "%d", &collec->bonus[i]->type);
            switch(collec->bonus[i]->type)
            {
            case BONUS_ADD:
                collec->bonus[i]->image = sprite[BONUS_ADD];
                break;
            case BONUS_BOOST:
                collec->bonus[i]->image = sprite[BONUS_BOOST];
                break;
            case BONUS_GROSSIR:
                collec->bonus[i]->image = sprite[BONUS_GROSSIR];
                break;
            case BONUS_RETRECIR:
                collec->bonus[i]->image = sprite[BONUS_RETRECIR];
                break;
            case SCIE:
                collec->bonus[i]->image = sprite[SCIE];
                break;
            case ENGRENAGE:
                collec->bonus[i]->image = sprite[ENGRENAGE];
                break;
            }
            collec->bonus[i]->vivant = 1;
        }

        fclose(fp);
    }
    else
    {
        printf("N'a pas réussi à ouvrir bonus.txt\n");
    }

    return collec;
}

void LibererCollec(t_collec *collec)
{
    int i;
    for(i=0;i<collec->nbBonus;i++)
    {
        free(collec->bonus[i]);
    }
    free(collec);
}
