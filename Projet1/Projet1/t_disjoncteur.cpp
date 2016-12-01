//SEB

#include "t_disjoncteur.h"
#include <stdlib.h>

// Retourne un disjoncteur créer en allocation dynamique et initialisé.
t_disjoncteur* nouveau_disjoncteur(int ampere, int tension) {

	t_disjoncteur* nouveau_disjoncteur = (t_disjoncteur*)malloc(sizeof(t_disjoncteur));

	nouveau_disjoncteur->ampere = ampere;

	nouveau_disjoncteur->tension = tension;

	nouveau_disjoncteur->demande_du_circuit = 0;

	tester_etat_disjoncteur(nouveau_disjoncteur);

	init_liste(nouveau_disjoncteur->ref_appareils, MAX_APPAREILS);

	return nouveau_disjoncteur;
}


// Retourne la puissance maximum possible pour ce disjoncteur.
int puissance_max(const t_disjoncteur* disjoncteur){

	return (disjoncteur->tension*disjoncteur->ampere*COEFF_PUISSANCE);
}


// Change l'état du disjoncteur à sa bonne valeur
void tester_etat_disjoncteur(t_disjoncteur* disjoncteur)
{
	disjoncteur->etat = 
		((disjoncteur->demande_du_circuit) < disjoncteur->ampere) ? 
		ALLUME : ETEINT;
}



/*Calcule la demande totale en ampères de tous les appareils branchés 
* sur un disjoncteur, et met le résultat dans disjoncteur.demande_du_circuit
*/
void calculer_demande_totale(t_disjoncteur* disjoncteur) {
	
	if (!liste_est_vide(disjoncteur->ref_appareils)) {

		do {

			disjoncteur->demande_du_circuit += lire_appareil(disjoncteur->ref_appareils).ampere;

		}while (!pc_a_la_fin(disjoncteur->ref_appareils));		

		disjoncteur->demande_du_circuit += lire_appareil(disjoncteur->ref_appareils).ampere;

	}	
}




//sous programme qui lit un élément dans la liste, le convertit en appareil
//et met la position courante à la case suivante
static t_appareil lire_appareil(t_liste* liste) {


	//permet d'aller lire un élément de la liste
	t_element* element;
	

	//Lecture de l'élément à la position courante
	obtenir_element(liste, element);

	//incrémentation de la position
	set_pc_suivant(liste);

	//conversion de l'élément en t_appareil*
	return *((t_appareil*)element);
}




/*permet d'ajouter un appareil dans la liste d'appareils
* nécessite de fournir toutes les caractéristiques de l'appareil
* 
* s'occupe aussi d'actualiser la consommation sur le disjoncteur
* ET son état
*/

void ajouter_appareil(t_disjoncteur* disjoncteur, 
	t_appareil* appareil) {

	/*Stratégie : 
	* On appelle le sous-programme de création d'un appareil avec les 
	* bons paramètres, puis on l'insère dans la liste d'appareils
	* à la position courante.
	* 
	* On actualise ensuite les champs du disjoncteur
	*/
	
		double ampere =appareil->ampere;

		double tension = appareil->tension;
		t_chaine categorie;
		t_chaine emplacement;
		strcpy(categorie,appareil->categorie);
		strcpy(emplacement,appareil->emplacement);
		
		if (tension == disjoncteur->tension) {

		//création et insertion du disjoncteur dans la liste
		inserer(disjoncteur->ref_appareils,
			nouvel_appareil(categorie, emplacement, ampere, tension));

		//actualisation de la demande totale
		calculer_demande_totale(disjoncteur);

		//actualisation de l'état du disjoncteur
		tester_etat_disjoncteur(disjoncteur);
	}
}



/*permet de retirer un appareil dans la liste d'appareils
* nécessite de fournir toutes les caractéristiques de l'appareil
*
* s'occupe aussi d'actualiser la consommation sur le disjoncteur
* ET son état
*/

///////////////////////////////////////////////////////////MODIFIE/////////////////////////////////////////////////////

void retirer_un_appareil(t_disjoncteur* disjoncteur,
	t_appareil* appareil_retire) {

	/*Stratégie :
	* On recherche l'appareil à retirer en comparant les enregistrements
	* avec les appareils de la liste
	* on retire le bon appareil
	*/

	t_element* element;

	set_pc_debut(disjoncteur->ref_appareils);


	while (!pc_a_la_fin(disjoncteur->ref_appareils)) {

		//Lecture de l'élément à la position courante en vue de le comparer
		obtenir_element(disjoncteur->ref_appareils, element);

		//test si c'est l'élément qu'on veut supprimer
		if (appareils_sont_pareils(appareil_retire,
			(t_appareil*)element)) {

			//suppression de l'appareil à la position courante (encapsulation)
			supprimer(disjoncteur->ref_appareils);

			//actualisation de la demande totale
			calculer_demande_totale(disjoncteur);

			//actualisation de l'état du disjoncteur
			tester_etat_disjoncteur(disjoncteur);
		}

		//Si les appareils n'étaient pas pareils, on place déplace pc pour aller 
		//lire l'appareil suivant
		else {
			set_pc_suivant(disjoncteur->ref_appareils);
		}
	}

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////
//SP SEB
///////////////////////////////////////////////////////////////////////////////////////////


//retourne un tableau contenant les references des appareil d'un disjoncteur 
//(rf 6.2)
t_appareil** obtenir_appareils(t_disjoncteur* disjoncteur,int* nb_appareils){

	assert(disjoncteur->ref_appareils!=0);

	t_element* tmp;
	int taille = obtenir_nb_elements(disjoncteur->ref_appareils);
	
	int i; 
	
	t_appareil** tableau =(t_appareil**) malloc(sizeof(t_appareil*)*taille);
	
	set_pc_debut(disjoncteur->ref_appareils);
	
	for(i=0;taille>i;i++){
		obtenir_element(disjoncteur->ref_appareils,tmp);
		tableau[i] = (t_appareil*)tmp;
		set_pc_suivant(disjoncteur->ref_appareils);
		i++;
	}
	*nb_appareils = taille;

	return tableau;
}


//vide un disjoncteur de ses appareils
//(rf 6.3)
void* vider_appareil(t_disjoncteur* disjoncteur){
//Met null à chaque élément de l'appareil. ATTENTION, ça ne libère pas la mémoire.
	disjoncteur->ref_appareils->fin = 0;
	disjoncteur->ref_appareils->pc = 0;
	disjoncteur->ref_appareils->tab_donnees = 0;
	disjoncteur->ref_appareils->taille = 0;

	return EXIT_SUCCESS;
}

