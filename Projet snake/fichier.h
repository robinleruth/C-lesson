#ifndef FICHIER_H_INCLUDED
#define FICHIER_H_INCLUDED

int DeterminerNombreDeScore(FILE *fp);
void ClasserTableau(int tableau[], int tailleTableau);
void AfficherRegles();
void RegarderScore();
void InitialiserTableau(int tab[], int tailleTableau);
void AddScore(int score);

#endif // FICHIER_H_INCLUDED
