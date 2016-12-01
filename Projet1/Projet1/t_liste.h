/**
 * Type de donn�es abstrait qui impl�mente une liste circulaire 
 * avec position courante .
 *
 * Cela signifie que la position suivante du dernier �l�ment est
 * le premier �l�ment et pareillement � l'envers
 *
 * La taille est limit�e � la valeur fournie � la proc�dure d'initialisation.
 *
 * @author Pierre B�lisle (copyright 2016)
 *
 */
#ifndef __T_LISTE__
#define __T_LISTE__

// LISTE_VIDE est consciemment mis � -1
// pour qu'apr�s l'insertion de la premi�re donn�e
// il soit � mis 0 et pointe sur la case du dernier �l�ment entr�e
// dans le tableau.
#define LISTE_VIDE -1

//Liste g�n�rique
typedef void* t_element;

//La repr�sentation m�moire de la liste
typedef struct{

	t_element* tab_donnees;
	int fin;
	int pc;
    int taille;

}t_liste;

// Initialise la liste.   Obligatoire pour le
// bon fonctionnement d'une liste.
void init_liste(t_liste* liste, int taille);

// Fonction bool�enne de base qui retourne TRUE
// si la liste st vide et FALSE sinon.
int liste_est_vide(const t_liste* liste);

// Fonction bool�enne de base qui retourne TRUE
// si la position courante est sur le dernier �l�ment
// significatif de la liste et FALSE sinon.
int pc_a_la_fin(const t_liste* liste);

// L'accesseur d'�l�ment � la position courante,
// sans l'enlever ni d�placer la position courante.
void obtenir_element(const t_liste* liste, t_element* element);

// Acesseur du nombre d'�l�ments dans la liste.
int obtenir_nb_elements(const t_liste* liste);

/*****Les mutateurs*****/

// Ins�re un �l�ment dans la liste � la position courante.
// (ex: 1 3 5 6 ; ins�re 2 avant position 1 donne 1 2 3 5 6
// et la position courante est sur l'�l�ment ins�r� (position 1)
// Insertion est impossible si la file est pleine.
void inserer(t_liste* liste, t_element element);


// Supprime l'�l�ment � la position courante.
// La position courante est sur le prochain �l�ment
// sauf si vide.
void supprimer(t_liste* l);


/*******Les mutatrices de la position courante*****/
// Si l'op�ration est impossible, rien n'est effectu�
// (ex: precedent du premier, suivant d'une liste vide,
//      suivant du dernier,  ...)

//On utilise le terme "set" plut�t que "d�placer" (plus court)
void set_pc_debut(t_liste* liste);
void set_pc_fin(t_liste* liste);

//D�place la position courante sur l'�l�ment suivant de la liste
//La liste est circulaire.  Le suivant du dernier e
void set_pc_suivant(t_liste* liste);


//D�place la position courante sur l'�l�ment pr�c�dent
//Si elle n'est pas vide.
//La liste est circulaire des deux sens.
void set_pc_precedent(t_liste* liste);

#endif