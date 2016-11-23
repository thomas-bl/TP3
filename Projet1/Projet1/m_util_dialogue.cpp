/*
* Implémentation de l'utilitaire de dialogue
* en mode graphique décrit dans le fichier de spécification(.h)
*
* Quelques sous-programmes sont ajoutés et décrits plus loin.
* Comme ils n'ont pas de prototype, l'ordre est parfois important.
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <float.h>

#include "m_util_dialogue.h" // La position possible des messages (GAUCHE, ...)
#include "types_et_constantes_globaux.h" // TAILLE_CAR, PRECISION
#include "winbgim.h" // SP graphique et boites de dialogue Windows de fichier.
#include "m_util_fonctions.h"

// Max digits pour la saisie d'un entier.
#define CHIFFRE_MAX 9999999


// Code ASCII de ces caractères pour la saisie.
#define BACKSPACE 8
#define ENTER 13
#define MOINS '-'
#define LE_POINT '.'


// Limites des valeurs pour les chiffres.
#define ASCII_ZERO '0'
#define ASCII_NEUF '9'


// La base pour convertir un entier en chaîne avec itoa.
#define BASE 10

// Utilisé pour la construction d'un nombre réel.
#define DEBUT -1

// C++
/*
* Stratégie : Utilisation de C++ pour faciliter le dialogue
*            pour la sauvegarde et l'ouverture d'un fichier.
*
* source : https://latedev.wordpress.com/2011/10/06/simple-windows-dialogs-from-c-part-1/
*/
char* boite_sauver_fichier ( const char* prompt ) {

    const int BUFSIZE = 200;
    char* buffer = (char*) calloc(BUFSIZE, sizeof(char));
    OPENFILENAME ofns = {0};
    ofns.lStructSize = sizeof( ofns );
    ofns.lpstrFile = buffer;
    ofns.nMaxFile = BUFSIZE;
    ofns.lpstrTitle = prompt;
    ofns.lpstrFilter = "All\0*.*\0Text\0*.XLS\0";
    GetSaveFileName( & ofns);
    
    return buffer;
}
  
char*  boite_ouvrir_fichier( const char* prompt ) {
    const int BUFSIZE = 200;
    char* buffer = (char*) calloc(BUFSIZE, sizeof(char));
    OPENFILENAME ofns = {0};
    ofns.lStructSize = sizeof( ofns );
    ofns.lpstrFile = buffer;
    ofns.nMaxFile = BUFSIZE;
    ofns.lpstrTitle = prompt;
    GetOpenFileName( & ofns );
    return buffer;
}
  



/*************************************************
chiffre_valide (fonction locale)
**************************************************
Retourne un chiffre valide entre ASCII_ZERO et ASCII_NEUF ou
ENTER, ESC ou BACKSPACE ou MOINS
*/

char chiffre_valide(){


    // Caractère saisi de retour.
    char car;

    do{
        // On lit un caractère.
        car = getch_graph();

    }while((car < ASCII_ZERO || car > ASCII_NEUF) && 
        car != ENTER && 
        car != BACKSPACE &&
        car != ESC &&
        car != MOINS);

    return car;
}
/*************************************************
entier_xy (fonction locale)
**************************************************
Lit seulement les caractères numériques
tant qu'il n'y a pas eu ENTER ou ESC. Ils sont assemblés pour
former un entier.  Les caractères sont mis de la couleur voulue.
*/
int entier_xy(int x, int y, int couleur_texte){

    /*
    * Stratégie : Avec chiffre_valide(), on obtient un caractère, 
    * il est convertit en chiffre de type entier et on l'ajoute au nombre.
    * comme seul les caractères valides sont considérés, il y a moins de
    * cas à tester après la saisie.  La saisie du caractère valide est dans la
    * fonction locale précédente et le reste est gérée ici.
    */

    // Permet de conservée l'entier à retourner.
    int valeur = 0;

    // Sert à saisir un caractère à la fois.
    char car = '0';

    // Utilisé en cas de retour arrière.
    char dernier_car;

    // Itérateur
    int nb_car = 0;

    // Position de départ de l'affichage des caractères entrés.
    int posx = x + TAILLE_CAR;

    // Pour la lisibilité du code.
    int premier_car = TRUE;

    // Le signe devient négatif seulement si le MOINS est entré
    // en première position.
    int signe = 1;

    // Respecter la demande.
    setcolor(couleur_texte);

    // Tant qu'on pas pas eu un ENTER, un ESC et au moins un chiffre.
    do{

        // On obtient un caractère valide en prenant soin de retenir le 
        // précédent pour utilisation future avec BACKSPACE.
        dernier_car = premier_car;

        // Seul un caractère valide pour un entier.
        car = chiffre_valide();

        // Le MOINS est acceptable juste comme premier caractère.
        if(premier_car && car == MOINS){
            premier_car = FALSE;
            signe = -1;
            outtextxy(posx, y, car_a_chaine(MOINS));
            posx+=TAILLE_CAR;
        }

        // On recule et on efface le caractère si c'est BACKSPACE.
        else if(car == BACKSPACE){

            // On ne va pas en bas de 0.
            nb_car = (nb_car)?nb_car-1:0;

            // On doit enlever le dernier digit.
            if(dernier_car != MOINS){
                valeur = valeur / BASE;
            }

            // On ne s'occupe pas d'un BACKSPACE au premier caractère donc
            // si la position a bougée, on replace la posx.
            if(posx - TAILLE_CAR > x + TAILLE_CAR){

                // On recule et on efface sans aller avant x + TAILLE_CAR.
                posx= (posx-TAILLE_CAR > x + TAILLE_CAR)
                    ?posx-TAILLE_CAR
                    :x+TAILLE_CAR;
            }

            // On a retiré le dernier caractère.
            else{
                valeur = 0;
                premier_car = TRUE;
                signe = 1;
                posx = x + TAILLE_CAR;
                car = '\0';
            }

            // Effacer le caractère.
            outtextxy(posx,y," ");

        }

        // Si ce n'est pas ENTER ou ESC, c'est un chiffre,
        // on affiche et on passe au caractère suivant.
        else if(car >= ASCII_ZERO && car <= ASCII_NEUF && valeur < CHIFFRE_MAX){         

            valeur = valeur * BASE + (car - ASCII_ZERO);
            outtextxy(posx,y,car_a_chaine(car));
            posx+=TAILLE_CAR;
            nb_car++;

            // Au cas où c'est la première fois.
            premier_car = FALSE;
        }

        // Escape, on veut retourner INT_MIN.
        else if (car == ESC){
            valeur = INT_MIN;
        }

    }while((nb_car == 0 || (car != ENTER && nb_car !=0)) && car != ESC);

    return valeur * signe;

}
/*************************************************
reel_xy (fonction locale)
**************************************************
Lit seulement les caractères numériques, le MOINS et LE_POINT
tant qu'il n'y a pas eu ENTER ou ESC elle les assemble pour
former un réel.  La différence avec entier_xy c'est qu'il 
y a la gestion du point et de la précision 
(nombre de décimal après le point). Les caractères sont 
de la couleur voulue.
*/
double reel_xy(int x, int y, int precision, int couleur_texte){

    /*
    * Stratégie : Avec getch_graph(), on obtient un caractère à
    * la fois qu'on conserve dans un tableau de caractères.  
    * Ensuite, ce tableau est converti avec la fonction 
    * atof de <string.h> en ayant pris soin de  
    * considérer la précision. 
    */

    // Position de départ de l'affichage des caractères entrés.
    int posx = x + TAILLE_CAR;

    // Sera mis à TRUE si le POINT est appuyé.
    int point_deja_entre = FALSE;

    // Le signe du nombre à retourner.
    int signe = 1;

    // Sert à concaténer les valeur entrées et à convertir
    // en réel avec atof.  Un assez gros nombre est possible.
    char nombre_en_chaine[TAILLE_MSG];

    // Itérateur.
    int nb_car = 0;

    // Sert à la saisie du caractère.
    char car;

    // À retourner.
    double valeur = DBL_MIN;

    // Pour gérer la précision.
    int position_du_point = DEBUT;

    // Une des conditions de sortie.
    int au_moins_un_chiffre = FALSE;

    // Respecter la demande.
    setcolor(couleur_texte);

    // Tant qu'on pas pas eu un ENTER, un ESC et au moins un chiffre.
    do{
        car  = getch_graph();

        // Le moins est accepté seulement si c'est le premier.
        if(nb_car == 0 && car == MOINS){
                signe = -1;
                outtextxy(posx, y, car_a_chaine(MOINS));
                posx+=TAILLE_CAR;

                // On retient le caractère.
                nombre_en_chaine[nb_car++] = car;
                
        }

        // Le POINT est acceptable comme premier_car mais aussi n'importe où 
        // mais une seule fois.
        else if(car == LE_POINT && !point_deja_entre){
                point_deja_entre = TRUE;
                position_du_point = nb_car;
                outtextxy(posx, y, car_a_chaine(LE_POINT));  
                posx+=TAILLE_CAR;            

                // On retient le caractère.
                nombre_en_chaine[nb_car++] = car;
        }
        
        // On recule pour effacer le caractère si c'est BACKSPACE.
        else if(car == BACKSPACE && nb_car != 0){

            // Enlève le BACKSPACE mais on ne va pas en base de 0.
            nb_car = (nb_car)?nb_car-1:0;

            // Si on a effacé le MOINS, le signe redevient positif.
            if(nombre_en_chaine[nb_car] == MOINS){
                signe = 1;
            }

            // On retient que le point est entré si c'est le cas.
            else if(nombre_en_chaine[nb_car] == LE_POINT){

                point_deja_entre = FALSE;
                position_du_point = DEBUT;
            }

            // Si tous les caractères sont effacé, 
            //il n'y a pas au moins un chiffre.
            if(nb_car == 0){
                au_moins_un_chiffre = FALSE;
            }

            // On recule et on efface sans aller avant x + TAILLE_CAR.
            posx= (posx-TAILLE_CAR > x + TAILLE_CAR)
                ?posx-TAILLE_CAR
                :x+TAILLE_CAR;

            // Effacer le caractère
            outtextxy(posx,y," ");
        }

        // Si ce n'est pas(MOINS, ENTER, ESC, POINT ou BACKSPACE), c'est un chiffre,
        // on affiche et on passe au caractère suivant.
        else if(car >= ASCII_ZERO && 
                car <= ASCII_NEUF){         

                outtextxy(posx,y,car_a_chaine(car));
                posx+=TAILLE_CAR;

                au_moins_un_chiffre = TRUE;

                // On saisit un caractère.
                nombre_en_chaine[nb_car++] = car;
        }

        // Deuxième condition d'arrêt.
        if(au_moins_un_chiffre && car == ENTER){
            valeur = 0;
            car = ESC;
        }

    }while(car != ESC) ;

    // Si pas annulé.
    if(valeur != DBL_MIN){

        // On termine la chaîne selon la précision.
        if(position_du_point != DEBUT){
            nombre_en_chaine[position_du_point + precision + 1] = '\0';
        }

        // Conversion en réel.
        valeur = atof(nombre_en_chaine);
    }
    return valeur;

}

// Affiche une cadre qui représente une fenêtre de saisie avec
// un message. 
void boite_message(char* msg, 
                   int x, int y,
                   int largeur, int hauteur,
                   int couleur_texte,
                   int couleur_boite){

        // On laisse un gap d'un caractère avant et après la chaîne.
        int droite = x + largeur;
        int bas = y + hauteur;

        // Respecte les couleurs.
        setcolor(couleur_boite);
        rectangle(x - TAILLE_CAR, 
            y - 1, 
            droite +  TAILLE_CAR, 
            bas + 1);

        setcolor(couleur_texte);
        outtextxy(x, y, msg);

}

/*
* Place le x,y du message selon sa position_msg et sa taille_msg.
*/
void obtenir_position_message(int* x_msg, int* y_msg, 
    int position_msg, int taille_msg, int hauteur){


        /*
        * Stratégie : On modifie x_msg et/ou y_msg selon la position reçue.
        *
        *             On obtient ainsi la position de la boîte de message autour 
        *             de la boîte de saisie.
        */

        // x
        switch(position_msg){

            // Déplace la position de x à gauche ou à droite
        case GAUCHE: 
        case HAUT_GAUCHE: 
        case BAS_GAUCHE: *x_msg = *x_msg - taille_msg - 2 * TAILLE_CAR;break;

        case DROITE: 
        case HAUT_DROITE: 
        case BAS_DROITE: *x_msg += taille_msg + 2 * TAILLE_CAR;
        }

        // y
        switch(position_msg){

            // Déplace y en haut.
        case HAUT_CENTRE: 
        case HAUT_GAUCHE: 
        case HAUT_DROITE: *y_msg -= hauteur; break;

            // Déplace y en bas.
        case BAS_CENTRE: 
        case BAS_GAUCHE: 
        case BAS_DROITE: *y_msg += hauteur; break;

        }
}

// Fonction locale pour créer une chaîne vide selon la taille.
// Sert pour effacer le texte dans un rectangle de saisie.
char* msg_vide(int taille){

    char* msg = (char*)calloc(taille, sizeof(char));
    int i;

    for(i = 0; i < taille; i++){

        msg[i] = ' ';
    }

    msg[i] = '\0';

    return msg;
}

// Remplace l'instruction pour clarifier et localiser 
// le code qui efface la chaîne.
void effacer_chaine(int x, int y, int taille_msg){

  outtextxy(x, y, msg_vide(taille_msg));

}

// Boite de saisie de données d'un entier
// qui doit etre entre min et max.  Si 
// l'utilisateur annule, la fonction retourne INT_MIN.
// Un gap d'un caractère avant et après la chaîne.
int boite_saisie_entier_valide_xy(char* msg, 
                                  int x, int y,
                                  int min, int max,
                                  int position_msg,
                                  int couleur_texte,
                                  int couleur_boite){

        /*
        * Stratégie : On calcule les coordonnées pour placer la fenêtre 
        * au centre.  Ensuite, la fonction entier_valide_xy() construit le
        * nombre et nous le retourne.  Si la valeur est INT_MIN, c'est que 
        * l'utilisateur a fait ESC.
        */
        const int HAUTEUR = 2 * textheight(msg);

        int taille_msg = textwidth(msg);
        int bas = y + HAUTEUR;

        int valeur;

        // Sert à retenir la position du message.
        int x_msg = x; 
        int y_msg = y;

        // Retourne la position du message où il faut afficher 
        // la boîte de message.    
        obtenir_position_message(&x_msg, &y_msg, 
                                 position_msg, 
                                 taille_msg, HAUTEUR);

        // Affiche la boîte de message à la position voulue.
        boite_message(msg, 
                      x_msg, y_msg, 
                      taille_msg, HAUTEUR, 
                      couleur_texte, couleur_boite);          

        // Affiche la boîte de saisie.
        setcolor(couleur_boite);

        // Une boîte pour la saisie.
        rectangle(x - TAILLE_CAR, 
            y,
            x + taille_msg + TAILLE_CAR,
            bas);

        // Évite une variable de plus pour positionner 
        // la boîte de saisie.
        y += textheight(msg) / 2;

        // Saisi de la valeur.
        valeur =  entier_xy(x, y, couleur_texte);

        while ((valeur >= CHIFFRE_MAX || valeur < min || valeur > max) &&
            valeur != INT_MIN ){

                // Affiche la boîte de message à la position voulue.
                boite_message(msg, 
                              x_msg, y_msg, 
                              taille_msg, HAUTEUR, 
                              couleur_texte, RED);      

                // Affiche la boîte de saisie en rouge.
                setcolor(RED);

                rectangle(x - TAILLE_CAR, 
                    y - textheight(msg) / 2,
                    x + taille_msg + TAILLE_CAR, 
                    bas);

                effacer_chaine(x, y, taille_msg / TAILLE_CAR);
                valeur =  entier_xy(x, y, couleur_texte);
        }

        return valeur;
}

// Boite de saisie de données à la position x,y 
// d'un nombre réel qui doit etre entre min et max.  Si 
// l'utilisateur annule (ESC), la fonction retourne DOUBLE_MIN.
// Un gap d'un caractère avant et après la chaîne.
double boite_saisie_reel_valide_xy(char* msg, 
                                int x, int y,
                                double min, double max,
                                int position_msg,
                                int precision,
                                int couleur_texte,
                                int couleur_boite){

        /*
        * Stratégie : On calcule les coordonnées pour placer la fenêtre 
        * au centre.  Ensuite, la fonction reel_valide_xy construit le nombre
        * et nous le retourne.  Si la valeur est DBL_MIN, c'est que 
        * l'utilisateur a fait ESC.
        */

        const int HAUTEUR = 2 * textheight(msg);

        int taille_msg = textwidth(msg);
        int bas = y + HAUTEUR;

        double valeur;

        // Sert à obtenir la position du message.
        int x_msg = x; 
        int y_msg = y;

        // Retourne la position du message où afficher la boîte.    
        obtenir_position_message(&x_msg, &y_msg, position_msg, taille_msg, HAUTEUR);

        // Affiche la boîte de message à la position voulue.
        boite_message(msg, 
                      x_msg, y_msg, 
                      taille_msg, HAUTEUR, 
                      couleur_texte, couleur_boite);          

        // Affiche la boîte de saisie.
        setcolor(couleur_boite);

        // Une boîte pour la saisie.
        rectangle(x_msg - TAILLE_CAR, 
            y,
            x_msg + taille_msg + TAILLE_CAR,
            bas);

        y += textheight(msg) / 2;
        
        valeur =  reel_xy(x, y, PRECISION, couleur_texte);

        while ((valeur < min || valeur > max) &&
            valeur != DBL_MIN){

                // Affiche la boîte de message à la position voulue.
                boite_message(msg, 
                              x_msg, y_msg, 
                              taille_msg, HAUTEUR, 
                              couleur_texte, RED);      

                setcolor(RED);
                rectangle(x_msg - TAILLE_CAR, 
                    y - textheight(msg) / 2,
                    x_msg + taille_msg + TAILLE_CAR, 
                    bas);

                effacer_chaine(x_msg, y, taille_msg / TAILLE_CAR);
                valeur =  reel_xy(x, y, PRECISION, couleur_texte);

        }

        return valeur;
}