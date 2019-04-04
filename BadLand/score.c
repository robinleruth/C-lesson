#include "include.h"

void saisiePseudo( char pseudo[], int resultat)
{

    int touche;
    char carac;
    int poscarac=0;
    int position=0;


    //saisie du nom du joueur
    while (!key[KEY_ENTER])
    {
        textprintf_ex(screen,font,300,100,makecol(255,255,255),-1,"PSEUDO :");
        textprintf_ex(screen,font,300,150,makecol(255,255,255),-1,"SCORE : %d",resultat);
        clear_keybuf();
        while(position<TAILLE_NOM-1) //on blinde la taille du pseudo du joueur a 4 caracteres
        {
            if (keypressed())
            {
                touche=readkey();
                if(touche != KEY_SPACE)
                {
                    // on recupere le caractere en castant en char
                    carac=touche;
                    //a chaque touche pressee on l'affiche sur screen
                    textprintf_ex(screen,font,400+poscarac,100,makecol(255,255,255),-1,"%c",carac);
                    poscarac=poscarac+8; //on decalle la position pour chaque nouveau caractere
                    pseudo[position]=carac; //copie du caractere dans chaine de caractere
                    position=position+1; //boucle
                    printf("%c\n",carac);
                    clear_keybuf();
                }

            }
        }
    }
    // on ajoute le /0 a la fin de la chaine
    pseudo[TAILLE_NOM-1]='\0';
}


void ouvertureFichier( int niveau)
{
    int i;
    int score_tmp;

    //ouverture fichier
    FILE* f1=NULL;
    //ouverture du fichier en fonction du niveau
    if(niveau==0)
    {
        f1=fopen("fichier/niveau0.txt","r");
    }
    else if(niveau==1)
    {
        f1=fopen("fichier/niveau1.txt","r");
    }
    else if(niveau==2)
    {
        f1=fopen("fichier/niveau2.txt","r");
    }

    //Vérification
    if(f1!=NULL)
    {
        for(i=0; i<NBR_SCORE; i++) //copie des 10 noms et scores dans strcuture pour tri
        {
            fgets(joueur[i].pseudo, TAILLE_NOM, f1);
            fscanf(f1,"%d\n", &score_tmp);
            joueur[i].score = score_tmp ;
        }
        fclose(f1);
    }


    else
    {
        printf("probleme d'ouverture de fichier");
    }

}


void copiefichier( int niveau)
{
    int i;
    FILE* f1=NULL;
    //ouverture du fichier en fonction du niveau
    if(niveau==0)
    {
        //1. Ouverture du fichier
        f1=fopen("fichier/niveau0.txt","w");
    }
    else if(niveau==1)
    {
        f1=fopen("fichier/niveau1.txt","w");
    }
    else if(niveau==2)
    {
        f1=fopen("fichier/niveau2.txt","w");
    }

    //Vérification
    if(f1!=NULL)
    {
        for(i=0; i<NBR_SCORE; i++) //on copie les 10 premieres cases de lae structure triee
        {
            fputs(temporaire[i].pseudo, f1);
            fprintf(f1," %d ", temporaire[i].score);
        }
        fclose(f1);
    }

    else
    {
        printf("probleme d'ouverture de fichier");
    }
}

void tri( int resultat, char pseudo[], int niveau)
{
    int i, test;
    t_joueur tmp; //inverser valeurs

    for(i=0; i<NBR_SCORE; i++) //on copie toutes joueur dans temporaire
    {
        temporaire[i]=joueur[i];
    }

    temporaire[NBR_SCORE+1].score=resultat; //ajout du score puis du pseudo du joueur dans temporaire pour classer ensuite
    for(i=0; i<TAILLE_NOM+2; i++) //copie du pseudo
    {
        temporaire[NBR_SCORE+1].pseudo[i]=pseudo[i];
    }
    //tri
    do
    {
        test=0;
        for(i=0; i<NBR_SCORE+1; i++)
        {
            if((temporaire[i+1].score)>(temporaire[i].score))
            {
                tmp  = temporaire[i] ;
                temporaire[i] = temporaire[i+1];
                temporaire[i+1] = tmp ;
                test=1;
            }
        }
    }
    while(test==1);
}

void afficherScore(int niveau)
{
    //declaration des variables
    int score;
    char joueur[TAILLE_NOM]; //garder en memoire le nom du joueur pour l'afficher ensuite
    int i;
    int position=0; //décaller la lettre suivante

    FILE* f1=NULL;

    clear_bitmap(screen);
    //ouverture d'un fichier en fonction du niveau choisi
    if(niveau==0)
    {
        f1=fopen("fichier/niveau0.txt","r");
    }
    else if(niveau==1)
    {
        f1=fopen("fichier/niveau1.txt","r");
    }
    else if(niveau==2)
    {
        f1=fopen("fichier/niveau2.txt","r");
    }
    //Vérification d'ouverture
    if(f1!=NULL)
    {
        textprintf_centre_ex(screen,font,400,25,makecol(255,255,255),-1,"SCORES NIVEAU %d",niveau+1);
        //on copie puis on affiche chaque nom et score sur screen
        for(i=0; i<NBR_SCORE; i++)
        {
            fgets(joueur,TAILLE_NOM,f1);
            printf("%s\n",joueur);
            fscanf(f1,"%d ",&score);
            printf("%d",score);

            position=position+20; //on change de "ligne"
            textprintf_ex(screen,font,50,100+position,makecol(255,255,255),-1,"%d.",i+1);
            textprintf_ex(screen,font,300,100+position,makecol(255,255,255),-1," %d points",score);
            textprintf_ex(screen,font,100,100+position,makecol(255,255,255),-1," %s", joueur);
        }
    }

    else
    {
        printf("probleme d'ouverture de fichier");
    }

}



void calculScore( int niveau, int resultat)
{
    clear_bitmap(screen);
    //resultat=1000/sqrt(duree);
    char pseudo[TAILLE_NOM];
    saisiePseudo(pseudo,resultat);
    ouvertureFichier(niveau);
    tri(resultat, pseudo, niveau);
    //copie de la nouvelle chaine dans fichier
    copiefichier(niveau);
}
