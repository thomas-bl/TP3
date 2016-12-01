#include <stdlib.h>
#include "t_appareil.h"


t_appareil* nouvel_appareil(t_chaine categorie, t_chaine emplacement,
	double ampere, double tension) {

	t_appareil* appareil = (t_appareil*)malloc(sizeof(t_appareil));

	appareil->ampere = ampere;
	strcpy(appareil->categorie,categorie);
	strcpy(appareil->emplacement,emplacement);
	appareil->tension = tension;

	return appareil;
}




int appareils_sont_pareils(const t_appareil* appareil_1, const t_appareil* appareil_2) {

	return (appareil_1 == appareil_2);
}


