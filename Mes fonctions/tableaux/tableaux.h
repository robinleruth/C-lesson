#ifndef TABLEAUX_H_INCLUDED
#define TABLEAUX_H_INCLUDED

void afficheTableau(int tableau[], int tailleTableau);
int sommeTableau(int tableau[], int tailleTableau);
float moyenneTableau(int tableau[], int tailleTableau);
void copieTableau(int tableauOriginal[], int tableauCopie[], int tailleTableau);
void maximumTableau(int tableau[], int tailleTableau, int valeurMax);
void ordonnerTableau(int tableau[], int tailleTableau);
int rechercheMini(int tableau[], int tailleTableau);
void initialiserTableau(int tableau[], int tailleTableau);
void remplirTableau(int tableau[], int tailleTableau);
void inverserTableau(const int tableau[], int inverse[], int tailleTableau);
void initialiserPointeur(char *tableau[], int tailleTableau);

#endif // TABLEAUX_H_INCLUDED
