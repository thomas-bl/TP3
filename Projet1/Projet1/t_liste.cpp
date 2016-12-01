/**
 * Impl�mente une liste circulaire avec position courante .
 *
 * Cela signifie que la position suivante du dernier �l�ment est
 * le premier �l�ment et pareillement � l'envers
 *
 * La taille est limit�e � MAX_ELEMENTS
 *
 * @author Pierre B�lisle (copyright 2016).
 *
 */
#include <stdlib.h>
#include <assert.h>
#include "t_liste.h"

 /*
 * Strat�gie : Une variable  retient o� est le dernier �l�ment 
 * significatif.  Le nombre d'�l�ments est 1 de plus que sa valeur.
 *
 * Toutes les op�rations se font � la position courante.
 *
 * Pour l'insertion, on d�cale � droite et pour la suppression on d�cale
 * � gauche.  Dans  les deux cas, le pointeur de fin est affect�.
 *
 * Si liste->fin == LISTE_VIDE, il n'y a aucun �l�ment.
 */


// PROC�DURES LOCALES
// D�cale toutes les donn�es du tableau d'une case vers la 
// droite de la case de d�part � la case de fin inclusivement.
// Aucune v�rification de la valeur des indices, ils
// doivent �tre valides.   Si depart < 0 ou que fin >= MAX_ELEMENTS - 1
// le programme risque de planter.
static void decaler_droite(t_element tab[], int depart, int fin){

    /*
    * Strat�gie : On utilise un for (puisqu'on connait le 
    * nombre d'it�ration) de la fin vers le d�but en d�pla�ant
    * les valeurs d'une case � droite.  La case 0 est la plus � gauche.
    */
    int i;

    // De la fin vers le d�but.
    for(i = fin; i >= depart; i--){

        // On d�cale d'une case.
        tab[i+1] = tab[i];
    }
    
}


// D�cale toutes les donn�es du tableau d'une case vers la 
// gauche de la case de d�part � la case de fin inclusivement.
// Aucune v�rification de la valeur des indices, ils
// doivent �tre valides.Si depart <= 0 ou que fin >= MAX_ELEMENTS - 1
// le programme risque de planter.
static void decaler_gauche(t_element tab[],  int depart, int fin){

    /*
    * Strat�gie : On utilise un for (puisqu'on connait le 
    * nombre d'it�ration) du d�part vers la fin en d�pla�ant
    * les valeurs d'une case � gauche.  La case 0 est la plus � gauche.
    */
    int i;

    // De la fin vers le d�but.
    for(i = depart; i <= fin; i++){

        // On d�cale d'une case.
        tab[i] = tab[i+1];
    }
    
}

// PROC�DURES PUBLICS
//La liste est initialis�e � LISTE_VIDE
void init_liste(t_liste* liste, int taille){

 /*
 * Strat�gie: Simplement initialiser les indices.
 * Le tableau de la liste a �t� allou� statiquement dans 
 * cet exemple-ci.
 *
 */ 

 liste->tab_donnees = (t_element*) malloc (sizeof(t_element) * taille);

 liste->fin = LISTE_VIDE;
 liste->pc = 0;
 liste->taille = taille;

}

// Fonction bool�enne de base qui retourne TRUE
// si la position courante est sur le dernier �l�ment
// significatif de la liste et FALSE sinon.
int pc_a_la_fin(const t_liste* liste){

    return liste->pc == liste->fin;
}

//D�place la position courante sur le premier �l�ment de la
//liste si la liste n'est pas vide
void set_pc_debut(t_liste* liste){

 liste->pc = 0;
}

//D�place la position courante � la fin
// Ne g�re pas les cas d'exception (fin invalide).
void set_pc_fin(t_liste* liste){

 liste->pc = liste->fin;
 }

//D�place la position courante sur l'�l�ment suivant de la liste
//La liste est circulaire.  Le suivant du dernier est le premier.
void set_pc_suivant(t_liste* liste){

 // Liste circulaire. Si pc est au dernier �l�ment, le suivant est 0.
 // On utilise le modulo pour retourner le pc � 0 (�vite un if).
 liste->pc = (liste->pc+1) % (liste->fin + 1);
}

//D�place la position courante sur l'�l�ment pr�c�dent
//Si elle n'est pas vide.
//La liste est circulaire des deux sens.
void set_pc_precedent(t_liste* liste){

 // Liste circulaire.  liste->pc == 0 si pc est au premier �l�ment.
 //on le remet � la fin avec l'op�rateur ternaire.
 liste->pc = (liste->pc == 0) ?liste->fin : liste->pc-1;

}

//Retourne l'�l�ment � la position courante via le pointeur
//Une erreur pour une liste vide.
void obtenir_element(const t_liste* liste, t_element* element){

  // Existe uniquement pour l'encapsulation.
  *element =  liste->tab_donnees[liste->pc];


}

//Retourne le nombre d'�l�ments de la liste
int obtenir_nb_elements(const t_liste*  liste){

  return liste->fin + 1;
}

//Retourne si la liste est vide ou non (TRUE ou FALSE)
int liste_est_vide(const t_liste*  liste){

 return liste->fin == LISTE_VIDE;
}

//Retourne si la liste est pleine ou non (TRUE ou FALSE)
int liste_est_pleine(const t_liste*  liste){

    return liste->fin == liste->taille - 1;
}


//Ins�re un �l�ment dans la liste � la position courante.
// (ex: 1 3 5 6 ; ins�re 2 avant position 1 donne 1 2 3 5 6
// et la position courante est sur l'�l�ment ins�r� (position 1)
// Insertion est impossible si la file est pleine.
void inserer(t_liste* liste,t_element element){

 /*
 * Strat�gie : On d�cale toutes les donn�es vers la droite � l'aide
 * d'une proc�dure locale. Ensuite l'�lement est ins�r� et
 * l'indice de fin est mis � jour..
 */
    // Cas d'exception.
    assert(liste != NULL);
    assert(!liste_est_pleine(liste));

    // On sait que si la liste vide ou si pc == 0, la boucle de 
    // d�calage n'aura pas lieu.
    decaler_droite(liste->tab_donnees, liste->pc, liste->fin);

    // Met l'��l�ment dans la liste.
    liste->tab_donnees[liste->pc] = element;

    // On met le pointeur de fin sur le dernier
    // �l�ment significatif du tableau.
    liste->fin++;

}

// Supprime l'�l�ment � la position courante.
// La position courante est sur le prochain �l�ment
// sauf si vide.
void supprimer(t_liste*  liste){

 /*
 * Strat�gie : On d�cale toutes les donn�es vers la gauche � l'aide
 * d'une proc�dure locale. Ensuite l'indice de fin est mis � jour.
 */

    // Cas d'exception.
    assert(liste != NULL);
    assert(!liste_est_vide(liste));

    // La liste ne doit pas �tre vide.
    decaler_gauche(liste->tab_donnees, liste->pc+1, liste->fin);

    // Si la pc est sur la fin, il faut replacer pc sur le
    // le nouveau dernier �l�ment.
    if(liste->fin == liste->pc){

        liste->pc--;
    }

    // Apr�s la suppression du dernier �l�ment, il
    // se remet tout seul � LISTE_VIDE.
    liste->fin--;
}















