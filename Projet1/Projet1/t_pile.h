/*
* Spécification du module qui implémente un type de données abstrait (TDA)
* qui simule le comportement d'un pile (stack).  Exemple
* présenté dans le cadre du cours inf145.
*
* Auteur : Pierre Bélisle (copyright A2016).
* 
*/
#ifndef __T_PILE__
#define __T_PILE__

// Définitions pour la librairie de fonctions T_PILE.CPP.
#define  MAX_ELEMENTS  50
#define  PILE_VIDE -1

// Changer cette déclaration pour obtenir une pile pour un autre type.
typedef void* t_element;

// Implémentation statique publique.
// À utiliser seulement via les sous-programmes.
typedef struct {
	 t_element  tab[MAX_ELEMENTS];
     int      sommet;
} t_pile;

// Procédure pour initialiser une pile, la pile sera vide après un appel
// De cette procédure. peut aussi être utilisé pour vider une pile.
void init_pile(t_pile * pile);

// Fonction pour vérifier si une pile est pleine.
int  pile_est_pleine(const t_pile* pile);

// Fonction qui retourne si une pile est vide.
int  pile_est_vide(const t_pile* pile);

// Procédure pour ajouter un élément au sommet d'une pile.
void empiler(t_pile* pile, t_element element);

// Procédure pour enlever un élément du sommet d'une pile et
// le retourner via le paramètre formel (passage par référence).
void desempiler(t_pile* pile, t_element* adr_element);

// Fonction qui retourne l'élément du dessus sans le désempiler.
void get_dessus(const t_pile* pile, t_element * adr_element);

// Fonction qui retourne le nombre d'éléments actuellement dans la pile.
int get_nb_elements(const t_pile* pile);

#endif