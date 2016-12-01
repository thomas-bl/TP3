#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "types_et_constantes_globaux.h"

// Retourne la valeur r�elle en cha�ne de caract�res.
char* double_a_chaine(double valeur){

    /*
    * On utilise sprintf, ce qui facilite le travail de conversion.
    * On pr�sume la valeur comme un r�el valide.
    */
    char* msg = (char*)calloc(TAILLE_MSG, sizeof(char));

    // Si la conversion n'est pas possible, on retourne NULL
    if (!sprintf(msg, "%4.2lf", valeur)){
        free(msg);
        msg = NULL;
    }

    return msg;
}

// Convertit un char en char*.
char* car_a_chaine (char c) {

    /*
    * Le d�tail sera expliqu� en classe.
    */
    char* s = (char*) calloc(2,sizeof(char));
    s[0] = c;
    return s;           
}
