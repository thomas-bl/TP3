/*
* Impl�mentation de l'utilitaire de dialogue
* en mode graphique d�crit dans le fichier de sp�cification(.h)
*
* Quelques sous-programmes sont ajout�s et d�crits plus loin.
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


// Code ASCII de ces caract�res pour la saisie.
#define BACKSPACE 8
#define ENTER 13
#define MOINS '-'
#define LE_POINT '.'


// Limites des valeurs pour les chiffres.
#define ASCII_ZERO '0'
#define ASCII_NEUF '9'


// La base pour convertir un entier en cha�ne avec itoa.
#define BASE 10

// Utilis� pour la construction d'un nombre r�el.
#define DEBUT -1

// C++
/*
* Strat�gie : Utilisation de C++ pour faciliter le dialogue
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


    // Caract�re saisi de retour.
    char car;

    do{
        // On lit un caract�re.
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
Lit seulement les caract�res num�riques
tant qu'il n'y a pas eu ENTER ou ESC. Ils sont assembl�s pour
former un entier.  Les caract�res sont mis de la couleur voulue.
*/
int entier_xy(int x, int y, int couleur_texte){

    /*
    * Strat�gie : Avec chiffre_valide(), on obtient un caract�re, 
    * il est convertit en chiffre de type entier et on l'ajoute au nombre.
    * comme seul les caract�res valides sont consid�r�s, il y a moins de
    * cas � tester apr�s la saisie.  La saisie du caract�re valide est dans la
    * fonction locale pr�c�dente et le reste est g�r�e ici.
    */

    // Permet de conserv�e l'entier � retourner.
    int valeur = 0;

    // Sert � saisir un caract�re � la fois.
    char car = '0';

    // Utilis� en cas de retour arri�re.
    char dernier_car;

    // It�rateur
    int nb_car = 0;

    // Position de d�part de l'affichage des caract�res entr�s.
    int posx = x + TAILLE_CAR;

    // Pour la lisibilit� du code.
    int premier_car = TRUE;

    // Le signe devient n�gatif seulement si le MOINS est entr�
    // en premi�re position.
    int signe = 1;

    // Respecter la demande.
    setcolor(couleur_texte);

    // Tant qu'on pas pas eu un ENTER, un ESC et au moins un chiffre.
    do{

        // On obtient un caract�re valide en prenant soin de retenir le 
        // pr�c�dent pour utilisation future avec BACKSPACE.
        dernier_car = premier_car;

        // Seul un caract�re valide pour un entier.
        car = chiffre_valide();

        // Le MOINS est acceptable juste comme premier caract�re.
        if(premier_car && car == MOINS){
            premier_car = FALSE;
            signe = -1;
            outtextxy(posx, y, car_a_chaine(MOINS));
            posx+=TAILLE_CAR;
        }

        // On recule et on efface le caract�re si c'est BACKSPACE.
        else if(car == BACKSPACE){

            // On ne va pas en bas de 0.
            nb_car = (nb_car)?nb_car-1:0;

            // On doit enlever le dernier digit.
            if(dernier_car != MOINS){
                valeur = valeur / BASE;
            }

            // On ne s'occupe pas d'un BACKSPACE au premier caract�re donc
            // si la position a boug�e, on replace la posx.
            if(posx - TAILLE_CAR > x + TAILLE_CAR){

                // On recule et on efface sans aller avant x + TAILLE_CAR.
                posx= (posx-TAILLE_CAR > x + TAILLE_CAR)
                    ?posx-TAILLE_CAR
                    :x+TAILLE_CAR;
            }

            // On a retir� le dernier caract�re.
            else{
                valeur = 0;
                premier_car = TRUE;
                signe = 1;
                posx = x + TAILLE_CAR;
                car = '\0';
            }

            // Effacer le caract�re.
            outtextxy(posx,y," ");

        }

        // Si ce n'est pas ENTER ou ESC, c'est un chiffre,
        // on affiche et on passe au caract�re suivant.
        else if(car >= ASCII_ZERO && car <= ASCII_NEUF && valeur < CHIFFRE_MAX){         

            valeur = valeur * BASE + (car - ASCII_ZERO);
            outtextxy(posx,y,car_a_chaine(car));
            posx+=TAILLE_CAR;
            nb_car++;

            // Au cas o� c'est la premi�re fois.
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
Lit seulement les caract�res num�riques, le MOINS et LE_POINT
tant qu'il n'y a pas eu ENTER ou ESC elle les assemble pour
former un r�el.  La diff�rence avec entier_xy c'est qu'il 
y a la gestion du point et de la pr�cision 
(nombre de d�cimal apr�s le point). Les caract�res sont 
de la couleur voulue.
*/
double reel_xy(int x, int y, int precision, int couleur_texte){

    /*
    * Strat�gie : Avec getch_graph(), on obtient un caract�re �
    * la fois qu'on conserve dans un tableau de caract�res.  
    * Ensuite, ce tableau est converti avec la fonction 
    * atof de <string.h> en ayant pris soin de  
    * consid�rer la pr�cision. 
    */

    // Position de d�part de l'affichage des caract�res entr�s.
    int posx = x + TAILLE_CAR;

    // Sera mis � TRUE si le POINT est appuy�.
    int point_deja_entre = FALSE;

    // Le signe du nombre � retourner.
    int signe = 1;

    // Sert � concat�ner les valeur entr�es et � convertir
    // en r�el avec atof.  Un assez gros nombre est possible.
    char nombre_en_chaine[TAILLE_MSG];

    // It�rateur.
    int nb_car = 0;

    // Sert � la saisie du caract�re.
    char car;

    // � retourner.
    double valeur = DBL_MIN;

    // Pour g�rer la pr�cision.
    int position_du_point = DEBUT;

    // Une des conditions de sortie.
    int au_moins_un_chiffre = FALSE;

    // Respecter la demande.
    setcolor(couleur_texte);

    // Tant qu'on pas pas eu un ENTER, un ESC et au moins un chiffre.
    do{
        car  = getch_graph();

        // Le moins est accept� seulement si c'est le premier.
        if(nb_car == 0 && car == MOINS){
                signe = -1;
                outtextxy(posx, y, car_a_chaine(MOINS));
                posx+=TAILLE_CAR;

                // On retient le caract�re.
                nombre_en_chaine[nb_car++] = car;
                
        }

        // Le POINT est acceptable comme premier_car mais aussi n'importe o� 
        // mais une seule fois.
        else if(car == LE_POINT && !point_deja_entre){
                point_deja_entre = TRUE;
                position_du_point = nb_car;
                outtextxy(posx, y, car_a_chaine(LE_POINT));  
                posx+=TAILLE_CAR;            

                // On retient le caract�re.
                nombre_en_chaine[nb_car++] = car;
        }
        
        // On recule pour effacer le caract�re si c'est BACKSPACE.
        else if(car == BACKSPACE && nb_car != 0){

            // Enl�ve le BACKSPACE mais on ne va pas en base de 0.
            nb_car = (nb_car)?nb_car-1:0;

            // Si on a effac� le MOINS, le signe redevient positif.
            if(nombre_en_chaine[nb_car] == MOINS){
                signe = 1;
            }

            // On retient que le point est entr� si c'est le cas.
            else if(nombre_en_chaine[nb_car] == LE_POINT){

                point_deja_entre = FALSE;
                position_du_point = DEBUT;
            }

            // Si tous les caract�res sont effac�, 
            //il n'y a pas au moins un chiffre.
            if(nb_car == 0){
                au_moins_un_chiffre = FALSE;
            }

            // On recule et on efface sans aller avant x + TAILLE_CAR.
            posx= (posx-TAILLE_CAR > x + TAILLE_CAR)
                ?posx-TAILLE_CAR
                :x+TAILLE_CAR;

            // Effacer le caract�re
            outtextxy(posx,y," ");
        }

        // Si ce n'est pas(MOINS, ENTER, ESC, POINT ou BACKSPACE), c'est un chiffre,
        // on affiche et on passe au caract�re suivant.
        else if(car >= ASCII_ZERO && 
                car <= ASCII_NEUF){         

                outtextxy(posx,y,car_a_chaine(car));
                posx+=TAILLE_CAR;

                au_moins_un_chiffre = TRUE;

                // On saisit un caract�re.
                nombre_en_chaine[nb_car++] = car;
        }

        // Deuxi�me condition d'arr�t.
        if(au_moins_un_chiffre && car == ENTER){
            valeur = 0;
            car = ESC;
        }

    }while(car != ESC) ;

    // Si pas annul�.
    if(valeur != DBL_MIN){

        // On termine la cha�ne selon la pr�cision.
        if(position_du_point != DEBUT){
            nombre_en_chaine[position_du_point + precision + 1] = '\0';
        }

        // Conversion en r�el.
        valeur = atof(nombre_en_chaine);
    }
    return valeur;

}

// Affiche une cadre qui repr�sente une fen�tre de saisie avec
// un message. 
void boite_message(char* msg, 
                   int x, int y,
                   int largeur, int hauteur,
                   int couleur_texte,
                   int couleur_boite){

        // On laisse un gap d'un caract�re avant et apr�s la cha�ne.
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
        * Strat�gie : On modifie x_msg et/ou y_msg selon la position re�ue.
        *
        *             On obtient ainsi la position de la bo�te de message autour 
        *             de la bo�te de saisie.
        */

        // x
        switch(position_msg){

            // D�place la position de x � gauche ou � droite
        case GAUCHE: 
        case HAUT_GAUCHE: 
        case BAS_GAUCHE: *x_msg = *x_msg - taille_msg - 2 * TAILLE_CAR;break;

        case DROITE: 
        case HAUT_DROITE: 
        case BAS_DROITE: *x_msg += taille_msg + 2 * TAILLE_CAR;
        }

        // y
        switch(position_msg){

            // D�place y en haut.
        case HAUT_CENTRE: 
        case HAUT_GAUCHE: 
        case HAUT_DROITE: *y_msg -= hauteur; break;

            // D�place y en bas.
        case BAS_CENTRE: 
        case BAS_GAUCHE: 
        case BAS_DROITE: *y_msg += hauteur; break;

        }
}

// Fonction locale pour cr�er une cha�ne vide selon la taille.
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
// le code qui efface la cha�ne.
void effacer_chaine(int x, int y, int taille_msg){

  outtextxy(x, y, msg_vide(taille_msg));

}

// Boite de saisie de donn�es d'un entier
// qui doit etre entre min et max.  Si 
// l'utilisateur annule, la fonction retourne INT_MIN.
// Un gap d'un caract�re avant et apr�s la cha�ne.
int boite_saisie_entier_valide_xy(char* msg, 
                                  int x, int y,
                                  int min, int max,
                                  int position_msg,
                                  int couleur_texte,
                                  int couleur_boite){

        /*
        * Strat�gie : On calcule les coordonn�es pour placer la fen�tre 
        * au centre.  Ensuite, la fonction entier_valide_xy() construit le
        * nombre et nous le retourne.  Si la valeur est INT_MIN, c'est que 
        * l'utilisateur a fait ESC.
        */
        const int HAUTEUR = 2 * textheight(msg);

        int taille_msg = textwidth(msg);
        int bas = y + HAUTEUR;

        int valeur;

        // Sert � retenir la position du message.
        int x_msg = x; 
        int y_msg = y;

        // Retourne la position du message o� il faut afficher 
        // la bo�te de message.    
        obtenir_position_message(&x_msg, &y_msg, 
                                 position_msg, 
                                 taille_msg, HAUTEUR);

        // Affiche la bo�te de message � la position voulue.
        boite_message(msg, 
                      x_msg, y_msg, 
                      taille_msg, HAUTEUR, 
                      couleur_texte, couleur_boite);          

        // Affiche la bo�te de saisie.
        setcolor(couleur_boite);

        // Une bo�te pour la saisie.
        rectangle(x - TAILLE_CAR, 
            y,
            x + taille_msg + TAILLE_CAR,
            bas);

        // �vite une variable de plus pour positionner 
        // la bo�te de saisie.
        y += textheight(msg) / 2;

        // Saisi de la valeur.
        valeur =  entier_xy(x, y, couleur_texte);

        while ((valeur >= CHIFFRE_MAX || valeur < min || valeur > max) &&
            valeur != INT_MIN ){

                // Affiche la bo�te de message � la position voulue.
                boite_message(msg, 
                              x_msg, y_msg, 
                              taille_msg, HAUTEUR, 
                              couleur_texte, RED);      

                // Affiche la bo�te de saisie en rouge.
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

// Boite de saisie de donn�es � la position x,y 
// d'un nombre r�el qui doit etre entre min et max.  Si 
// l'utilisateur annule (ESC), la fonction retourne DOUBLE_MIN.
// Un gap d'un caract�re avant et apr�s la cha�ne.
double boite_saisie_reel_valide_xy(char* msg, 
                                int x, int y,
                                double min, double max,
                                int position_msg,
                                int precision,
                                int couleur_texte,
                                int couleur_boite){

        /*
        * Strat�gie : On calcule les coordonn�es pour placer la fen�tre 
        * au centre.  Ensuite, la fonction reel_valide_xy construit le nombre
        * et nous le retourne.  Si la valeur est DBL_MIN, c'est que 
        * l'utilisateur a fait ESC.
        */

        const int HAUTEUR = 2 * textheight(msg);

        int taille_msg = textwidth(msg);
        int bas = y + HAUTEUR;

        double valeur;

        // Sert � obtenir la position du message.
        int x_msg = x; 
        int y_msg = y;

        // Retourne la position du message o� afficher la bo�te.    
        obtenir_position_message(&x_msg, &y_msg, position_msg, taille_msg, HAUTEUR);

        // Affiche la bo�te de message � la position voulue.
        boite_message(msg, 
                      x_msg, y_msg, 
                      taille_msg, HAUTEUR, 
                      couleur_texte, couleur_boite);          

        // Affiche la bo�te de saisie.
        setcolor(couleur_boite);

        // Une bo�te pour la saisie.
        rectangle(x_msg - TAILLE_CAR, 
            y,
            x_msg + taille_msg + TAILLE_CAR,
            bas);

        y += textheight(msg) / 2;
        
        valeur =  reel_xy(x, y, PRECISION, couleur_texte);

        while ((valeur < min || valeur > max) &&
            valeur != DBL_MIN){

                // Affiche la bo�te de message � la position voulue.
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