#ifndef __TYPES_ET_CONSTANTES__ 
#define __TYPES_ET_CONSTANTES__ 


/*
* D�fini les constantes globales au projet des disjoncteurs.
*/
#define FALSE 0
#define TRUE 1

#define BASE 10

#define TAILLE_MSG 200

// L'espace entre les disjoncteurs.
#define GAP_X 100
#define GAP_Y 10

// En pixels.
#define LARGEUR_DISJONCTEUR 120
#define HAUTEUR_DISJONCTEUR 20

// Couleur des couleurs d'�tat d'un interrupteur.
#define COULEUR_ALLUME WHITE
#define COULEUR_ETEINT RED

#define COULEUR_CONTOUR_DISJ_VIDE GREEN
#define COULEUR_CONTOUR_DISJ YELLOW

// Taille standard en pixels.
#define TAILLE_CAR 8

// Position et taille du rectangle d'info � l'�cran.
#define POS_INFO_X 10
#define POS_INFO_Y 10
#define LARGEUR_BOX 40
#define HAUTEUR_BOX 6

// Position du menu
#define POS_MENU_X 10
#define POS_MENU_Y 700

// Position des bo�tes de dialogue.
#define DIALOGUE_X 500
#define DIALOGUE_Y 300
#define DEPLACEMENT_Y 60

// Nombre de chiffres d�cimaux acceptables pour un r�el.
#define PRECISION 4

// Touche d'annulation � tous les niveaux.
#define ESC 27

// Maximum de caract�res dans une cha�ne
#define MAX_CAR 30

// Type qui clarifie le code pour manipuler les 
// cha�nes de caract�res.
typedef char t_chaine[MAX_CAR];

// Enregistrement public pour regrouper
// les coordonn�es d'un disjoncteur.
typedef struct{
    int col;
    int lig;
}t_coord;


// Les diff�rentes tensions
#define TENSION_PHASE 120
#define TENSION_ENTREE 240

#endif