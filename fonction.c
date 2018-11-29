#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "fonction.h"

#define COLONNE 30
#define LIGNE 15
#define ESPACE_C ( COLONNE/15 *3) //la zone de déplacement des chevaux entre 2 écuries ( COLONNE/15 *3)
#define ESPACE_L ( LIGNE/15 *3) //la zone de déplacement des chevaux entre 2 écuries ( COLONNE/15 *3)
#define ECURIE_C (COLONNE-ESPACE_C)/2
#define ECURIE_L (LIGNE-ESPACE_L)/2

#define C_BASE -30
#define C_ROUGE 1
#define C_VERT 2
#define C_JAUNE 3
#define C_BLEU 4
#define C_BLANC 7

char coul[][6]={ {"jaune"},{" ou "},{"bleu"},{" ou "},{"vert"},{" ou "},{"rouge"} };

int initialisation_chevaux(char plateau_jeu[LIGNE][COLONNE], int nb_humain, int nb_ia, struct Joueur *joueur)
{
	int nb_chevaux=0;
	char temp[2];

	do
	{
		printf("Nombre de chevaux (entre 2 et 4) :");
		nb_chevaux = lireEntier(nb_chevaux);
	}while(nb_chevaux<2 || nb_chevaux>4);

	joueur->pion->C = -1;
	joueur->pion->L = -1;
	for(int i=0; i<nb_humain+nb_ia; i++)
	{
		for(int j=0; j<nb_chevaux; j++)
		{
			if(joueur[i].couleur[0]=='j')
			{
				joueur[i].pion[j].C = 0;
				joueur[i].pion[j].L = ECURIE_L-1-j;
				plateau_jeu[ECURIE_L-1-j][0]='J';
				sprintf(temp, "%d", j+1);
				plateau_jeu[ECURIE_L-1-j][1]=temp[0];
			}
			if(joueur[i].couleur[0]=='b')
			{
				joueur[i].pion[j].C = COLONNE-ECURIE_C+j*2;
				joueur[i].pion[j].L = 0;
				plateau_jeu[0][COLONNE-ECURIE_C+j*2]='B';
				sprintf(temp, "%d", j+1);
				plateau_jeu[0][COLONNE-ECURIE_C+j*2+1]=temp[0];
			}
			if(joueur[i].couleur[0]=='v')
			{
				joueur[i].pion[j].C = ECURIE_C-1-j*2-1;
				joueur[i].pion[j].L = LIGNE-1;
				plateau_jeu[LIGNE-1][ECURIE_C-1-j*2-1]='V';
				sprintf(temp, "%d", j+1);
				plateau_jeu[LIGNE-1][ECURIE_C-1-j*2]=temp[0];
			}
			if(joueur[i].couleur[0]=='r')
			{
				joueur[i].pion[j].C = COLONNE-2;
				joueur[i].pion[j].L = LIGNE-ECURIE_L+j;
				plateau_jeu[LIGNE-ECURIE_L+j][COLONNE-2]='R';
				sprintf(temp, "%d", j+1);
				plateau_jeu[LIGNE-ECURIE_L+j][COLONNE-1]=temp[0];
			}
		}
	}
	return nb_chevaux;
}

int deplacement(char plateau_jeu[LIGNE][COLONNE], struct Joueur *joueur, int premier)
{
	int resultat_des=lancer_des(), deplacement =0;
	char temp[2];
	for(int i=0; i<LIGNE; i++)
	{
		for(int j=0; j<COLONNE; j++)
		{
			if(i<=LIGNE/2 && j<=ECURIE_C)		//dans zone jaune
			{
				if(resultat_des==6 && joueur[premier].couleur[0]=='j' && plateau_jeu[i][j]=='J' && i==ECURIE_L-1 && j==0 && plateau_jeu[i+1][j]=='*')
				{
					if(joueur[premier].type == 0)
					{
						do{
							printf("%s(%s) a fait un 6, mettre en jeu un cheval ?(o/n) ", joueur[premier].nom, joueur[premier].couleur);
							lire(temp, 2);
						}while(temp[1]!='\0' || (temp[0]!='o' && temp[0]!='O' && temp[0]!='n' && temp[0]!='N') );
					}
					if(temp[0]=='o' || temp[0]=='O' || joueur[premier].type == 1)
					{
						plateau_jeu[i+1][j]= plateau_jeu[i][j];
						plateau_jeu[i][j]=' ';
						plateau_jeu[i+1][j+1]=plateau_jeu[i][j+1];
						plateau_jeu[i][j+1]=' ';
						int ajout=1;
						char carac=plateau_jeu[i-ajout][j];
						while(carac=='J')
						{
							plateau_jeu[i-ajout+1][j]=plateau_jeu[i-ajout][j];
							plateau_jeu[i-ajout+1][j+1]=plateau_jeu[i-ajout][j+1];
							ajout++;
							carac=plateau_jeu[i-ajout][j];
							if(carac!='J')
							{
							plateau_jeu[i-ajout+1][j]=' ';
							plateau_jeu[i-ajout+1][j+1]=' ';
							}
						}
					}
				}
				else if(resultat_des==6 && joueur[premier].couleur[0]=='j' && plateau_jeu[i][j]=='J' && i==ECURIE_L-1 && j==0 && plateau_jeu[i+1][j]!='J')
				{

				}
			}
			else if(i<LIGNE/2)		//dans zone bleu
			{
				if(resultat_des==6 && joueur[premier].couleur[0]=='b' && plateau_jeu[i][j]=='B' && i==0 && j==COLONNE-ECURIE_C)
				{
					if(joueur[premier].type == 0)
					{
						do{
							printf("%s(%s) a fait un 6, mettre en jeu un cheval ?(o/n) ", joueur[premier].nom, joueur[premier].couleur);
							lire(temp, 2);
						}while(temp[1]!='\0' || (temp[0]!='o' && temp[0]!='O' && temp[0]!='n' && temp[0]!='N') );
					}
					if(temp[0]=='o' || temp[0]=='O' || joueur[premier].type == 1)
					{
						plateau_jeu[i][j-2]= plateau_jeu[i][j];
						plateau_jeu[i][j]=' ';
						plateau_jeu[i][j-1]=plateau_jeu[i][j+1];
						plateau_jeu[i][j+1]=' ';
						int ajout=2;
						char carac=plateau_jeu[i][j+ajout];
						while(carac=='B')
						{
							plateau_jeu[i][j+ajout-2]=plateau_jeu[i][j+ajout];
							plateau_jeu[i][j+ajout-1]=plateau_jeu[i][j+ajout+1];
							ajout+=2;
							carac=plateau_jeu[i][j+ajout];
							if(carac!='B')
							{
								plateau_jeu[i][j+ajout-2]=' ';
								plateau_jeu[i][j+ajout-1]=' ';
							}
						}
					}
				}
			}
			else if(j<COLONNE/2)		//dans zone verte
			{
				if(resultat_des==6 && joueur[premier].couleur[0]=='v' && plateau_jeu[i][j]=='V' && i==LIGNE-1 && j==ECURIE_C-2)
				{
					if(joueur[premier].type == 0)
					{
						do{
							printf("%s(%s) a fait un 6, mettre en jeu un cheval ?(o/n) ", joueur[premier].nom, joueur[premier].couleur);
							lire(temp, 2);
						}while(temp[1]!='\0' || (temp[0]!='o' && temp[0]!='O' && temp[0]!='n' && temp[0]!='N') );
					}
					if(temp[0]=='o' || temp[0]=='O' || joueur[premier].type == 1)
					{
						plateau_jeu[i][j+2]= plateau_jeu[i][j];
						plateau_jeu[i][j]=' ';
						plateau_jeu[i][j+3]=plateau_jeu[i][j+1];
						plateau_jeu[i][j+1]=' ';
						int ajout=2;
						char carac=plateau_jeu[i][j+ajout];
						while(carac=='V')
						{
							plateau_jeu[i][j-ajout+2]=plateau_jeu[i][j-ajout];
							plateau_jeu[i][j-ajout+3]=plateau_jeu[i][j-ajout+1];
							ajout+=2;
							carac=plateau_jeu[i][j-ajout];
							if(carac!='V')
							{
							plateau_jeu[i][j-ajout+2]=' ';
							plateau_jeu[i][j-ajout+3]=' ';
							}
						}
					}
				}
			}
			else		//dans zone rouge
			{
				if(resultat_des==6 &&  joueur[premier].couleur[0]=='r' && plateau_jeu[i][j]=='R' && i==LIGNE-ECURIE_L && j==COLONNE-2)
				{
					if(joueur[premier].type == 0)
					{
						do{
							printf("%s(%s) a fait un 6, mettre en jeu un cheval ?(o/n) ", joueur[premier].nom, joueur[premier].couleur);
							lire(temp, 2);
						}while(temp[1]!='\0' || (temp[0]!='o' && temp[0]!='O' && temp[0]!='n' && temp[0]!='N') );
					}
					if(temp[0]=='o' || temp[0]=='O' || joueur[premier].type == 1)
					{
						plateau_jeu[i-1][j]= plateau_jeu[i][j];
						plateau_jeu[i][j]=' ';
						plateau_jeu[i-1][j+1]=plateau_jeu[i][j+1];
						plateau_jeu[i][j+1]=' ';
						int ajout=1;
						char carac=plateau_jeu[i+ajout][j];
						while(carac=='R')
						{
							plateau_jeu[i+ajout-1][j]=plateau_jeu[i+ajout][j];
							plateau_jeu[i+ajout-1][j+1]=plateau_jeu[i+ajout][j+1];
							ajout++;
							carac=plateau_jeu[i+ajout][j];
							if(carac!='R')
							{
							plateau_jeu[i+ajout-1][j]=' ';
							plateau_jeu[i+ajout-1][j+1]=' ';
							}
						}
					}
				}
			}
		}
	}
	return deplacement;
}

void dep(char plateau_jeu[LIGNE][COLONNE], struct Joueur *joueur, int premier, int nb_chevaux)
{
	int resultat_des=lancer_des(), deplacement = 0, num_pion = 0;
	int a, b;
	char temp[2];
	while(deplacement == 0)
	{
		if(resultat_des==6)
		{
			if(joueur[premier].couleur[0] == 'j' && joueur[premier].pion[num_pion].L == ECURIE_L-1 && joueur[premier].pion[num_pion].C == 0)
			{
				if(joueur[premier].type == 0)
				{
					do{
						printf("%s(%s) a fait un 6, mettre un jeu un pion ?(o/n) ", joueur[premier].nom, joueur[premier].couleur);
						lire(temp, 2);
					}while(temp[1]!='\0' || (temp[0]!='o' && temp[0]!='O' && temp[0]!='n' && temp[0]!='N') );
				}
				if(joueur[premier].type == 1)
				{
					printf("%s(%s) a fait un 6, et sort un cheval\n", joueur[premier].nom, joueur[premier].couleur);
				}
				if(temp[0]=='o' || temp[0]=='O' || joueur[premier].type == 1)
				{
					deplacement++;
					a=ECURIE_L-1;
					b=0;
					plateau_jeu[a+1][b]= plateau_jeu[a][b];
					plateau_jeu[a][b]=' ';
					plateau_jeu[a+1][b+1]=plateau_jeu[a][b+1];
					plateau_jeu[a][b+1]=' ';
					int ajout=1;
					char carac=plateau_jeu[a-ajout][b];
					while(carac=='J')
					{
						plateau_jeu[a-ajout+1][b]=plateau_jeu[a-ajout][b];
						plateau_jeu[a-ajout+1][b+1]=plateau_jeu[a-ajout][b+1];
						ajout++;
						carac=plateau_jeu[a-ajout][b];
						if(carac!='J')
						{
						plateau_jeu[a-ajout+1][b]=' ';
						plateau_jeu[a-ajout+1][b+1]=' ';
						}
					}
				}
			}
			else if(joueur[premier].couleur[0] == 'j')
			{

			}
			else if(joueur[premier].couleur[0] == 'b' && joueur[premier].pion[num_pion].L == 0 && joueur[premier].pion[num_pion].C == COLONNE-ECURIE_C)
			{
				if(joueur[premier].type == 0)
				{
					do{
						printf("%s(%s) a fait un 6, mettre un jeu un pion ?(o/n) ", joueur[premier].nom, joueur[premier].couleur);
						lire(temp, 2);
					}while(temp[1]!='\0' || (temp[0]!='o' && temp[0]!='O' && temp[0]!='n' && temp[0]!='N') );
				}
				if(joueur[premier].type == 1)
				{
					printf("%s(%s) a fait un 6, et sort un cheval\n", joueur[premier].nom, joueur[premier].couleur);
				}
				if(temp[0]=='o' || temp[0]=='O' || joueur[premier].type == 1)
				{
					deplacement++;
					a = 0;
					b = COLONNE-ECURIE_C;
					plateau_jeu[a][b-2]= plateau_jeu[a][b];
					plateau_jeu[a][b]=' ';
					plateau_jeu[a][b-1]=plateau_jeu[a][b+1];
					plateau_jeu[a][b+1]=' ';
					int ajout=2;
					char carac=plateau_jeu[a][b+ajout];
					while(carac=='B')
					{
						plateau_jeu[a][b+ajout-2]=plateau_jeu[a][b+ajout];
						plateau_jeu[a][b+ajout-1]=plateau_jeu[a][b+ajout+1];
						ajout+=2;
						carac=plateau_jeu[a][b+ajout];
						if(carac!='B')
						{
							plateau_jeu[a][b+ajout-2]=' ';
							plateau_jeu[a][b+ajout-1]=' ';
						}
					}
				}
			}
			else if(joueur[premier].couleur[0] == 'r' && joueur[premier].pion[num_pion].L == LIGNE-ECURIE_L && joueur[premier].pion[num_pion].C == COLONNE-2)
			{
				if(joueur[premier].type == 0)
				{
					do{
						printf("%s(%s) a fait un 6, mettre un jeu un pion ?(o/n) ", joueur[premier].nom, joueur[premier].couleur);
						lire(temp, 2);
					}while(temp[1]!='\0' || (temp[0]!='o' && temp[0]!='O' && temp[0]!='n' && temp[0]!='N') );
				}
				if(joueur[premier].type == 1)
				{
					printf("%s(%s) a fait un 6, et sort un cheval\n", joueur[premier].nom, joueur[premier].couleur);
				}
				if(temp[0]=='o' || temp[0]=='O' || joueur[premier].type == 1)
				{
					deplacement++;
					a = LIGNE-ECURIE_L ;
					b = COLONNE-2;
					plateau_jeu[a-1][b]= plateau_jeu[a][b];
					plateau_jeu[a][b]=' ';
					plateau_jeu[a-1][b+1]=plateau_jeu[a][b+1];
					plateau_jeu[a][b+1]=' ';
					int ajout=1;
					char carac=plateau_jeu[a+ajout][b];
					while(carac=='R')
					{
						plateau_jeu[a+ajout-1][b]=plateau_jeu[a+ajout][b];
						plateau_jeu[a+ajout-1][b+1]=plateau_jeu[a+ajout][b+1];
						ajout++;
						carac=plateau_jeu[a+ajout][b];
						if(carac!='R')
						{
						plateau_jeu[a+ajout-1][b]=' ';
						plateau_jeu[a+ajout-1][b+1]=' ';
						}
					}
				}
			}
			else if(joueur[premier].couleur[0] == 'v' && joueur[premier].pion[num_pion].L == LIGNE-1 && joueur[premier].pion[num_pion].C == ECURIE_C-2)
			{
				if(joueur[premier].type == 0)
				{
					do{
						printf("%s(%s) a fait un 6, mettre un jeu un pion ?(o/n) ", joueur[premier].nom, joueur[premier].couleur);
						lire(temp, 2);
					}while(temp[1]!='\0' || (temp[0]!='o' && temp[0]!='O' && temp[0]!='n' && temp[0]!='N') );
				}
				if(joueur[premier].type == 1)
				{
					printf("%s(%s) a fait un 6, et sort un cheval\n", joueur[premier].nom, joueur[premier].couleur);
				}
				if(temp[0]=='o' || temp[0]=='O' || joueur[premier].type == 1)
				{
					deplacement++;
					a = LIGNE-1;
					b = ECURIE_C-2;
					plateau_jeu[a][b+2]= plateau_jeu[a][b];
					plateau_jeu[a][b]=' ';
					plateau_jeu[a][b+3]=plateau_jeu[a][b+1];
					plateau_jeu[a][b+1]=' ';
					int ajout=2;
					char carac=plateau_jeu[a][b+ajout];
					while(carac=='V')
					{
						plateau_jeu[a][b-ajout+2]=plateau_jeu[a][b-ajout];
						plateau_jeu[a][b-ajout+3]=plateau_jeu[a][b-ajout+1];
						ajout+=2;
						carac=plateau_jeu[a][b-ajout];
						if(carac!='V')
						{
						plateau_jeu[a][b-ajout+2]=' ';
						plateau_jeu[a][b-ajout+3]=' ';
						}
					}
				}
			}
		}
		else
		{
			num_pion++;
		}
		if(num_pion==nb_chevaux)
		{
			num_pion=0;
		}
	}
	if(joueur[premier].type == 1)
	{
		attendre(200);
	}
}

int tri(int nb_humain, int nb_ia, struct Joueur *joueur, int premier)
{
	int modif=0, compteur;
	if(joueur[premier].couleur[0]=='j' && modif==0)
	{
		compteur=0;
		while(modif==0 && compteur<nb_humain+nb_ia)
		{
			premier++;
			compteur++;
			if(premier==nb_humain+nb_ia)
			{
				premier=0;
			}
			if(joueur[premier].couleur[0]=='b')
			{
				modif++;
			}
		}
		if(modif==0)
		{
		compteur=0;
			while(modif==0 && compteur<nb_humain+nb_ia)
			{
				premier++;
				compteur++;
				if(premier==nb_humain+nb_ia)
				{
					premier=0;
				}
				if(joueur[premier].couleur[0]=='r')
				{
					modif++;
				}
			}
		}
		if(modif==0)
		{
		compteur=0;
			while(modif==0 && compteur<nb_humain+nb_ia)
			{
				premier++;
				compteur++;
				if(premier==nb_humain+nb_ia)
				{
					premier=0;
				}
				if(joueur[premier].couleur[0]=='v')
				{
					modif++;
				}
			}
		}
	}
	if(joueur[premier].couleur[0]=='b' && modif==0)
	{
		compteur=0;
		while(modif==0 && compteur<nb_humain+nb_ia)
		{
			premier++;
			compteur++;
			if(premier==nb_humain+nb_ia)
			{
				premier=0;
			}
			if(joueur[premier].couleur[0]=='r')
			{
				modif++;
			}
		}
		if(modif==0)
		{
			compteur=0;
			while(modif==0 && compteur<nb_humain+nb_ia)
			{
				premier++;
				compteur++;
				if(premier==nb_humain+nb_ia)
				{
					premier=0;
				}
				if(joueur[premier].couleur[0]=='v')
				{
					modif++;
				}
			}
		}
		if(modif==0)
		{
			compteur=0;
			while(modif==0 && compteur<nb_humain+nb_ia)
			{
				premier++;
				compteur++;
				if(premier==nb_humain+nb_ia)
				{
					premier=0;
				}
				if(joueur[premier].couleur[0]=='j')
				{
					modif++;
				}
			}
		}
	}
	if(joueur[premier].couleur[0]=='r' && modif==0)
	{
		compteur=0;
		while(modif==0 && compteur<nb_humain+nb_ia)
		{
			premier++;
			compteur++;
			if(premier==nb_humain+nb_ia)
			{
				premier=0;
			}
			if(joueur[premier].couleur[0]=='v')
			{
				modif++;
			}
		}
		if(modif==0)
		{
			compteur=0;
			while(modif==0 && compteur<nb_humain+nb_ia)
			{
				premier++;
				compteur++;
				if(premier==nb_humain+nb_ia)
				{
					premier=0;
				}
				if(joueur[premier].couleur[0]=='j')
				{
					modif++;
				}
			}
		}
		if(modif==0)
		{
			compteur=0;
			while(modif==0 && compteur<nb_humain+nb_ia)
			{
				premier++;
				compteur++;
				if(premier==nb_humain+nb_ia)
				{
					premier=0;
				}
				if(joueur[premier].couleur[0]=='b')
				{
					modif++;
				}
			}
		}
	}
	if(joueur[premier].couleur[0]=='v' && modif==0)
	{
		compteur=0;
		while(modif==0 && compteur<nb_humain+nb_ia)
		{
			premier++;
			compteur++;
			if(premier==nb_humain+nb_ia)
			{
				premier=0;
			}
			if(joueur[premier].couleur[0]=='j')
			{
				modif++;
			}
		}
		if(modif==0)
		{
			compteur=0;
			while(modif==0 && compteur<nb_humain+nb_ia)
			{
				premier++;
				compteur++;
				if(premier==nb_humain+nb_ia)
				{
					premier=0;
				}
				if(joueur[premier].couleur[0]=='b')
				{
					modif++;
				}
			}
		}
		if(modif==0)
		{
			compteur=0;
			while(modif==0 && compteur<nb_humain+nb_ia)
			{
				premier++;
				compteur++;
				if(premier==nb_humain+nb_ia)
				{
					premier=0;
				}
				if(joueur[premier].couleur[0]=='r')
				{
					modif++;
				}
			}
		}
	}
	return premier;
}

int lancer_des(void)
{
    srand(time(NULL));
	int des=rand()%6+1;
	while(des!=6)
	{
		des=rand()%6+1;
	}
	return des;
}
int initialisation_nb_humain()
{
	int nb_humain;
	do
	{
		printf("Nombre de joueur (entre 0 et 4): ");
		nb_humain = lireEntier(nb_humain);
	}while( (nb_humain<0 || nb_humain>4) );

	return nb_humain;
}
char *initialisation_nom_humain(int ordre)
{
	char *nom = NULL;
	nom= malloc( sizeof(char*) * 22);
	printf("Nom du joueur %d (20 caractere max): ", ordre+1);
	lire(nom, 22);
	if(nom[20]!='\0'){ printf("Je vous avez prévenu... du coup votre nom est %s\n", nom);}
	nom[20]='\0';

	return nom;
}
void initialisation_couleur_humain(int nb_humain, struct Joueur *humain, int ordre)
{
	int jaune=0, bleu=2, vert=4, rouge=6;
	do
	{
		do
		{
			printf("Couleur de %s (", humain[ordre].nom);
			for(int i=0; i<7; i++)
			{
				for(int j=0; j<6; j++)
				{
					printf("%c",coul[i][j]);
				}
			}
			printf(") : ");
			lire(humain[ordre].couleur, 7);
		}while(humain[ordre].couleur[0]=='\0');
	}while(strcmp(coul[jaune], humain[ordre].couleur) != 0 && strcmp(coul[bleu], humain[ordre].couleur) != 0 && strcmp(coul[vert], humain[ordre].couleur) != 0 && strcmp(coul[rouge], humain[ordre].couleur) != 0);
	if(strcmp(coul[jaune], humain[ordre].couleur) == 0 )
	{
		humain[ordre].couleur[0]='j';
		for(int j=0; j<6; j++)
		{
			coul[jaune][j]='\0';
			if(coul[jaune+1][j]!='\0')
			{
				coul[jaune+1][j]='\0';
			}
			else if(coul[bleu+1][j]!='\0')
			{
				coul[bleu+1][j]='\0';
			}
			else if(coul[vert+1][j]!='\0')
			{
				coul[vert+1][j]='\0';
			}
		}
	}
	else if(strcmp(coul[bleu], humain[ordre].couleur) == 0 )
	{
		humain[ordre].couleur[0]='b';
		for(int j=0; j<6; j++)
		{
			coul[bleu][j]='\0';
			if(coul[bleu+1][j]!='\0')
			{
				coul[bleu+1][j]='\0';
			}
			else if(coul[bleu-1][j]!='\0')
			{
				coul[bleu-1][j]='\0';
			}
		}
	}
	else if(strcmp(coul[vert], humain[ordre].couleur) == 0 )
	{
		humain[ordre].couleur[0]='v';
		for(int j=0; j<6; j++)
		{
			coul[vert][j]='\0';
			if(coul[vert+1][j]!='\0')
			{
				coul[vert+1][j]='\0';
			}
			else if(coul[vert-1][j]!='\0')
			{
				coul[vert-1][j]='\0';
			}
			else if(coul[bleu-1][j]!='\0')
			{
				coul[bleu-1][j]='\0';
			}
		}
	}
	else if(strcmp(coul[rouge], humain[ordre].couleur) == 0 )
	{
		humain[ordre].couleur[0]='r';
		for(int j=0; j<6; j++)
		{
			coul[rouge][j]='\0';
			if(coul[rouge-1][j]!='\0')
			{
				coul[rouge-1][j]='\0';
			}
			else if(coul[vert-1][j]!='\0')
			{
				coul[vert-1][j]='\0';
			}
			else if(coul[bleu-1][j]!='\0')
			{
				coul[bleu-1][j]='\0';
			}
		}
	}

}
void initialisation_humain(int nb_humain, struct Joueur *humain)
{
	for(int i=0; i<nb_humain; i++)
	{
		strcpy(humain[i].nom , initialisation_nom_humain(i) );
		initialisation_couleur_humain(nb_humain, humain, i);
		humain[i].type = 0;
	}
}
int initialisation_nb_ia(int nb_humain)
{
	int nb_ia=0;
	if(nb_humain>=0 && nb_humain<4)
	{
		do
		{
			if(nb_humain==0)
			{
				printf("Nombre de ia (entre %d et %d): ",2,4-nb_humain);
			}
			else if(nb_humain==1)
			{
				printf("Nombre d'IA (entre %d et %d): ",1,4-nb_humain);
			}
			else if(nb_humain>0 && nb_humain<4)
			{
				printf("Nombre d'IA (entre %d et %d): ",0,4-nb_humain);
			}
			nb_ia = lireEntier(nb_ia);
		}while(nb_humain+nb_ia<=1 || nb_humain+nb_ia>4);
	}

	return nb_ia;
}
void initialisation_nom_ia(int nb_humain, int nb_ia, struct Joueur *ia)
{
    srand(time(NULL));
	char nom_drole[][21]={ {"Théo Také"},{"Lucie Fer"},{"Elma Guiche"},{"Aisha faimal"},{"Vincent Tim"},{"Marie Roina"},{"Sam Pique"},{"Emma Maindantaface"},{"Annie hilation"},{"Mateo Porte"},{"Kelly Diote"},{"Jean Peuplu"},{"Ivan Dlad-Rogue"},{"Homer D'Halor"},{"Sophie Fonfek"},{"Garcin Lazare"},{"Terry Dicule"},{"Paul Hisse-Ouvret"},{"Eva Zion"},{"Elie Copter"},{"Camille Zole"},{"Axel Aire"},{"Simon Cusaunnet"} };
	int hasard = 0;
	for(int a=nb_humain; a<nb_ia+nb_humain; a++)
	{
		do
		{
			hasard = rand()%(sizeof(nom_drole)/21);
			strcpy(ia[a].nom, nom_drole[hasard]);
		}while(nom_drole[hasard][0]=='\0');
		nom_drole[hasard][0]='\0';
	}
}
void initialisation_couleur_ia(int nb_ia, struct Joueur *ia, int ordre)
{
	int jaune=0, bleu=2, vert=4, rouge=6;

	if(coul[jaune][0]!='\0')
	{
		ia[ordre].couleur[0]='j';
		for(int j=0; j<6; j++)
		{
			ia[ordre].couleur[j]=coul[jaune][j];
			coul[jaune][j]='\0';
		}
	}
	else if(coul[bleu][0]!='\0')
	{
		ia[ordre].couleur[0]='b';
		for(int j=0; j<6; j++)
		{
			ia[ordre].couleur[j]=coul[bleu][j];
			coul[bleu][j]='\0';
		}
	}
	else if(coul[vert][0]!='\0')
	{
		ia[ordre].couleur[0]='v';
		for(int j=0; j<6; j++)
		{
			ia[ordre].couleur[j]=coul[vert][j];
			coul[vert][j]='\0';
		}
	}
	else if(coul[rouge][0]!='\0')
	{
		ia[ordre].couleur[0]='r';
		for(int j=0; j<6; j++)
		{
			ia[ordre].couleur[j]=coul[rouge][j];
			coul[rouge][j]='\0';
		}
	}
}
void initialisation_ia(int nb_humain, int nb_ia, struct Joueur *ia)
{
	for (int i=nb_humain; i<nb_ia+nb_humain; i++)
	{
		initialisation_couleur_ia(nb_ia, ia, i);
		ia[i].type = 1;
	}
	initialisation_nom_ia(nb_humain, nb_ia, ia);
}
void initialisation_plateau(char plateau_jeu[LIGNE][COLONNE])					//fonction qui initialilse le plateau de jeu
{
  char temp[2];
  int bleu=1,rouge=6,vert=6,jaune=1;
  for(int i=0; i<LIGNE; i++)
	{
		for(int j=0; j<COLONNE; j++)
		{
			if(j%2==0)
			{
				if(i<ECURIE_L && j<ECURIE_C)		//ECURIE_C en haut a gauche JAUNE
				{
					plateau_jeu[i][j]=' ';
				}
				else if(i==LIGNE/2 && j>=1 && j<COLONNE/2-1)
				{
					sprintf(temp, "%d", jaune);
					jaune++;
					plateau_jeu[i][j]=temp[0];
				}
				else if(i<ECURIE_L && j>=COLONNE-ECURIE_C)		//ECURIE_C en haut a droite BLEU
				{
					plateau_jeu[i][j]=' ';
				}
				else if(i>=LIGNE/15 && i<LIGNE/2 && j==COLONNE/2-1)
				{
					sprintf(temp, "%d", bleu);
					bleu++;
					plateau_jeu[i][j]=temp[0];
				}
				else if(i>=LIGNE-ECURIE_L && j<ECURIE_C)		//ECURIE_C en bas a gauche VERT
				{
					plateau_jeu[i][j]=' ';
				}
				else if(i>LIGNE/2 && i<LIGNE-1 && j==COLONNE/2-1)
				{
					sprintf(temp, "%d", vert);
					vert--;
					plateau_jeu[i][j]=temp[0];
				}
				else if(i>=LIGNE-ECURIE_L && j>=COLONNE-ECURIE_C)		//ECURIE_C en bas a droite ROUGE
				{
					plateau_jeu[i][j]=' ';
				}
				else if(i==LIGNE/2 && j>COLONNE/2 && j<=COLONNE - 3)
				{
					sprintf(temp, "%d", rouge);
					rouge--;
					plateau_jeu[i][j]=temp[0];
				}
				else
				{
					plateau_jeu[i][j]='*';
				}
			}
			else if(j<COLONNE)
			{
				plateau_jeu[i][j]=' ';
			}
		}
	}
}
void afficher_plateau(char plateau_jeu[LIGNE][COLONNE])										//fonction qui affiche le plateau de jeu
{
    for(int i=0; i<LIGNE; i++)
	{
        for(int j=0; j<COLONNE; j++)
			{
				if(plateau_jeu[i][j-1]=='J')
				{
					couleur(0, C_BLANC, 0);
				}
				else if(plateau_jeu[i][j-1]=='B')
				{
					couleur(0, C_BLANC, 0);
				}
				else if(plateau_jeu[i][j-1]=='V')
				{
					couleur(0, C_BLANC, 0);
				}
				else if(plateau_jeu[i][j-1]=='R')
				{
					couleur(0, C_BLANC, 0);
				}
				else if(i==LIGNE/2 && j==COLONNE/2)
				{
					couleur(0,0,0);
				}
				else if(i<=LIGNE/2 && j<=ECURIE_C)		//JAUNE
				{
					couleur(0,C_JAUNE,0);
					if(i<ECURIE_L && j<ECURIE_C )
					{
						couleur(0,0,C_JAUNE);
					}
				}
				else if(i<LIGNE/2)		//BLEU
				{
					couleur(0,C_BLEU,0);
					if(i<ECURIE_L && j>=ECURIE_C+ESPACE_C )
					{
						couleur(0,0,C_BLEU);
					}
				}
				else if(j<=COLONNE/2)		//VERT
				{
					couleur(0,C_VERT,0);
					if(i>=LIGNE-ECURIE_L && j<ECURIE_C )
					{
						couleur(0,0,C_VERT);
					}
				}
				else		//ROUGE
				{
					couleur(0,C_ROUGE,0);
					if(i>=LIGNE-ECURIE_L && j>=COLONNE-ECURIE_C )
					{
						couleur(0,0,C_ROUGE);
					}
				}
				if(plateau_jeu[i][j]=='J')		//Cheval JAUNE
				{
					couleur(0,C_JAUNE,0);
				}
				if(plateau_jeu[i][j]=='B')		//Cheval BLEU
				{
					couleur(0,C_BLEU,0);
				}
				if(plateau_jeu[i][j]=='V')		//Cheval VERT
				{
					couleur(0,C_VERT,0);
				}
				if(plateau_jeu[i][j]=='R')		//Cheval ROUGE
				{
					couleur(0,C_ROUGE,0);
				}

				printf("%c",plateau_jeu[i][j]);
            }

		couleur(0,C_BASE,C_BASE);
        printf("\n");
    }
}
void couleur(int attr, int fg, int bg)					//fonction qui ajoute de la couleur en modificant le terminal
{
	char command[13];

		/* command est la commande de controle du terminal */
	sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
	printf("%s", command);
}
void attendre(float temps)							//fonction qui met sur pause un nombre de miliseconde
{
    clock_t arrivee=clock()+(temps*CLOCKS_PER_SEC/100); // On calcule le moment où l'attente devra s'arrêter
    while(clock()<arrivee);
}
void viderBuffer(void)
{
    int caractere = 0;
    while (caractere != '\n' && caractere != EOF)
    {
        caractere = getchar();
    }
}
int lireEntier(int nombre)
{
    char buffer[100] = {0};
	if (lire(buffer, 100))
	{
		sscanf(buffer, "%d", &nombre);
	}
	else
	{
		return -1;
	}
	if(buffer[1]!='\0')
	{
		nombre=9;
	}

    return nombre;
}
int lire(char *chaine, int longueur)
{
    char *positionEntree = NULL;

    if (fgets(chaine, longueur, stdin) != NULL)
    {
        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL)
        {
            *positionEntree = '\0';
        }
        else
        {
            viderBuffer();
        }
        return 1;
    }
    else
    {
        viderBuffer();
        return 0;
    }
}
