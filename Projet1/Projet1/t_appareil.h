/*
* Module de type qui regroupe tout dans le projet qui concerne un
* appareil.
*
* On y retrouve les constantes, d�finition de type et sous-programme
* li� � un appareil.
*/

#ifndef __T_APPAREIL__
#define __T_APPAREIL__

//contient toutes les constantes utiles
#include "types_et_constantes_globaux.h"
#include <string.h>


//-------------------------DEFINITION DES CONSTANTES-------------------




//-----------------------DECLARATION DES TYPES-------------------------

/*
* Cet enregistrement retient la cat�gorie (perceuse, scie, ...),
* l'emplacement (chambre, cuisine, ...), l'amperage et la tension
* d'un appareil.
*/

typedef struct{

	//Chaine de caract�res
	t_chaine categorie;

	//Chaine de caract�res
	t_chaine emplacement;

	//Amperage de l'appareil en amperes
	double ampere;

	//Tension d'utilisation de l'appareil, 
	//TENSION_PHASE ou TENSION_ENTREE
	double tension;

}t_appareil;





//-----------PROTOTYPES DES SOUS-PROGRAMMES PROPRES AU T_APPAREIL----------

/*Retourne la r�f�rence d'un nouveau appareil apres avoir allou� dynamiquement
* son espace m�moire et 'avoir rempli avec les donn�es fournies
*/
t_appareil* nouvel_appareil(t_chaine categorie, t_chaine emplacement,
	double ampere, double tension);


/*Retourne TRUE ou FALSE selon si appareil_1 et appareil_2 sont identiques ou non*/
int appareils_sont_pareils(const t_appareil* appareil_1, const t_appareil* appareil_2);



#endif