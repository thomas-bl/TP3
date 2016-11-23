/*
* Module de type qui regroupe tout dans le projet qui concerne un
* disjoncteur.
*
* On y retrouve les constantes, définition de type et sous-programme
* lié à un disjoncteur.
*/
#ifndef __T_DISJONCTEUR__
#define __T_DISJONCTEUR__


//---------------FICHIERS EN-TETE UTILES------------------

//contient toutes les constantes utiles
#include "types_et_constantes_globaux.h"

//contient le type t_liste qui va retenir les appareil
#include "t_liste.h"

//contient la définition de l'appareil
#include "t_appareil.h"

//pour gérer les FILE*
#include <stdio.h>



//--------------CONSTANTES LOCALES-------------------------

// États de l'interrupteur d'un disjoncteur.
#define ALLUME 1 // À l'installation.
#define ETEINT 0 // surcharge de courant.

// Tous les ampérages considérés pour un disjoncteur.
const int AMPERAGES_PERMIS[] = {15, 20, 40, 50, 60};

// Nombre d'ampérages différents possibles (tableau de constantes)
#define NB_AMPERAGES_TRAITES 5

// Coefficient calcul puissance
#define COEFF_PUISSANCE 0.8

#define MAX_APPAREILS 50


//-----------------DEFINITION DES TYPES---------------------------

// On conserve l'ampérage, le voltage, l'état (ALLUME ou ETEINT),
// la demande en courant sur le circuit et un tableau de références
// vers les appareils branchés sur ce disjoncteur
typedef struct{

    //En watt
    double ampere;

    //ON - OFF
    int etat;

    // Puissance de la demande actuelle
    // du circuit en amperes
    double demande_du_circuit;

    // TENSION_PHASE ou TENSION_ENTREE
    int tension;

	//Tableau de pointeurs vers les appareils branchés sur ce disjoncteur
	t_liste* ref_appareils;

}t_disjoncteur;





//---------DEFINITION DES SOUS-PROGRAMMES---------------------

// Retourne un disjoncteur initialisé aux valeurs fournies.
t_disjoncteur* nouveau_disjoncteur(int ampere, int tension);

// Retourne la puissance maximum possible pour le disjoncteur.
// Ne doit pas être NULL. Aucune validation.
int puissance_max(const t_disjoncteur* disjoncteur);

//Change l'état du disjoncteur selon si la demande en puissance dépasse 
//ou non le max
void tester_etat_disjoncteur(t_disjoncteur* disjoncteur);


/*Calcule la demande totale en ampères de tous les appareils branchés
* sur un disjoncteur, et met le résultat dans disjoncteur.demande_du_circuit
*/
void calculer_demande_totale(t_disjoncteur* disjoncteur);


//sous programme qui lit un élément dans la liste, le convertit en appareil
//et met la position courante à la case suivante
static t_appareil lire_appareil(t_liste* liste);




/*permet d'ajouter un appareil dans la liste d'appareil
* nécessite de fournir toutes les caractéristiques de l'appareil
*
* s'occupe aussi d'actualiser la consommation sur le disjoncteur
* ET son état
*/

void ajouter_un_appareil(t_disjoncteur* disjoncteur, 
	t_chaine categorie, t_chaine emplacement,
	double ampere, double tension);

#endif