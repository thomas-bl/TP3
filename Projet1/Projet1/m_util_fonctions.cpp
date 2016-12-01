#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "types_et_constantes_globaux.h"

// Retourne la valeur réelle en chaîne de caractères.
char* double_a_chaine(double valeur){

    /*
    * On utilise sprintf, ce qui facilite le travail de conversion.
    * On présume la valeur comme un réel valide.
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
    * Le détail sera expliqué en classe.
    */
    char* s = (char*) calloc(2,sizeof(char));
    s[0] = c;
    return s;           
}
