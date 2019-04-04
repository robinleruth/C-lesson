#ifndef CHAINES_H_INCLUDED
#define CHAINES_H_INCLUDED

void majuscule(const char *str);
void comparaison(const char *str, const char *str1);
void compter(const char *str);
void concat(const char *str, const char *str1);
int voyelle(const char *str);
void clean(char *str);
void purger();
int trouverNombreDeLettres(const char *str);
void ordonnerTableauDeChaines(char *tableau[], int tailleTableau);
void remplirTableauDeChaines(char *tableau[], char *str, int tailleTableau);
void libererMemoire(char *tableau[], int tailleTableau);

#endif // CHAINES_H_INCLUDED
