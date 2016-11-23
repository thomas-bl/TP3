/*
* Module utile pour permettre la saisit dans un 
* environnement graphique.
*
* Il permet la saisie d'un nombre entier, un nombre réel 
* et un nom de fichier pour sauvegarde ou récupération.
*
* Les constantes servent à l'appel de les boîte de saisie
* de valeurs numériques.
*/

// Position possible des messages.
#define HAUT_GAUCHE 0
#define HAUT_CENTRE 1
#define HAUT_DROITE 2
#define GAUCHE 3
#define DROITE 4
#define BAS_GAUCHE 5
#define BAS_CENTRE 6
#define BAS_DROITE 7

// Ouvre une boîte de dialogue pour obtenir un nom de fichier
// à sauvegarder.  Retourne "" si aucun fichier n'a 
// été sélectionné.  Le paramètre est le titre de la boîte.
char* boite_sauver_fichier(const char* titre);

// Ouvre une boîte de dialogue pour obtenir un nom de fichier
// à ouvrir.  Retourne "" si aucun fichier n'a 
// été sélectionné.  Le paramètre est le titre de la boîte.
char* boite_ouvrir_fichier(const char* titre);

// Affiche un message dans une boîte de la couleur reçue
// à la position x,y de la taille fournie.
void boite_message(char* msg, 
                   int x, int y,
                   int largeur, int hauteur,
                   int couleur_texte,
                   int couleur_boite);

// Boite de saisie de données à la position x,y 
// d'un entier qui doit etre entre min et max.  Si 
// l'utilisateur annule (ESC), la fonction retourne INT_MIN.
// Il y a un gap d'un caractère avant et après la chaîne.
int boite_saisie_entier_valide_xy(char* msg, 
                                  int x, int y,
                                  int min, int max,
                                  int position_msg,
                                  int couleur_texte,
                                  int couleur_boite);

// Boite de saisie de données à la position x,y 
// d'un nombr eréel qui doit etre entre min et max.  Si 
// l'utilisateur annule (ESC), la fonction retourne DOUBLE_MIN.
// Il y a un gap d'un caractère avant et après la chaîne.
double boite_saisie_reel_valide_xy(char* msg, 
                                int x, int y,
                                double min, double max,
                                int position_msg,
                                int precision,
                                int couleur_texte,
                                int couleur_boite);