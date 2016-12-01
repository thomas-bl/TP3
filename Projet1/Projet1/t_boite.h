/*
* Module qui permet la gestion d'une boîte électrique
* avec disjoncteurs.  Il contient tout ce qui concerne une boîte
* électrique dans le cadre du travail pratique.
*
* La boite doit d'abord être initialisée au nombre 
* d'ampères voulus.  Le nombre maximum de disjoncteurs est MAX_DISJONCTEURS.
*
* Tous les sous-programmes public (.h) agissent sur la boîte 
* fournie en paramètre.
*
* La position du disjoncteur fourni à un sous-programme doit être 
* déjà validée.
*
* Aucune validation n'est effectuée par les sous-programmes.
*
* Auteur : Pierre Bélisle
*
* Inspiré d'un énoncé de travail pratique de M. David Beaulieu 
* avec la contribution de M. Hugues Saulnier tous deux chargés 
* de cours à l'Éts.
*
* Session : A2016
*/
#ifndef __T_BOITE__
#define __T_BOITE__

// Nécessaire à la boîte.
#include "t_disjoncteur.h" // Type et SP.


// Constantes globales au projet concernant une boîte.
#define NB_COLONNES 2

// Ampérage minimum possible de la boîte.
#define AMPERE_TOTAL_MIN 100
#define AMPERE_TOTAL_MAX 400

// État d'une position dans la boîte si l'interrupteur
// est absent.
#define VIDE -1

// Les limites en nombre de disjoncteurs
#define MIN_DISJONCTEURS 2
#define MAX_DISJONCTEURS 34

// Maximum de lignes sur une colonne.
#define NB_LIGNES_MAX MAX_DISJONCTEURS / NB_COLONNES





// Aucun disjoncteur au départ dans une boîte neuve.
typedef struct{
    
    // Une boite sur deux colonnes.
    // On ne conserve que les adresses.
    t_disjoncteur* tab_disjoncteurs[NB_LIGNES_MAX][NB_COLONNES];

    //Puissance en entrée.
    double nb_amperes;

}t_boite;



// Ajoutez les protypes manquants selon l'énoncé.

// Retourne l'adresse d'une boite neuve, avec toutes les cases disjoncteurs
// sur NULL
t_boite* obtenir_boite_neuve(int amperage);

//Retourne la puissance totale consommée sur les disjoncteurs.
double puissance_total_boite(const t_boite* boite);

// Retourne la consommation totale en Ampère.
double consommation_totale(const t_boite* boite);

// Retourne le temps de support de la charge.
double temps_ups(const t_boite* boite);

// Retourne le nombre de disjoncteurs actuellement dans la boite.
int nb_disjoncteurs_actuel(const t_boite* boite);

// Retourne le nombre de disjoncteurs de la tension fournie 
// actuellement dans la boite.
int nb_disjoncteurs_tension(const t_boite* boite, int tension);

// Retourne le ratio d'utilisation de la puissance du circuit, en %
double ratio_utilisation(const t_boite* boite);


// Retourne le disjoncteur qui se trouve aux coordonnées reçues.
t_disjoncteur* obtenir_disjoncteur(const t_boite* boite,
	const t_coord* coord);



//sous programme qui retire le disjoncteur aux coordonnées passées en argument
void retirer_un_disjoncteur(t_boite* boite, t_coord* coor);




///////////////////////////////////////////////////////////////////////////////////////
//modif SEB
///////////////////////////////////////////////////////////////////////////////////////
void* installer_disjoncteur(t_boite* boite,t_coord* c,t_disjoncteur* disjoncteur);




#endif