#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED

void saisiePseudo( char pseudo[], int resultat);
void ouvertureFichier( int niveau);
void copiefichier( int niveau);
void tri( int resultat, char pseudo[], int niveau);
void afficherScore(int niveau);
void calculScore( int niveau, int resultat);

#endif // SCORE_H_INCLUDED
