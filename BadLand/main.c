#include "include.h"

int main(int argc, char *argv[])
{
    t_liste *ancre = NULL;
    t_decor decor; // Map visible
    t_decor fond; //Arrière plan
    t_menu menu;
    BITMAP *spritesBonus[NB_BONUS];
    BITMAP *niveaux = NULL;
    BITMAP *regleDuJeu = NULL;
    BITMAP *gameOver = NULL;
    BITMAP *gagner = NULL;
    int continuer = 1;

    int niveau = -1;

    ///1 - Initialisation
    lancerToutAllegro(800, 600);
    srand(time(NULL));

    InitialiserMenu(&menu);
    ancre = NouvelElementFin(ancre);
    ChargerSpritesDebut(ancre->element);
    ChargerToutesImages(&fond, &decor, &menu, spritesBonus);
    niveaux = chargerImage("images/MenuNiveau.bmp");
    regleDuJeu = chargerImage("images/regleJeu.bmp");
    gameOver = chargerImage("images/gameOver.bmp");
    gagner = chargerImage("images/gagner.bmp");

    ///2 - Menu
    while(menu.quitter == 0)
    {
        clear_bitmap(page);
        blit(menu.image, page,0,0,0,0,SCREEN_W,SCREEN_H);
        blit(page, screen, 0,0,0,0, SCREEN_W, SCREEN_H);

        menu.jouer = jouer();
        menu.quitter = quitter();
        menu.regles = regarderRegles();
        menu.regarderScore=menuScore();

        while(menu.jouer == 1)
        {
            clear_bitmap(page);
            blit(niveaux,page,0,0,0,0,SCREEN_W,SCREEN_H);
            blit(page, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
            ///3 - Jeu
            while(continuer)
            {

                blit(niveaux, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
                while(niveau == -1)
                    niveau = ChoisirNiveau();
                InitialiserDecor(&fond);
                InitialiserDecor(&decor);
                niveau = JouerNiveau(&fond, &decor, niveau, ancre, spritesBonus);
                if((niveau == 0)||(niveau == -1)) continuer = 0;
                if(niveau == 0)
                {
                    while(!key[KEY_ENTER])
                    {
                        clear_bitmap(page);
                        blit(gameOver, page, 0,0,0,0,SCREEN_W, SCREEN_H);
                        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                    }
                    continuer = 0;
                }
                if(niveau == -1)
                {
                    while(!key[KEY_ENTER])
                    {
                        clear_bitmap(page);
                        blit(gagner, page, 0,0,0,0,SCREEN_W, SCREEN_H);
                        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                    }
                }
            }
            if(niveau <= 0)
            {
                niveau = -1;
            }
            menu.jouer = 0;
            continuer = 1;
        }

        while(menu.regarderScore)
        {

            clear_bitmap(page);
            blit(niveaux,page,0,0,0,0,SCREEN_W,SCREEN_H);
            blit(page, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
            while(niveau == -1)
                niveau = ChoisirNiveau();
            afficherScore(niveau);
            while(!key[KEY_ESC])
            {
            }
            menu.regarderScore=0;
            niveau=-1;

        }
        while(menu.regles)
        {
            while(!key[KEY_ESC])
            {
                clear_bitmap(page);
                blit(regleDuJeu, page,0,0,0,0,SCREEN_W,SCREEN_H);
                blit(page, screen,0,0,0,0,SCREEN_W,SCREEN_H);
            }
            menu.regles = 0;
        }
    }
    return 0;
}
END_OF_MAIN();
