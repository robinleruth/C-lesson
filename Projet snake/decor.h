#ifndef DECOR_H_INCLUDED
#define DECOR_H_INCLUDED

void ParametrerTerrain(int matrice[ABSCISSE_MAX][ORDONNEE_MAX]);
void AfficherScoreEcran(int score);
void coloration(int couleurDuTexte, int couleurDeFond);
void InitialiserMenu(Menu *menu);
void ChoisirOption(Menu *menu);
void InitialiserMatrice(int matrice[ABSCISSE_MAX][ORDONNEE_MAX]);
void AfficherNbreDePommesEcran(int nbrePommes);

#endif // DECOR_H_INCLUDED
