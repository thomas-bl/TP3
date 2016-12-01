/*
* Impl�mentation du module de type t_pile
*
* Auteur : Pierre B�lisle (copyright A2016).
* 
*/
#include "t_pile.h" // t_pile, PILE_VIDE, MAX_ELEMENTS

// Proc�dure pour initialiser une pile, la pile sera vide apr�s un appel
// De cette proc�dure. peut aussi �tre utilis� pour vider une pile.
void init_pile(t_pile * pile){

    /*
    * Strat�gie: Il suffit de mettre le sommet en dehors
    * de la pile pour pr�tendre qu'elle est vide.  
    * Le  tableau n'a pas � �tre modifi�. 
    */
    pile->sommet = PILE_VIDE;
}

// Fonction pour v�rifier si une pile est pleine.
int  pile_est_pleine(const t_pile* pile){

    //On compare le sommet avec le nombre d'�l�ments maximum possibles. 
    return pile->sommet == MAX_ELEMENTS;
}

// Fonction qui retourne si une pile est vide.
int  pile_est_vide(const t_pile* pile){

    //On compare le sommet avec la constante pr�vue. 
    return pile->sommet == PILE_VIDE;

}

// Proc�dure pour ajouter un �l�ment au sommet d'une pile.
void empiler(t_pile* pile, t_element element){

    /*
    * Strat�gie : On utilise la pr�-incr�mentation  du C 
    * sur le sommet avant de mettre l'�l�ment dans le tableau.
    */

    pile->tab[++pile->sommet] = element;
}

// Proc�dure pour enlever un �l�ment du sommet d'une pile et
// le retourner via le param�tre formel (passage par r�f�rence).
void desempiler(t_pile* pile, t_element* adr_element){

    /*
    * Strat�gie : On utilise la post-d�cr�mentation  du C 
    * sur le sommet et on retourne l'l�ment qui se trouve
    * au nouveau sommmet.
    */

    *adr_element = pile->tab[pile->sommet--];
}

// Fonction qui retourne l'�l�ment du dessus sans le d�sempiler.
void get_dessus(const t_pile* pile, t_element * adr_element){

    /*
    * Strat�gie : Retourne l'�l�ment au somment sans 
    * d�crm�menter le sommet.
    */

    *adr_element = pile->tab[pile->sommet];

}

// Fonction qui retourne le nombre d'�l�ments actuellement dans la pile.
int get_nb_elements(const t_pile* pile){

   /*
    * Strat�gie : Il s'av�re que sommet + 1 est �gal au nombre 
    * d'�l�ments actuellement dans la pile.
    */

    return pile->sommet+1;

}

