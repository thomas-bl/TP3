/**
 * Type de données abstrait qui implémente une liste circulaire 
 * avec position courante .
 *
 * Cela signifie que la position suivante du dernier élément est
 * le premier élément et pareillement à l'envers
 *
 * La taille est limitée à la valeur fournie à la procédure d'initialisation.
 *
 * @author Pierre Bélisle (copyright 2016)
 *
 */
#ifndef __T_LISTE__
#define __T_LISTE__

// LISTE_VIDE est consciemment mis à -1
// pour qu'après l'insertion de la première donnée
// il soit à mis 0 et pointe sur la case du dernier élément entrée
// dans le tableau.
#define LISTE_VIDE -1

//Liste générique
typedef void* t_element;

//La représentation mémoire de la liste
typedef struct{

	t_element* tab_donnees;
	int fin;
	int pc;
    int taille;

}t_liste;

// Initialise la liste.   Obligatoire pour le
// bon fonctionnement d'une liste.
void init_liste(t_liste* liste, int taille);

// Fonction booléenne de base qui retourne TRUE
// si la liste st vide et FALSE sinon.
int liste_est_vide(const t_liste* liste);

// Fonction booléenne de base qui retourne TRUE
// si la position courante est sur le dernier élément
// significatif de la liste et FALSE sinon.
int pc_a_la_fin(const t_liste* liste);

// L'accesseur d'élément à la position courante,
// sans l'enlever ni déplacer la position courante.
void obtenir_element(const t_liste* liste, t_element* element);

// Acesseur du nombre d'éléments dans la liste.
int obtenir_nb_elements(const t_liste* liste);

/*****Les mutateurs*****/

// Insère un élément dans la liste à la position courante.
// (ex: 1 3 5 6 ; insère 2 avant position 1 donne 1 2 3 5 6
// et la position courante est sur l'élément inséré (position 1)
// Insertion est impossible si la file est pleine.
void inserer(t_liste* liste, t_element element);


// Supprime l'élément à la position courante.
// La position courante est sur le prochain élément
// sauf si vide.
void supprimer(t_liste* l);


/*******Les mutatrices de la position courante*****/
// Si l'opération est impossible, rien n'est effectué
// (ex: precedent du premier, suivant d'une liste vide,
//      suivant du dernier,  ...)

//On utilise le terme "set" plutôt que "déplacer" (plus court)
void set_pc_debut(t_liste* liste);
void set_pc_fin(t_liste* liste);

//Déplace la position courante sur l'élément suivant de la liste
//La liste est circulaire.  Le suivant du dernier e
void set_pc_suivant(t_liste* liste);


//Déplace la position courante sur l'élément précédent
//Si elle n'est pas vide.
//La liste est circulaire des deux sens.
void set_pc_precedent(t_liste* liste);

#endif