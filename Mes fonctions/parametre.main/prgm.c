#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int i;
    FILE *fp1 = NULL;

    if(argc>1)
    {
        fp1=fopen(argv[1], "r");
    }

    if(fp1!=NULL)
    {
        while(!feof(fp1))
        {
            printf("%c", fgetc(fp1));
        }
        fclose(fp1);
    }
    else
    {
        printf("Erreur fichier");
        exit(EXIT_FAILURE);
    }
    for(i=0;i<argc;i++)
    {
        printf("\nL'argument %d est : %s", i+1, argv[i]);
    }
    printf("\n\n");
    system("PAUSE");
    return EXIT_SUCCESS;
}
