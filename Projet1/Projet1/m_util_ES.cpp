/*
* Module de fonctions utilitaires pour les entr�es-sorties
* du programme de disjoncteurs A16 INF145 (voir �nonc�).
*
* Auteur : Pierre B�lisle (copyright A2016).
*/
// Les modules utilis�es et la raison.
#include <limits.h> //INT_MIN

#include "types_et_constantes_globaux.h" //DEPLACEMENT_Y

#include "m_util_ES.h"
#include "m_util_dialogue.h" // Bo�tes de saisie.
#include "m_util_fonctions.h" // double__chaine

#include "t_disjoncteur.h" // t_appareil, AMPERAGES_PERMIS, NB_AMPERAGES_TRAITES
#include "t_boite.h" // NB_COLONNES, NB_LIGNES_MAX
#include "winBGIm.h" //  WHITE, 


/*
* Module qui permet l'interaction avec l'utilisateur dans le projet pour
* saisir et valider tension, amp�rage, ligne, colonne et demande.
*/

// Retourne une paire (colonne-ligne) valide via les param�tres.
void obtenir_position_valide(int x, int y, 
                             int* colonne, int* ligne, 
                             int position_msg){

     /*
     * Strat�gie : On lit les valeurs en commen�ant � 1 alors il faut
     * soustraire 1 pour concorder avec le tableau de disjoncteurs.

     */

                       
    *colonne = 
        boite_saisie_entier_valide_xy("Entrez la colonne du disjoncteur",
                                      x, y,
                                      1, NB_COLONNES,
                                      position_msg,
                                      WHITE, WHITE);

     // Si l'utlisateur n'a pas annul�.
     if(*colonne != INT_MIN){

         (*colonne)--;

         *ligne = 
             boite_saisie_entier_valide_xy("Entrez la position du disjoncteur",
                                           x, y + DEPLACEMENT_Y,
                                           1, NB_LIGNES_MAX,
                                           position_msg,
                                           WHITE, WHITE);

         if(*ligne != INT_MIN){
             (*ligne)--;
         }
     }

}


/*
* Fonction  pour saisir et valider la tension d'un disjoncteur. 
*/
int tension_valide(int x, int y, int position_msg) {

    int tension;

    do{
        tension = 
            boite_saisie_entier_valide_xy("Entrez la tension du disjoncteur",
                                          x, y,
                                          TENSION_PHASE, TENSION_ENTREE,
                                          position_msg,
                                          WHITE, WHITE);

    }while(tension != INT_MIN && 
        tension != TENSION_ENTREE &&
        tension != TENSION_PHASE);

    return tension;
}

/*
* Fonction bool�enne locale pour v�rifier si l'amp�re 
* re�u est dans le tableau des amp�rages permis.
*/
static int ampereDsTableau(int ampere) {

    /*
    * Strat�gie : Utilise la fouille lin�aire.  Un while et un bool�en 
    * pour que la boucle se termine au tour suivant que la valeur est trouv�e.
    */

    int permis = FALSE;

    int i = 0;

    while(i < NB_AMPERAGES_TRAITES && !permis){

        // Affectation de l'expression directement dans la variable.
        permis = ampere == AMPERAGES_PERMIS[i];
        i++;
    }

    return permis;
}


/*
* Fonction pour saisir et valider l'amp�rage d'un disjoncteur. 
*/
int ampere_valide(int x, int y, int position_msg) {

    /*
    * Strat�gie : En utilisant boite_saisie_valide_entier_xy, la validation 
    * entre les bornes est effectu�e.  Ensuite, on valide les amp�rages permis
    * � l'aide de la fonction locale ampereDsTableau.
    *
    * � noter : Nous sommes conscient que cette strat�gie ne r�agit pas
    * de fa�on identique pour les erreurs de limites et celle d'existence.
    */

    int ampere;

    int valide;

    do{
       ampere = boite_saisie_entier_valide_xy(
           "Entrez l'amp�rage du disjoncteur",
           x, y,
           AMPERAGES_PERMIS[0], AMPERAGES_PERMIS[NB_AMPERAGES_TRAITES-1],
           position_msg,
           WHITE, WHITE);

       // �vite pls appels pour �tre utilis� dans l'ent�te du while.
       valide =  ampereDsTableau(ampere);

       if(!valide && ampere != INT_MIN){

           cleardevice();
           boite_message("L'amp�rage n'est pas valide (voir �nonc�)",
                         DIALOGUE_X, 
                         DIALOGUE_Y,
                         500, 30, WHITE, WHITE);
           delay(2000);
           cleardevice();
       }

    }while(ampere != INT_MIN && !valide);

    return ampere;
}

// Affiche un tableau de coordonn�es (colonne-ligne).
// Seules les nb_coords premi�res coordonn�es sont affich�es.
void afficher_coords(t_coord tab_coords[], int nb_coords){

    /*
    * Strat�gie : On affiche les coordonn�es avec boite_message
    * et les fonctions de string.h.
    */
    // Valeur approximative calcul�e � l'oeil.
    const int HAUTEUR = 30;
    const int LARGEUR = 200;

    t_chaine buf;
    t_chaine buf2;

    int y = 200;

    for(int i = 0; i < nb_coords; i++){

        // Pourrait �tre dans un SP.  On conact�ne les valeurs
        // en le entourant de parenth�ses.
        strcpy(buf, "("); 
        strcat(buf, _itoa(tab_coords[i].col+1, buf2, BASE));
        strcat(buf, "-");
        strcat(buf, _itoa(tab_coords[i].lig+1, buf2, BASE));
        strcat(buf, ")");

        boite_message(buf,10, y += HAUTEUR, LARGEUR, HAUTEUR, WHITE, BLUE);
    }

}

// Affiche un appareil � la position re�ue.
void afficher_appareil(int x, int y, 
                       const t_appareil* appareil){

    /*
    * Strat�gie : On utilise les fonctions de string.h pour construire
    * les messages � transmetre � boite_message.
    */

    const int HAUTEUR = 30;
    const int LARGEUR = 200;

    // Sert � la construction des cha�nes.
    t_chaine buf;
    t_chaine buf2;

    strcpy(buf, "Cat�gorie : "); 
    char* str_cat = strcat(buf, appareil->categorie);
    boite_message(str_cat,x, y, LARGEUR, HAUTEUR, WHITE, BLUE);


    strcpy(buf, "Emplacement : "); 
    char* str_piece = strcat(buf, appareil->emplacement);
    boite_message(str_piece,x, y += HAUTEUR , LARGEUR, HAUTEUR, WHITE, BLUE);

    strcpy(buf, "Ampere : ");     
    char* str_ampere = strcat(buf, double_a_chaine(appareil->ampere));
    boite_message(str_ampere,x, y += HAUTEUR, LARGEUR, HAUTEUR, WHITE, BLUE);

    strcpy(buf, "Tension : ");     
    char* str_tension =  strcat(buf, _itoa(appareil->tension, buf2, BASE));
    boite_message(str_tension,x, y += HAUTEUR, LARGEUR, HAUTEUR, WHITE, BLUE);
}

// Affiche tous les appareils du tableau.  La fonction afficher_appareil 
// doit exister.
void afficher_les_appareils(t_appareil* tab_appareils[], 
                            int nb_appareils){

    // Valeur approximative calcul�e � l'oeil.
    const int POS_X = 100;

    const int HAUTEUR_MAX = 500;

    // Changement de colonne et de ligne.
    const int DEP_X = 210;
    const int DEP_Y = 130;


    int x = POS_X;
    int y = 0;


    // Affiche tous les appareils en prenant soin de ne
    // pas d�passer le bas de l'�cran et en changeant de
    // colonne si cela arrive.
    for(int i = 0; i < nb_appareils; i++){


        // Il y a de bien meilleur fa�on de g�rer 
        // l'�cran.  SI cela vous int�resse, voyez viewport en C.
        if(y > HAUTEUR_MAX){
            x += DEP_X;
            y = 0;
        }


        afficher_appareil(x,y+=DEP_Y, tab_appareils[i]);
    }

}

