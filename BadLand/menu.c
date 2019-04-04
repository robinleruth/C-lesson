#include "include.h"

int jouer()
{
    if((mouse_b&1)&&(mouse_x > 350)&&(mouse_x < 460)&&(mouse_y > 215)&&(mouse_y < 240))
    {
        while(mouse_b&1);
        return 1;

    }
    else return 0;
}

int menuScore()
{
    if((mouse_b&1)&&(mouse_x > 340)&&(mouse_x < 465)&&(mouse_y > 330)&&(mouse_y < 350))
    {
        while(mouse_b&1);
        return 1;

    }
    else return 0;
}

int quitter()
{
    if((mouse_b&1)&&(mouse_x > 330)&&(mouse_x < 480)&&(mouse_y > 390)&&(mouse_y < 410))
    {
        while(mouse_b&1);
        return 1;
    }
    else return 0;
}

int ChoisirNiveau()
{
    if((mouse_b&1)&&(mouse_x > 280)&&(mouse_x < 540)&&(mouse_y > 190)&&(mouse_y < 270))
    {
        while(mouse_b&1);
        return 0;
    }
    else if((mouse_b&1)&&(mouse_x > 90)&&(mouse_x < 340)&&(mouse_y > 315)&&(mouse_y < 390))
    {
        while(mouse_b&1);
        return 1;
    }
    else if((mouse_b&1)&&(mouse_x > 460)&&(mouse_x < 720)&&(mouse_y > 315)&&(mouse_y < 390))
    {
        while(mouse_b&1);
        return 2;
    }
    else return -1;
}

int regarderRegles()
{
    if((mouse_b&1)&&(mouse_x > 300)&&(mouse_x < 510)&&(mouse_y > 270)&&(mouse_y < 290))
    {
        while(mouse_b&1);
        return 1;

    }
    else return 0;
}
