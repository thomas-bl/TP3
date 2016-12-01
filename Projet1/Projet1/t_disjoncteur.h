/*
* Module de type qui regroupe tout dans le projet qui concerne un
* disjoncteur.
*
* On y retrouve les constantes, d�finition de type et sous-programme
* li� � un disjoncteur.
*/
#ifndef __T_DISJONCTEUR__
#define __T_DISJONCTEUR__


//---------------FICHIERS EN-TETE UTILES------------------

//contient toutes les constantes utiles
#include "types_et_constantes_globaux.h"

//contient le type t_liste qui va retenir les appareil
#include "t_liste.h"

//contient la d�finition de l'appareil
#include "t_appareil.h"

//pour g�rer les FILE*
#include <stdio.h>

//Pour les cas impossibles
#include <assert.h>

//--------------CONSTANTES LOCALES-------------------------

// �tats de l'interrupteur d'un disjoncteur.
#define ALLUME 1 // � l'installation.
#define ETEINT 0 // surcharge de courant.

// Tous les amp�rages consid�r�s pour un disjoncteur.
const int AMPERAGES_PERMIS[] = {15, 20, 40, 50, 60};

// Nombre d'amp�rages diff�rents possibles (tableau de constantes)
#define NB_AMPERAGES_TRAITES 5

// Coefficient calcul puissance
#define COEFF_PUISSANCE 0.8

#define MAX_APPAREILS 50


//-----------------DEFINITION DES TYPES---------------------------

// On conserve l'amp�rage, le voltage, l'�tat (ALLUME ou ETEINT),
// la demande en courant sur le circuit et un tableau de r�f�rences
// vers les appareils branch�s sur ce disjoncteur
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

	//Tableau de pointeurs vers les appareils branch�s sur ce disjoncteur
	t_liste* ref_appareils;

}t_disjoncteur;





//---------DEFINITION DES SOUS-PROGRAMMES---------------------

// Retourne un disjoncteur initialis� aux valeurs fournies.
t_disjoncteur* nouveau_disjoncteur(int ampere, int tension);

// Retourne la puissance maximum possible pour le disjoncteur.
// Ne doit pas �tre NULL. Aucune validation.
int puissance_max(const t_disjoncteur* disjoncteur);

//Change l'�tat du disjoncteur selon si la demande en puissance d�passe 
//ou non le max
void tester_etat_disjoncteur(t_disjoncteur* disjoncteur);


/*Calcule la demande totale en amp�res de tous les appareils branch�s
* sur un disjoncteur, et met le r�sultat dans disjoncteur.demande_du_circuit
*/
void calculer_demande_totale(t_disjoncteur* disjoncteur);


//sous programme qui lit un �l�ment dans la liste, le convertit en appareil
//et met la position courante � la case suivante
static t_appareil lire_appareil(t_liste* liste);




/*permet d'ajouter un appareil dans la liste d'appareil
* n�cessite de fournir toutes les caract�ristiques de l'appareil
*
* s'occupe aussi d'actualiser la consommation sur le disjoncteur
* ET son �tat
*/

void ajouter_appareil(t_disjoncteur* disjoncteur, 
	t_appareil* appareil);



/////////////////////////////////////////////////////////////////////////////////////////////////////
//Prototypes Seb
/////////////////////////////////////////////////////////////////////////////////////////////////////

t_appareil** obtenir_appareils(t_disjoncteur* disjoncteur,int *nb_appareils);



void* vider_appareil(t_disjoncteur* disjoncteur);




/////////////////////////////////////////////////////////////////////////////////////////////////////
#endif