/*
* Module qui permet la gestion d'une boîte électrique
* avec disjoncteurs.
*
* La boite doit d'abord être initialisée au nombre de Ampère voulu.
*
* Le projet ne contient qu'une seule boîte.  Tous les sous- 
* programmes public (.h) agissent sur la même boîte.
*/
#include "t_boite.h"
#include "winBGIm.h"
#include "mtwister.h"

// Ajouter les SP manauqants.

// Retourne l'adresse d'une boite neuve, avec toutes les cases disjoncteurs
// sur NULL
t_boite* obtenir_boite_neuve(int amperage){
	//itérateurs
	int L;
	int C;
	t_boite* ma_boite = (t_boite*)malloc(sizeof(t_boite));

	ma_boite->nb_amperes = amperage;

	for(L=0; L<NB_LIGNES_MAX; L++){
		for(C=0; C<NB_COLONNES; C++){
			ma_boite->tab_disjoncteurs[L][C] = NULL;
		}
	}

	return ma_boite;
}


//Retourne la puissance totale sur les disjoncteurs.
double puissance_total_boite(const t_boite* boite){

	double  total = 0;
	//itérateurs pour parcourir le tableau de disjoncteurs
	int l;
	int c;

	for (l = 0; l < NB_LIGNES_MAX; l++) {
		for (c = 0; c < NB_COLONNES; c++) {
			total += puissance_max(boite->tab_disjoncteurs[l][c]);
		}
	}

	return total;
}


//Retourne la consommation totale de la boîte
double consommation_totale(const t_boite* boite){

	double  total = 0;
	//itérateurs pour parcourir le tableau de disjoncteurs
	int l;
	int c;

	for (l = 0; l<NB_LIGNES_MAX; l++) {
		for (c = 0; c<NB_COLONNES; c++) {
			//test pour ne pas aller dans une case sans disjoncteur
			if (boite->tab_disjoncteurs[l][c]) {
				//ajout de la puissance
				total += boite->tab_disjoncteurs[l][c]->demande_du_circuit
					* boite->tab_disjoncteurs[l][c]->tension;
			}
		}
	}

	return total;
}


// Retourne le temps de support de la charge.
double temps_ups(const t_boite* boite){
	
	double conso_totale = consommation_totale(boite)/TENSION_ENTREE; 
	return ((conso_totale) ? (boite->nb_amperes/(conso_totale)) : NULL);
}


// Retourne le nombre de disjoncteurs actuellement dans la boite.
int nb_disjoncteurs_actuel(const t_boite* boite){

	return nb_disjoncteurs_tension(boite,TENSION_ENTREE) 
		+ nb_disjoncteurs_tension(boite, TENSION_PHASE);
}


// Retourne le nombre de disjoncteurs de la tension fournie 
// actuellement dans la boite.
int nb_disjoncteurs_tension(const t_boite* boite, int tension){
	int i = 0;
	int j = 0;
	int nb = 0;
	for (j=0;j<NB_COLONNES;j++){
		for (i=0; i<NB_LIGNES_MAX;i++){
			if (boite->tab_disjoncteurs[i][j] != NULL && boite->tab_disjoncteurs[i][j]->tension == tension){
				nb++ ;
			}
		}
	}

    return nb;
}


// Retourne le ratio d'utilisation de la puissance du circuit, en %
double ratio_utilisation(const t_boite* boite){
	
	return ((puissance_total_boite(boite))/(TENSION_ENTREE*boite->nb_amperes)) *100;
}





// Retourne le disjoncteur qui se trouve aux coordonnées reçues.
t_disjoncteur* obtenir_disjoncteur(const t_boite* boite,
	const t_coord* coord) {

	return boite->tab_disjoncteurs[coord->lig][coord->col];
}



//sous programme qui retire le disjoncteur aux coordonnées passées en argument
void retirer_un_disjoncteur(t_boite* boite, t_coord* coor) {
	/*Stratégie :  */


	boite->tab_disjoncteurs
}