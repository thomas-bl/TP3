/*
* Sp�cification du module qui impl�mente un type de donn�es abstrait (TDA)
* qui simule le comportement d'un pile (stack).  Exemple
* pr�sent� dans le cadre du cours inf145.
*
* Auteur : Pierre B�lisle (copyright A2016).
* 
*/
#ifndef __T_PILE__
#define __T_PILE__

// D�finitions pour la librairie de fonctions T_PILE.CPP.
#define  MAX_ELEMENTS  50
#define  PILE_VIDE -1

// Changer cette d�claration pour obtenir une pile pour un autre type.
typedef void* t_element;

// Impl�mentation statique publique.
// � utiliser seulement via les sous-programmes.
typedef struct {
	 t_element  tab[MAX_ELEMENTS];
     int      sommet;
} t_pile;

// Proc�dure pour initialiser une pile, la pile sera vide apr�s un appel
// De cette proc�dure. peut aussi �tre utilis� pour vider une pile.
void init_pile(t_pile * pile);

// Fonction pour v�rifier si une pile est pleine.
int  pile_est_pleine(const t_pile* pile);

// Fonction qui retourne si une pile est vide.
int  pile_est_vide(const t_pile* pile);

// Proc�dure pour ajouter un �l�ment au sommet d'une pile.
void empiler(t_pile* pile, t_element element);

// Proc�dure pour enlever un �l�ment du sommet d'une pile et
// le retourner via le param�tre formel (passage par r�f�rence).
void desempiler(t_pile* pile, t_element* adr_element);

// Fonction qui retourne l'�l�ment du dessus sans le d�sempiler.
void get_dessus(const t_pile* pile, t_element * adr_element);

// Fonction qui retourne le nombre d'�l�ments actuellement dans la pile.
int get_nb_elements(const t_pile* pile);

#endif