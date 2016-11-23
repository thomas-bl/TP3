/*
* Module de type qui regroupe tout dans le projet qui concerne un
* appareil.
*
* On y retrouve les constantes, définition de type et sous-programme
* lié à un appareil.
*/

#ifndef __T_APPAREIL__
#define __T_APPAREIL__

//contient toutes les constantes utiles
#include "types_et_constantes_globaux.h"



//-------------------------DEFINITION DES CONSTANTES-------------------




//-----------------------DECLARATION DES TYPES-------------------------

/*
* Cet enregistrement retient la catégorie (perceuse, scie, ...),
* l'emplacement (chambre, cuisine, ...), l'amperage et la tension
* d'un appareil.
*/

typedef struct{

	//Chaine de caractères
	t_chaine categorie;

	//Chaine de caractères
	t_chaine emplacement;

	//Amperage de l'appareil en amperes
	double ampere;

	//Tension d'utilisation de l'appareil, 
	//TENSION_PHASE ou TENSION_ENTREE
	double tension;

}t_appareil;





//-----------PROTOTYPES DES SOUS-PROGRAMMES PROPRES AU T_APPAREIL----------

/*Retourne la référence d'un nouveau appareil apres avoir alloué dynamiquement
* son espace mémoire et 'avoir rempli avec les données fournies
*/
t_appareil* nouvel_appareil(t_chaine categorie, t_chaine emplacement,
	double ampere, double tension);


/*Retourne TRUE ou FALSE selon si appareil_1 et appareil_2 sont identiques ou non*/
int appareils_sont_pareils(const t_appareil* appareil_1, const t_appareil* appareil_2);



#endif