#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "fonction.h"

#define COLONNE 30
#define LIGNE 15



int main(void)
{
	srand(time(NULL));
	system("clear");
  char plateau_jeu[LIGNE][COLONNE];    //tableau 2D pour le plateau de jeu en caractère

	int nb_humain = initialisation_nb_humain() , nb_ia = initialisation_nb_ia(nb_humain), premier=rand()%(nb_humain+nb_ia);
	int nb_chevaux;
	struct Joueur joueur[nb_humain+nb_ia];

	initialisation_humain( nb_humain, joueur);
	initialisation_ia( nb_humain,  nb_ia, joueur);

  initialisation_plateau(plateau_jeu);
	nb_chevaux = initialisation_chevaux(plateau_jeu, nb_humain, nb_ia, joueur);
	for(int i=0; i<8; i++)
	{
		system("clear");
		afficher_plateau(plateau_jeu);
		//deplacement(plateau_jeu, joueur, premier);
		dep(plateau_jeu, joueur, premier, nb_chevaux);
		premier = tri(nb_humain, nb_ia, joueur, premier);

	}
    return 0;
}
