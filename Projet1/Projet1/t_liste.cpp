/**
 * Implémente une liste circulaire avec position courante .
 *
 * Cela signifie que la position suivante du dernier élément est
 * le premier élément et pareillement à l'envers
 *
 * La taille est limitée à MAX_ELEMENTS
 *
 * @author Pierre Bélisle (copyright 2016).
 *
 */
#include <stdlib.h>
#include <assert.h>
#include "t_liste.h"

 /*
 * Stratégie : Une variable  retient où est le dernier élément 
 * significatif.  Le nombre d'éléments est 1 de plus que sa valeur.
 *
 * Toutes les opérations se font à la position courante.
 *
 * Pour l'insertion, on décale à droite et pour la suppression on décale
 * à gauche.  Dans  les deux cas, le pointeur de fin est affecté.
 *
 * Si liste->fin == LISTE_VIDE, il n'y a aucun élément.
 */


// PROCÉDURES LOCALES
// Décale toutes les données du tableau d'une case vers la 
// droite de la case de départ à la case de fin inclusivement.
// Aucune vérification de la valeur des indices, ils
// doivent être valides.   Si depart < 0 ou que fin >= MAX_ELEMENTS - 1
// le programme risque de planter.
static void decaler_droite(t_element tab[], int depart, int fin){

    /*
    * Stratégie : On utilise un for (puisqu'on connait le 
    * nombre d'itération) de la fin vers le début en déplaçant
    * les valeurs d'une case à droite.  La case 0 est la plus à gauche.
    */
    int i;

    // De la fin vers le début.
    for(i = fin; i >= depart; i--){

        // On décale d'une case.
        tab[i+1] = tab[i];
    }
    
}


// Décale toutes les données du tableau d'une case vers la 
// gauche de la case de départ à la case de fin inclusivement.
// Aucune vérification de la valeur des indices, ils
// doivent être valides.Si depart <= 0 ou que fin >= MAX_ELEMENTS - 1
// le programme risque de planter.
static void decaler_gauche(t_element tab[],  int depart, int fin){

    /*
    * Stratégie : On utilise un for (puisqu'on connait le 
    * nombre d'itération) du départ vers la fin en déplaçant
    * les valeurs d'une case à gauche.  La case 0 est la plus à gauche.
    */
    int i;

    // De la fin vers le début.
    for(i = depart; i <= fin; i++){

        // On décale d'une case.
        tab[i] = tab[i+1];
    }
    
}

// PROCÉDURES PUBLICS
//La liste est initialisée à LISTE_VIDE
void init_liste(t_liste* liste, int taille){

 /*
 * Stratégie: Simplement initialiser les indices.
 * Le tableau de la liste a été alloué statiquement dans 
 * cet exemple-ci.
 *
 */ 

 liste->tab_donnees = (t_element*) malloc (sizeof(t_element) * taille);

 liste->fin = LISTE_VIDE;
 liste->pc = 0;
 liste->taille = taille;

}

// Fonction booléenne de base qui retourne TRUE
// si la position courante est sur le dernier élément
// significatif de la liste et FALSE sinon.
int pc_a_la_fin(const t_liste* liste){

    return liste->pc == liste->fin;
}

//Déplace la position courante sur le premier élément de la
//liste si la liste n'est pas vide
void set_pc_debut(t_liste* liste){

 liste->pc = 0;
}

//Déplace la position courante à la fin
// Ne gère pas les cas d'exception (fin invalide).
void set_pc_fin(t_liste* liste){

 liste->pc = liste->fin;
 }

//Déplace la position courante sur l'élément suivant de la liste
//La liste est circulaire.  Le suivant du dernier est le premier.
void set_pc_suivant(t_liste* liste){

 // Liste circulaire. Si pc est au dernier élément, le suivant est 0.
 // On utilise le modulo pour retourner le pc à 0 (évite un if).
 liste->pc = (liste->pc+1) % (liste->fin + 1);
}

//Déplace la position courante sur l'élément précédent
//Si elle n'est pas vide.
//La liste est circulaire des deux sens.
void set_pc_precedent(t_liste* liste){

 // Liste circulaire.  liste->pc == 0 si pc est au premier élément.
 //on le remet à la fin avec l'opérateur ternaire.
 liste->pc = (liste->pc == 0) ?liste->fin : liste->pc-1;

}

//Retourne l'élément à la position courante via le pointeur
//Une erreur pour une liste vide.
void obtenir_element(const t_liste* liste, t_element* element){

  // Existe uniquement pour l'encapsulation.
  *element =  liste->tab_donnees[liste->pc];


}

//Retourne le nombre d'éléments de la liste
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


//Insère un élément dans la liste à la position courante.
// (ex: 1 3 5 6 ; insère 2 avant position 1 donne 1 2 3 5 6
// et la position courante est sur l'élément inséré (position 1)
// Insertion est impossible si la file est pleine.
void inserer(t_liste* liste,t_element element){

 /*
 * Stratégie : On décale toutes les données vers la droite à l'aide
 * d'une procédure locale. Ensuite l'élement est inséré et
 * l'indice de fin est mis à jour..
 */
    // Cas d'exception.
    assert(liste != NULL);
    assert(!liste_est_pleine(liste));

    // On sait que si la liste vide ou si pc == 0, la boucle de 
    // décalage n'aura pas lieu.
    decaler_droite(liste->tab_donnees, liste->pc, liste->fin);

    // Met l'éélément dans la liste.
    liste->tab_donnees[liste->pc] = element;

    // On met le pointeur de fin sur le dernier
    // élément significatif du tableau.
    liste->fin++;

}

// Supprime l'élément à la position courante.
// La position courante est sur le prochain élément
// sauf si vide.
void supprimer(t_liste*  liste){

 /*
 * Stratégie : On décale toutes les données vers la gauche à l'aide
 * d'une procédure locale. Ensuite l'indice de fin est mis à jour.
 */

    // Cas d'exception.
    assert(liste != NULL);
    assert(!liste_est_vide(liste));

    // La liste ne doit pas être vide.
    decaler_gauche(liste->tab_donnees, liste->pc+1, liste->fin);

    // Si la pc est sur la fin, il faut replacer pc sur le
    // le nouveau dernier élément.
    if(liste->fin == liste->pc){

        liste->pc--;
    }

    // Après la suppression du dernier élément, il
    // se remet tout seul à LISTE_VIDE.
    liste->fin--;
}















