/*
* Tp2 Boite de disjoncteurs :  Programme principal fournit avec des 
* sous-programmes � compl�ter. 
*
* Dans le cadre du cours INF145.  
* Voir �nonc� fourni pour plus de d�tails.
*
* semestre : A16
* Auteur du code : Pierre B�lisle (copyright 2016);
* D'apr�s une id�e de David Beaulieu sugg�r� par Hugues Saulnier.  
* Tous deux charg�s de cours � l'�ts.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h> // EXIT_SUCCESS
#include <limits.h> // INT_MIN

#include "types_et_constantes_globaux.h"

#include "t_boite.h" // Types et SP.

#include "m_graphique.h" // Dessin de la boite en mode graphique.

#include "winBGIm.h" // Graphique Windows.

#include "m_util_dialogue.h" // Boites de dialogue.

#include "mtwister.h" // G�n�rateurs al�atoires.

#include "m_util_ES.h" // Fonctions de saisie et de validation.

#include "t_appareil.h"

#include "m_gestion_menu.h"

/*******************
* CONSTANTES
*******************/
// Taille en pixels par d�faut.
// � modifier si settextstyle est utilis� pour 
// changer la police de caract�res.
#define TAILLE_CAR 8

// Espace gauche et droite.
#define GAP_DROITE 2 * TAILLE_CAR
#define GAP_GAUCHE TAILLE_CAR

// Sert � l'appel d'initwindow.
#define PLEIN_X 1000
#define PLEIN_Y 800

// Pourcentage d'une bo�te remplie au d�part.
#define POURC_REMPLI .60

// Pourcentage de volt == TENSION_ENTREE.
#define POURC_TENSION_ENTREE .30

/*******************
* PROTOTYPES
*******************/
// Remplit la boite avec des disjoncteurs s�lectionn�s au hasard
// � partir des constantes POURC_REMPLI et POURC_TENSION_ENTREE.
void remplir_boite(t_boite* boite);

// Distribue la t�che � effectuer sur la bo�te selon le choix.
void effectuer_tache(char choix, t_boite* boite);


// Affiche les options du menu selon POS_MENU_X et POS_MENU_Y.
void afficher_menu();




int main(void){

    t_boite boite;

    // Plein �cran.  Doit �tre fait avant d'utiliser getmaxx et getmaxy.
    // initwindow ne tient pas compte des param�tre et 
    // ouvre plein �cran (bogue winbgim).
    initwindow(PLEIN_X, PLEIN_Y);

    // Les constantes locales �vite d'appeler 
    // plusieurs fois getmax() et getmaxy().
    const int TAILLE_X = getmaxx();
    const int TAILLE_Y = getmaxy();
    const int MILIEU_X = TAILLE_X / 2;
    const int MILIEU_Y = TAILLE_Y / 2;

    // Initialisation du germe al�atoire.
    mt_srand(time(NULL));

    // Choix de l'utilisateur.
    char choix;

    // Amp�rage demand� � l'utilisateur.
    int max_amperes = 
        boite_saisie_entier_valide_xy("Entrez l'amp�rage de la bo�te",
                                       DIALOGUE_X, DIALOGUE_Y,
                                       AMPERE_TOTAL_MIN, AMPERE_TOTAL_MAX,
                                       HAUT_CENTRE,
                                       WHITE, WHITE);

    // Si l'utilisateur n'a pas annul�.
    if(max_amperes != INT_MIN){

        // On obtient un bo�te vide.
        boite = *obtenir_boite_neuve(max_amperes);

        // Remplit la bo�te avec quelques disjoncteurs
        // selon les constantes POURC_REMPLI et POURC_TENSION_ENTREE.
        //  Abr�ge la saisie de donn�es de d�part.
        // Sert � commencer avec un bo�te quelconque si aucune r�cup�ration
        // n'a �t� effectu�e. 
        //remplir_boite(&boite);

        // Tant que l'utilisateur le d�sire (ESC pour quitter).
        do{

            afficher_boite(&boite);

            afficher_menu();

            choix = getch_graph();

            // Le distributeur de t�ches.
            effectuer_tache(choix, &boite);

        }while (choix != ESC);

    }

    // D�sallouer la m�moire avant de quitter (bonnes pratiques).
    vider_boite(&boite);
    closegraph();

    return EXIT_SUCCESS;
}

/*
* Remplit la boite avec des disjoncteurs s�lectionn�s au hasard
* � partir des constantes POURC_REMPLI et POURC_TENSION_ENTREE.
*/
void remplir_boite(t_boite* boite){

   // En partant, le POURC_REMPLI de la bo�te est en 
   // TENSION_PHASE et le reste en TENSION_ENTREE.  Tous sont allum�s.
   int colonne;
   int ligne;

   // Compte le nombre de disjoncteurs install�s.
   int compteur = 0;

   // Sert � obtenir les diff�rents amp�rages g�n�r�s.
   int ampere;
   
   // Sert � r�cup�rer ceux � installer.
   t_disjoncteur*  disjoncteur;


   // Remplit selon la valeur du POURC_REMPLI du nombre total de disjoncteurs.
   while(compteur < (int) MAX_DISJONCTEURS * POURC_REMPLI){

          // Un amp�rage au hasard.
          ampere = mt_randi(NB_AMPERAGES_TRAITES) - 1;
          colonne = mt_randi(2) - 1;
          ligne = mt_randi(MAX_DISJONCTEURS / 2) - 1;

          // Le pourcentage en volt TENSION_ENTREE.
          if(mt_randf(0,1) < POURC_TENSION_ENTREE){

              // Obtenir un disjoncteur de la bonne tension.
              disjoncteur = 
                  nouveau_disjoncteur(AMPERAGES_PERMIS[ampere],
                                   TENSION_ENTREE);

          }
          // Le reste en TENSION_PHASE.
          else{

              disjoncteur = 
                    nouveau_disjoncteur(AMPERAGES_PERMIS[ampere], 
                                     TENSION_PHASE);
          }

          t_coord c = {colonne, ligne};

          installer_disjoncteur(boite, &c, disjoncteur);

          compteur++;
         
    }
}



// Affiche les options du menu selon POS_MENU_X et POS_MENU_Y.
void afficher_menu(){

    outtextxy(POS_MENU_X,POS_MENU_Y,
        "Options du menu : "
        "1: Ajouter un disjoncteur "
        "2: Ajouter des appareils "
        "3: Sauvegarder "
        "4: R�cup�rer");

    outtextxy(POS_MENU_X,POS_MENU_Y + 20,
        "5: Afficher les appareils d'un disjoncteur "
        "6: Retirer un appareil "
        "7: Retirer un disjoncteur "
        "8: Sugg�rer des disjoncteurs "
        "9: D�faire dernier retrait"
        );

}



// Distribue la t�che � effectuer sur la bo�te selon le choix.
void effectuer_tache(char choix, t_boite* boite){

    /*
    * Utilisation de switch-case si possible (bonne pratique).
    */

    // Rien n'est effectu� si le choix ne fait pas partie du menu.
    switch(choix)
    {

    case '1': ajouter_disjoncteur(boite);break;
    case '2': ajouter_des_appareils(boite);break;
    case '3': sauvegarder_boite(boite);break;
    case '4': recuperer_boite(boite);break;
    case '5': afficher_appareils(boite);break;
    case '6': retirer_appareil(boite);break;

              boite_message("Appuyez sur une touche pour quitter",
                             500, 700, 300, 20, WHITE, WHITE);

              getch();
              break;

     case '7': retirer_disjoncteur(boite);break;

     case '8' : suggerer_disjoncteurs(boite);break;

     case '9' : defaire_retraits(boite);




    }
}







