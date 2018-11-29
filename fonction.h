#define COLONNE 30
#define LIGNE 15
#define ESPACE_C ( COLONNE/15 *3) //la zone de déplacement des chevaux entre 2 écuries ( COLONNE/15 *3)
#define ESPACE_L ( LIGNE/15 *3) //la zone de déplacement des chevaux entre 2 écuries ( COLONNE/15 *3)
#define ECURIE_C (COLONNE-ESPACE_C)/2
#define ECURIE_L (LIGNE-ESPACE_L)/2

struct Case
{
	int C, L;
};
struct Pion
{
	int C, L;				// C pour colonne donc abscisse, et L pour LIGNE donc ordonnee
};
struct Joueur
{
	char nom[20];
	char couleur[6];
	int type;		// humain= 0   ou ia=1
	struct Pion pion[4];
};




int initialisation_chevaux(char plateau_jeu[LIGNE][COLONNE], int nb_humain, int nb_ia, struct Joueur *joueur);

int deplacement(char plateau_jeu[LIGNE][COLONNE], struct Joueur *humain, int premier);
void dep(char plateau_jeu[LIGNE][COLONNE], struct Joueur *joueur, int premier, int nb_chevaux);

int tri(int nb_humain, int nb_ia, struct Joueur *joueur, int premier);

int lancer_des(void);
int initialisation_nb_humain(void);
char *initialisation_nom_humain(int ordre);
void initialisation_couleur_humain(int nb_humain, struct Joueur *humain, int ordre );
void initialisation_humain(int nb_humain, struct Joueur *humain);
int initialisation_nb_ia(int nb_humain);
void initialisation_nom_ia(int nb_humain, int nb_ia, struct Joueur *ia);
void initialisation_couleur_ia(int nb_ia, struct Joueur *ia, int ordre );
void initialisation_ia(int nb_humain, int nb_ia, struct Joueur *ia);
void initialisation_plateau(char plateau_jeu[LIGNE][COLONNE]);
void afficher_plateau(char plateau_jeu[LIGNE][COLONNE])	;
void couleur(int attr, int fg, int bg);
void attendre(float temps);
void viderBuffer(void);
int lireEntier(int nombre);
int lire(char *chaine, int longueur);
