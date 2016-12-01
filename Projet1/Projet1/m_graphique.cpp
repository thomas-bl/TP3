/*
* Module qui permet la gestion d'une boîte électrique
* avec disjoncteurs.
*
* La boite doit d'abord être initialisée au nombre d'ampère voulu.
*
*/
#include <stdio.h>
#include <math.h>
#include "types_et_constantes_globaux.h"
#include "winBGIm.h"
#include "m_graphique.h"
#include "m_util_fonctions.h"


/*
* Fonction locale qui affiche le contour d'un disjoncteur
* avec les valeurs reçues.
*/ 
void afficher_contour_disjoncteur(double ampere, 
                                  int tension,
                                  int puissance, 
                                  int gauche, 
                                  int haut,
                                  int couleur){

    // Contour du disjoncteur
    setcolor(couleur);

    char msg [TAILLE_MSG] = {0};

    // Aide à la clarté de la lecture du code.
    int droite = gauche + LARGEUR_DISJONCTEUR;
    int bas = haut + HAUTEUR_DISJONCTEUR;
    int gauche_dep = gauche;

    //// Affiche ampère et tension
    outtextxy(gauche, haut -  TAILLE_CAR, double_a_chaine(ampere));

    gauche+=strlen(double_a_chaine(ampere)) * TAILLE_CAR;
    outtextxy(gauche, haut - TAILLE_CAR, "A/");

    gauche+=strlen("A/") * TAILLE_CAR;
    outtextxy(gauche, haut - TAILLE_CAR, itoa(tension, msg, 10));

    gauche+=strlen(msg) * TAILLE_CAR;
    outtextxy(gauche, haut - TAILLE_CAR, "V/");

    gauche+=strlen("V/") * TAILLE_CAR;
    outtextxy(gauche, haut - TAILLE_CAR, double_a_chaine(puissance * tension));

    gauche+=strlen(double_a_chaine(puissance * tension)) * TAILLE_CAR;
    outtextxy(gauche, haut - TAILLE_CAR, "W");

    // Afficher le contour
    rectangle(gauche_dep, haut, droite, bas);

}

// Affiche un carré COULEUR_ALLUME ou COULEUR_ETEINT selon l'état.
// La bonne position a été calculée préalablement.
void afficher_interrupteur(int etat,
                           int tension,
                           int gauche, 
                           int haut){

    // Calcul la position dans le disjoncteur selon son état.
    gauche = (etat)
               ? gauche 
                   : gauche + (LARGEUR_DISJONCTEUR / 2);

    // Afficher l'état de l'interrupteur à l'aide du remplissage.
    setfillstyle(1, 
        (etat)?COULEUR_ALLUME:COULEUR_ETEINT);

    // Afficher l'interrupteur à l'aide de bar.
    bar(gauche, 
        haut, 
        gauche + LARGEUR_DISJONCTEUR / 2,
        haut + HAUTEUR_DISJONCTEUR);

}

// Effectue les calculs pour afficher le contour et l'interrupteur
// au bon endroit à l'écran.
void afficher_disjoncteur(const t_boite* boite, 
                          int colonne, 
                          int ligne, 
                          int GAP_AUTOUR_X,
                          int GAP_AUTOUR_Y){

    // Pout obtenir un disjoncteur non vide de la boîte.
    t_disjoncteur* disjoncteur;

    disjoncteur = boite->tab_disjoncteurs[ligne][colonne];

    // Tiens compte du gap en x avant la boite.
    int gauche = colonne *  
                 (GAP_X + LARGEUR_DISJONCTEUR) + GAP_X + GAP_AUTOUR_X;

    // Si c'est vide, on affiche un contour prévu pour les disjoncteurs vides,
    // ampère et tension à 0.
    if(disjoncteur == NULL){

            // Tiens compte du gap en y avant la boite.
            int haut = ligne  * 
               (HAUTEUR_DISJONCTEUR + GAP_Y) + GAP_Y + GAP_AUTOUR_Y;


            afficher_contour_disjoncteur(0, 0, 0, 
                                         gauche, haut, COULEUR_CONTOUR_DISJ_VIDE);
    }

    // Sinon, on affiche le disjoncteur selon son état.
    else{


        // Tiens compte du gap en y avant la boite.
        int haut = ligne  * 
            (HAUTEUR_DISJONCTEUR +  GAP_Y)  + GAP_Y + GAP_AUTOUR_Y;

        afficher_contour_disjoncteur(disjoncteur->ampere, 
                                     disjoncteur->tension,
                                     disjoncteur->demande_du_circuit,
                                     gauche, haut, COULEUR_CONTOUR_DISJ);  

        afficher_interrupteur(disjoncteur->etat, 
                              disjoncteur->tension, 
                              gauche, 
                              haut);     
    }


    
}

// Contour de la boîte qui s'adapte au nombre de disjoncteurs.
void afficher_cadre_autour(int largeur_boite, 
                           int hauteur_boite,
                           int GAP_AUTOUR_X,
                           int GAP_AUTOUR_Y){


    int droite = getmaxx() - GAP_AUTOUR_X;

    int bas = GAP_AUTOUR_Y + hauteur_boite + GAP_Y;

    setcolor(BLUE);
    rectangle(GAP_AUTOUR_X, GAP_AUTOUR_Y, droite, bas);

}


/*
* Fonction locale pour afficher le temps UPS, l'ampérage de la boîte 
* et la puissance totale consommée.
*/
void afficher_info_boite(const t_boite* boite, 
     int* hauteur_car, int* largeur_car){

    // Gestion des saut de ligne selon la taille du texte.
    int ligne;
    setcolor(WHITE);
    settextstyle(1,0,1);

    *hauteur_car = textheight("a");
    *largeur_car = textwidth("a");

    ligne = POS_INFO_Y;

    rectangle (POS_INFO_X, 
               POS_INFO_Y, 
               POS_INFO_X + *largeur_car * LARGEUR_BOX, 
               POS_INFO_Y + *hauteur_car * HAUTEUR_BOX);

    char msg[TAILLE_MSG];
    sprintf_s(msg, "Capacité : %4.0lf A", boite->nb_amperes);
    outtextxy(POS_INFO_X + TAILLE_CAR, POS_INFO_Y + ligne, msg);

    ligne+= *hauteur_car;
    sprintf_s(msg, "Total consommée : %4.0lf W", consommation_totale(boite));
    outtextxy(POS_INFO_X + TAILLE_CAR, POS_INFO_Y + ligne, msg);

    ligne+= *hauteur_car;
    sprintf_s(msg, "UPS : %4.2lf heure(s) disponible(s)", temps_ups(boite));
    outtextxy(POS_INFO_X + TAILLE_CAR, POS_INFO_Y + ligne, msg);

    ligne+= *hauteur_car;
    sprintf_s(msg, 
              "Nombre de disjoncteurs %d V: %d", 
              TENSION_PHASE, 
              nb_disjoncteurs_tension(boite, TENSION_PHASE));

    outtextxy(POS_INFO_X + TAILLE_CAR, POS_INFO_Y + ligne, msg);

    ligne+= *hauteur_car;
    sprintf_s(msg, 
              "Nombre de disjoncteurs %d V: %d", 
              TENSION_ENTREE, 
              nb_disjoncteurs_tension(boite, TENSION_ENTREE));

    outtextxy(POS_INFO_X + TAILLE_CAR, POS_INFO_Y + ligne, msg);


}


// Affiche la boîte électrique
// et l'état de ses disjoncteurs
void afficher_boite(const t_boite* boite){

    /*
    * Stratégie : L'affichage a été découpé en plusieurs sous-=programmes.
    * Ici, le travail consiste à obtenir les valeurs de l'écran pour afficher
    * la boîte centrée avec tous ses disjoncteurs.
    */
    int NB_COL = NB_COLONNES;

    // Recevoir la taille des caractères après l'affichage des infos.
    int hauteur_car;
    int largeur_car;

    int nb_disjoncteurs = nb_disjoncteurs_actuel(boite);

    // Selon le nombre de colonnes à intervalles égaux.
    int largeur_boite = (NB_COLONNES * LARGEUR_DISJONCTEUR +
                        (NB_COLONNES + 1) * GAP_X);

       
    // Dépend du nombre de lignes de disjoncteurs (2 x ligne).
    int hauteur_boite =  
        NB_LIGNES_MAX * (HAUTEUR_DISJONCTEUR + GAP_Y) + 2 * GAP_Y;

    // Retient la taille des carcayères avant d'afficher les infos.
    textsettingstype ts;
    gettextsettings(&ts);

    cleardevice();

    afficher_info_boite(boite, &hauteur_car, &largeur_car);

    // Remet les caractères à leur taille initiale.
    settextstyle(ts.font,ts.direction,ts.charsize);

    // Espace autour de la boite.
    int GAP_AUTOUR_X = (getmaxx() - largeur_boite) / 2;
    int GAP_AUTOUR_Y = HAUTEUR_BOX * hauteur_car +  2 * GAP_Y;

    
    afficher_cadre_autour(largeur_boite, 
                          hauteur_boite, 
                          GAP_AUTOUR_X, 
                          GAP_AUTOUR_Y);


    // Affiche les disjoncteurs à l'intérieur de la boite.
    for(int i = 0; i < NB_COLONNES; i++){
        for(int j = 0; j < NB_LIGNES_MAX; j++){
            
            afficher_disjoncteur(boite, 
                                 i, j, 
                                 GAP_AUTOUR_X, 
                                 GAP_AUTOUR_Y + GAP_Y);
        }
    }
}