#include "include.h"

BITMAP *calque_batiment;
BITMAP *calque_grille;
BITMAP *calque_routes;
BITMAP *calque_ressources;
BITMAP *buffer;
int* timer;

int main()
{
    lancerToutAllegro();
    InitialiserCalques();
    t_jeu *jeu = NULL;
    int compteur_boucle=0, i,test_stade=0;
    jeu = AllouerStructPrincipale();
    dessin_matrice(calque_grille);
    BITMAP* herbe= load_bitmap("images/herbe.bmp",NULL);
    BITMAP* pointeur= load_bitmap("images/pointeur.bmp",NULL);
    BITMAP* aide = load_bitmap("images/aide.bmp",NULL);
    int* mode=malloc(sizeof(int));
    *mode=15;
    timer=malloc(sizeof(int));
    *timer=time(NULL);
    jeu->choix_menu = HABITATION;
    while(!key[KEY_ESC])
    {
        compteur_boucle++;
        choixmodeaffichage(mode);
        affichage_global(herbe, *mode, pointeur);
        if(*timer!=time(NULL)||compteur_boucle%3==0)
        {
            if(compteur_boucle%60==0) test_stade=1;
            *timer=time(NULL);
            if(key[KEY_H])
            {
                jeu->choix_menu=HABITATION;
                AjouterElement(jeu);
                AfficherBatiments(jeu->batiments->imagesBatiments, jeu->batiments);
            }
            if(key[KEY_C])
            {
                jeu->choix_menu=CENTRALE;
                AjouterElement(jeu);
                AfficherRessources(jeu->chateaux, jeu->centrales);
            }
            if(key[KEY_E])
            {
                jeu->choix_menu=CHATEAU_EAU;
                AjouterElement(jeu);
                AfficherRessources(jeu->chateaux, jeu->centrales);
            }
            if(key[KEY_R])
            {
                jeu->choix_menu = ROUTE;
                AjouterElement(jeu);
                remplissage_calque_route(jeu->matrice, jeu->ensembleRoutes->routes, jeu->ensembleRoutes->nbroute, jeu->ensembleRoutes->bibliroute);
            }
            if(key[KEY_D])
            {
                if(jeu->matrice[mouse_x/20][mouse_y/20] != -1)
                {
                    switch(jeu->matrice[mouse_x/20][mouse_y/20])
                    {
                    case ROUTE:
                        SupprimerRouteSelectionnee(jeu->ensembleRoutes->routes, mouse_x, mouse_y, jeu->ensembleRoutes->nbroute, jeu->matrice);
                        remplissage_calque_route(jeu->matrice, jeu->ensembleRoutes->routes, jeu->ensembleRoutes->nbroute, jeu->ensembleRoutes->bibliroute);
                        break;
                    case HABITATION:
                        SupprimerBatimentsSelectionne(jeu->batiments->habitations, mouse_x, mouse_y, jeu->batiments->tailleTableau, jeu->matrice);
                        clear_to_color(calque_batiment, makecol(255,0,255));
                        AfficherBatiments(jeu->batiments->imagesBatiments, jeu->batiments);
                        break;
                    case CENTRALE:
                        SupprimerCentraleSelectionne(jeu->centrales->centrales, mouse_x, mouse_y, jeu->centrales->tailleTableauCentrale, jeu->matrice);
                        clear_to_color(calque_ressources, makecol(255,0,255));
                        AfficherRessources(jeu->chateaux, jeu->centrales);
                        break;
                    case CHATEAU_EAU:
                        SupprimerChateauSelectionne(jeu->chateaux->chateaux, mouse_x, mouse_y, jeu->chateaux->tailleTableauChateau, jeu->matrice);
                        clear_to_color(calque_ressources, makecol(255,0,255));
                        AfficherRessources(jeu->chateaux, jeu->centrales);
                        break;
                    case CASERNE:
                        break;
                    }
                }

            }
            if(key[KEY_A])
            {
                while(!key[KEY_Z])
                {
                    if(aide != NULL)
                    {

                        blit(aide, screen, 0, 0, 0, 0, LARGEUR, HAUTEUR);
                    }
                }
            }
            if(key[KEY_SPACE])
            {
                for(i=0; i<jeu->chateaux->nb_chateaux; i++)
                {
                    if(jeu->chateaux->chateaux[i] != NULL)
                        gestion_eau(*jeu->chateaux->chateaux[i],jeu->matrice,matrice_adjacence(creation_carte_route(jeu->matrice)),jeu->batiments);
                }
                for(i=0; i<jeu->chateaux->nb_chateaux; i++)
                {
                    gestion_elec(*jeu->centrales->centrales[i],jeu->matrice,matrice_adjacence(creation_carte_route(jeu->matrice)),jeu->batiments);
                }
            }
            for(i=0; i<jeu->batiments->nb_habitation&&test_stade==1; i++)
            {
                if(jeu->batiments->habitations[i] != NULL)
                {
                    printf("MAISON : %d\n",jeu->batiments->habitations[i]->temps_initial);

                    if((((*timer-jeu->batiments->habitations[i]->temps_initial)%15==0)&&(jeu->batiments->habitations[i]->temps_initial!=*timer))&&(test_stade==1))
                    {
                        test_stade=0;
                        ChangerStade(jeu->batiments->habitations[i],1);
                        printf("A %d A\n",jeu->batiments->habitations[i]->stade);
                        AfficherBatiments(jeu->batiments->imagesBatiments, jeu->batiments);
                    }
                }
            }
        }



        /** Sous linux : sleep(), sous windows : rest() **/
        //rest(20);
        sleep(0.9);
    }

    SupprimerJeu(jeu);
    destroy_bitmap(calque_grille);

    return 0;
}
END_OF_MAIN();
