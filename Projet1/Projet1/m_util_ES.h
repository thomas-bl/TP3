#include "t_appareil.h"  // Un module à écrire.
/*
* Module qui permet l'interaction avec l'utilisateur dans le projet pour
* saisir et valider tension, ampérage, ligne, colonne et demande.
*
* Auteur : Pierre Bélisle (Copyright 2016).
*/

// Retourne une paire (colonne-ligne) valide via les paramètres
// Si l'utilisateur annule, les valeurs retournées sont INT_MIN.
void obtenir_position_valide(int x, int y, 
                             int* colonne, int* ligne, 
                             int position_msg);


/*
* Fonction pour saisir et valider la tension d'un disjoncteur. 
* La tension est TENSION_PHASE ou TENSION_ENTREE, rien d'autres.
*/
int tension_valide(int x, int y, int position_msg);

/*
* Fonction locale pour saisir et valider l'ampérage d'un disjoncteur.
* L'ampère une des valeurs possibles décrites dans le tableau 
* AMPERAGES_POSSIBLES défini dans t_disjoncteur.h"
*/
int ampere_valide(int x, int y, int position_msg);

// Affiche un tableau de coordonnées (colonne-ligne).
// Seules les nb_coords premières coordonnées sont affichées.
void afficher_coords(t_coord tab_coords[], int nb_coords);

// Affiche un appareil à la position x,y.
void afficher_appareil(int x, int y, const t_appareil* appareil);

// Affiche tous les appareils du tableau.  La fonction afficher_appareil 
// doit exister.
// Si le nombre d'appareils est trop élevé,  l'affichage 
// dépasse l'écran en x.
void afficher_les_appareils(t_appareil* tab_appareils[], 
                            int nb_appareils);