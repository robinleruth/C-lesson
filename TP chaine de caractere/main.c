#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototype.h"

int main(int argc, char *argv[])
{
    char ch[100];
    char ch1[100];
    char choix = 0;

    do
    {
        printf("Saisissez une chaine de caracteres : ");
        fgets(ch, 100, stdin);
        if(ch[0]=='\0')
        {
            printf("\nVous n'avez pas entr� une chaine de caract�res valides !\n");
        }
    }while(ch[0]=='\0');

    printf("\n\n");

    choix = menu(choix);

    switch(choix)
    {
    case '1':
        printf("\n\nLa chaine de caract�res en majuscule est : ");
        majuscule(ch);
        break;
    case '2':
        printf("\n\nLa chaine de caract�res en minuscule est : ");
        minuscule(ch);
        break;
    case '3':
        printf("\n\nSaisissez une autre chaine de caracteres : ");
        fgets(ch1, 100, stdin);
        comparaison(ch, ch1);
        break;
    case '4':
        compter(ch);
        break;
    case '5':
        printf("\n\nSaisissez une autre chaine de caracteres : ");
        fgets(ch1, 100, stdin);
        concat(ch, ch1);
        break;
    case '6':
        break;
    case '7':
        break;
    case '8':
        voyelle(ch);
        break;
    default :
        printf("\n\nCe que vous avez saisi n'est pas valide.\n");
    }

    printf("\n\n");
    return 0;
}

char menu(char c)
{
    printf("***************MENU***************\n\n");
    printf("Voulez-vous : \n");
    printf("Convertir la chaine saisie en majuscules? Tapez 1\n");
    printf("Convertir la chaine en minuscules? Tapez 2 \n");
    printf("Comparez 2 chaines a saisir? Tapez 3\n");
    printf("Compter la longueur de la cha�ne? Tapez4\n");
    printf("Concat�ner deux chaines dans la premi�re? Tapez 5 \n");
    printf("Crypter une chaine en appliquant un d�calage circulaire dont la valeur est entr�e par l'utilisateur? Tapez 6 \n");
    printf("D�crypter une chaine de caract�res crypt�e en appliquant un d�calage circulaire inverse � partir d'une valeur entr�e par l'utilisateur? Tapez 7\n");
    printf("Compter le nombre de voyelles dans la chaine? Tapez 8 \n");
    c=getch();
    return c;
}

void majuscule(const char *str)
{
    int diff = 'a'-'A';
    char a;

    while(*str) //Tant qu'on n'arrive pas � la fin de la chaine
    {
        a=*str;
        if ((*str>='a')&&(*str<='z'))
        {
            a=*str-diff;
            printf("%c", a);
        }
        else
        {
            printf("%c", a);
        }
        *str++;
    }
}

void minuscule (const char *str)
{
    int diff = 'a'-'A';
    char a;

    while (*str)
    {
        a = *str;
        if((*str>='A')&&(*str<='Z'))
        {
            a = *str + diff;
            printf("%c", a);
        }
        else
        {
            printf("%c", a);
        }
        *str++;
    }
}

void comparaison(const char *str, const char *str1)
{
    int res;
    res = strcmp(str, str1);
    if (res>0)
    {
        printf("\nLa chaine 1 est plus longue que la chaine 2");
    }
    else if (res==0)
    {
        printf("\nLes deux chaines ont la meme longueur");
    }
    else
    {
        printf("\nLa chaine 1 est plus petite que la chaine 2");
    }
}


void compter(const char *str)
{
    printf("\nLa longueur de la chaine est %d", strlen(str));
}


void concat(const char *str, const char *str1)
{
    strcat(str, str1);
    printf("\nLes deux cha�nes concat�n�es sont : %s", str);
}


void decal_circ(const char *str)
{

}

void voyelle(const char *str)
{
    int i = 0;
    while (*str)
    {
        if (*str==',')
        {
            i++;
        }
        *str++;
    }
    printf("\nIl y a %d voyelles dans le code.", i);
}
