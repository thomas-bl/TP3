//SEB

/*
* Module utilitaire de sous-programmes fournis
* dans le cadre du tp3 inf1145 A16 (voir énoncé)
*
* Auteur : Pierre Bélisle (Copyright 2016).
*/

// Votre module du tp2.
#include "t_boite.h"

// Déclenche l'ajout d'un disjoncteur dans la boîte.
void ajouter_disjoncteur(t_boite* boite);

// Déclenche la sauvegarde d'une boîte dans un fichier binaire.
void sauvegarder_boite(const t_boite* boite);

// Déclenche la récupération d'une boîte d'un fichier binaire
// et remplit la boite reçu en paramètre, par référence.
void recuperer_boite(t_boite* boite);

// Permet l'utilisateur de retirer un disjoncteur de la boîte.
void retirer_disjoncteur(t_boite* boite);

//Demande les coordonnées du disjoncteur et affiche les informations
//sur les appareils qu'il contient
void afficher_les_appareils_un_disjoncteur(t_boite* boite);


////////////////////////////////////////////////////
//Modif SEB
////////////////////////////////////////////////////
void*vider_boite(t_boite* boite);

void*ajouter_des_appareils(t_boite* boite);

void*afficher_appareils(t_boite* boite);

void*retirer_appareil(t_boite* boite);

void*suggerer_disjoncteurs(t_boite* boite);

void*defaire_retraits(t_boite* boite);



