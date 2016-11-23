/*
* Module pour regrouper les sous-programmes qui gère les
* options du menu du tp3 présenté dans Demarrer_simulation 
* (voir énoncé).
*
* @author Pierre Bélisle (copyright 2016) 
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h> 
#include <float.h> // DBL_MIN

#include "m_util_ES.h"
#include "m_gestion_menu.h"
#include "m_util_dialogue.h"
#include "m_util_fonctions.h"
#include "types_et_constantes_globaux.h"
#include "winBGIm.h"
#include "t_pile.h"

// module à écrire
#include "t_appareil.h"

// Mettre vos modules du tp2
#include "t_boite.h"  
#include "t_disjoncteur.h" // 


void retirer_disjoncteur(t_boite* boite){

    t_coord c;

    cleardevice();

    // Les données de position et de taille sont arbitraires et n'ont pas 
    // été mises en constantes.
    boite_message("Quel disjoncteur", 500,200, 100,30, WHITE, WHITE);

    obtenir_position_valide(500,250,
        &c.col, &c.lig, 
        HAUT_CENTRE);

    // Si l'utilisateur n'as pas annulé.
    if(c.col != INT_MIN && c.lig != INT_MIN){

        retirer_un_disjoncteur(boite, &c);
    }

}


// Déclenche l'ajout d'un disjoncteur.
void ajouter_disjoncteur(t_boite* boite){

    cleardevice();

    // Les valeurs à saisir avant l'ajout.
    t_coord c;
    int tension;
    int ampere;

    int ligne_rendu = 1;

    obtenir_position_valide(DIALOGUE_X, DIALOGUE_Y, 
        &c.col, &c.lig, 
        HAUT_CENTRE);

    // Si l'utilisateur n'a pas annulé.
    if(c.col != INT_MIN && c.lig != INT_MIN){

        ligne_rendu++;

        // Il faut la tension et l'ampérage
        tension = tension_valide(DIALOGUE_X,
            DIALOGUE_Y + ligne_rendu * DEPLACEMENT_Y,
            HAUT_CENTRE);

        // Si l'utilisateur n'a pas annulé.
        if(tension != INT_MIN){

            ligne_rendu++;

            // Saisie de l'ampérage.
            ampere = ampere_valide(DIALOGUE_X,
                DIALOGUE_Y + ligne_rendu * DEPLACEMENT_Y, 
                HAUT_CENTRE);

            // Si l'utilisateur n'a pas annulé, on ajoute le disjoncteur.
            if(ampere != INT_MIN){

                t_disjoncteur* disjoncteur = 
                    nouveau_disjoncteur(ampere, tension);

                installer_disjoncteur(boite, &c, disjoncteur);
            }
        }
    }
}



// Procédure locale pour écrire les appareils du 
// disjoncteur.
void sauvegarder_appareil(t_disjoncteur* d, FILE* fic){


    int  nb_appareils;
                
    // On obtient un tableau avec les références vers les appareils.
    t_appareil** tab_appareils = obtenir_appareils(d, &nb_appareils);
    
    // D'abord il faut retenirl e nombre d'appareils.
    fwrite(&nb_appareils,sizeof(int),1,fic);

    // Tous les appareils.
    for(int i = 0; i < nb_appareils; i++){
        fwrite(tab_appareils[i],sizeof(t_appareil),1,fic);
    }


}

// Déclenche la sauvegarde d'une boîte.
void sauvegarder_boite(const t_boite* boite){

    // Utilisation d'une boîte de dialogue Windows.
    char* nom_fic = boite_sauver_fichier("Choisissez un nom de sauvegarde" );

    // Tentative d'ouverture en écriture du fichier.
    FILE* fic = fopen(nom_fic, "wb");

    t_disjoncteur* d;

    t_coord c;

    int existe;

    //  Si l'ouverture a réussi.
    if(fic){

        // On écrit la boîte d'un coup.
        printf("\n%d ", fwrite(&boite->nb_amperes,1, sizeof(double),fic));

        // On parcourt le tableau de disjoncteurs.
        for(c.lig = 0; c.lig < NB_LIGNES_MAX; c.lig++){

            for(c.col = 0; c.col < NB_COLONNES; c.col++){

                // Le disjoncteur à écrire.
                d = obtenir_disjoncteur(boite,&c);

                // On retient dans le fichier si le disjoncteur
                // existe ou non.
                if(d){


                    existe = TRUE;

                    // On indique qu'il y a un disjoncteur à cette position
                    fwrite(&existe,sizeof(int), 1, fic);

                    fwrite(d,sizeof(t_disjoncteur),1,fic);

                    sauvegarder_appareil(d, fic);


                }

                // Si le disjoncteur est NULL, on le remplace par un disjoncteur (0,0).
                // Sert à la récupération.  Si l'ampere est 0, c'est un disjoncteur 
                // qu'il faut remettre à NULL.
                else{

                    existe = FALSE;
                    fwrite(&existe,sizeof(int), 1,fic);
                }
            }

        }
        fclose(fic);
    }


    // Si l'utilisateur n'a pas annulé, il y a eu un problème.
    // On avise.
    else if(strcmp(nom_fic,""))
    {

        cleardevice();

        boite_message("Il y a un problème avec le fichier.  Aucune sauvegarde", 
            DIALOGUE_X, DIALOGUE_Y, 
            500, 20, WHITE, RED);

        //Laisse le temps de voir le message.
        delay(2000);
    }
}


// Procédure locale qui récupère les appareils pour ce
// disjoncteur.
void recuperer_appareils(t_disjoncteur* d, FILE* fic){

    int nb_appareils;
    t_appareil* appareil;

    fread(&nb_appareils,sizeof(int),1,fic);

    for(int k = 0; k < nb_appareils; k++){

        // Création d'un l'appareil vide pour récupération.
        appareil = nouvel_appareil("", "", 0, 0);
        fread(appareil, sizeof(t_appareil), 1, fic);

        ajouter_appareil(d, appareil);

    }

}

// Déclenche la récupération d'une boîte d'un fichier
// binaire et remplit la boite reçu en paramètre, par référence.
void recuperer_boite(t_boite* boite){

    // Utilisation d'une boîte de dialogue Windows.
    char* nom_fic = boite_ouvrir_fichier( "Choisissez une boite à ouvrir" );

    // Tentative d'ouverture en lecture.
    FILE* fic = fopen(nom_fic, "rb");

    int existe;


    // Si le fichier existe
    if(fic){

        vider_boite(boite);

        // On récupère le nombre d'ampères en premier.
        fread(&boite->nb_amperes,sizeof(double),1,fic);

        // On a remplit chaque case du tableau à NULL, il reste 
        // à obtenir les disjoncteurs obtenus du fichier.
        for(int i = 0; i < NB_LIGNES_MAX;i++){

            for(int j = 0; j < NB_COLONNES; j++){

                // On récupère s'il y a une disjoncteur
                fread(&existe, 1, sizeof(int), fic);

                // S'Il n'y en a pas, la case est déjà NULL.
                if(existe){

                    // Un nouveau disjoncteur pour obtenir les données.
                    boite->tab_disjoncteurs[i][j] = nouveau_disjoncteur(0,0);

                    // Lecture directement du disjoncteur dans la boîte.
                    fread(boite->tab_disjoncteurs[i][j],sizeof(t_disjoncteur),1,fic);

                    // Important de réinitialiser la liste et la demande.
                    init_liste(&boite->tab_disjoncteurs[i][j]->liste_appareils);
                    
                    boite->tab_disjoncteurs[i][j]->demande_du_circuit = 0;

                    // Procédure locale pour obtienir les appareils du fichier et
                    // les ajouter au disjoncteur.
                    recuperer_appareils(boite->tab_disjoncteurs[i][j], fic);


                }


            }

        }
        fclose(fic);
    }


    // Si l'utilisateur n'a pas annulé, il y a eu un problème.
    // On avise.
    else if(strcmp(nom_fic,""))
    {

        cleardevice();

        boite_message("Il y a un problème avec le fichier.  Aucune récupération", 
            DIALOGUE_X, DIALOGUE_Y, 
            500, 20, WHITE, RED);

        //Laisse le temps de voir le message.
        getch();
    }
}
