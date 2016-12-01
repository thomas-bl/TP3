/*
* Implémentation du module de type t_pile
*
* Auteur : Pierre Bélisle (copyright A2016).
* 
*/
#include "t_pile.h" // t_pile, PILE_VIDE, MAX_ELEMENTS

// Procédure pour initialiser une pile, la pile sera vide après un appel
// De cette procédure. peut aussi être utilisé pour vider une pile.
void init_pile(t_pile * pile){

    /*
    * Stratégie: Il suffit de mettre le sommet en dehors
    * de la pile pour prétendre qu'elle est vide.  
    * Le  tableau n'a pas à être modifié. 
    */
    pile->sommet = PILE_VIDE;
}

// Fonction pour vérifier si une pile est pleine.
int  pile_est_pleine(const t_pile* pile){

    //On compare le sommet avec le nombre d'éléments maximum possibles. 
    return pile->sommet == MAX_ELEMENTS;
}

// Fonction qui retourne si une pile est vide.
int  pile_est_vide(const t_pile* pile){

    //On compare le sommet avec la constante prévue. 
    return pile->sommet == PILE_VIDE;

}

// Procédure pour ajouter un élément au sommet d'une pile.
void empiler(t_pile* pile, t_element element){

    /*
    * Stratégie : On utilise la pré-incrémentation  du C 
    * sur le sommet avant de mettre l'élément dans le tableau.
    */

    pile->tab[++pile->sommet] = element;
}

// Procédure pour enlever un élément du sommet d'une pile et
// le retourner via le paramètre formel (passage par référence).
void desempiler(t_pile* pile, t_element* adr_element){

    /*
    * Stratégie : On utilise la post-décrémentation  du C 
    * sur le sommet et on retourne l'lément qui se trouve
    * au nouveau sommmet.
    */

    *adr_element = pile->tab[pile->sommet--];
}

// Fonction qui retourne l'élément du dessus sans le désempiler.
void get_dessus(const t_pile* pile, t_element * adr_element){

    /*
    * Stratégie : Retourne l'élément au somment sans 
    * décrmémenter le sommet.
    */

    *adr_element = pile->tab[pile->sommet];

}

// Fonction qui retourne le nombre d'éléments actuellement dans la pile.
int get_nb_elements(const t_pile* pile){

   /*
    * Stratégie : Il s'avère que sommet + 1 est égal au nombre 
    * d'éléments actuellement dans la pile.
    */

    return pile->sommet+1;

}

