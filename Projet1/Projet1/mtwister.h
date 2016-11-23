/*==========================================================*/

/*
	le module offrant un mersenne twister, un générateur de nombres 
	pseudo-aléatoires considéré comme le meilleur pour la simulation numérique

	Une courte présentation francaise suit l'introduction en anglais des auteurs japonais
	et donnera le caractère général de chaque  fonction offerte

   Les 2 auteurs n'offraient originallement que des mtwister uniformes 
   qui peuvaient parfois paraitre redondantes. Pour un professionnel qui sait
   construire des mtwister différentes de l'uniforme, ça va
   mais j'ai choisi d'ajouter pour les étudiants quelques fonctions standardisées 
   permettant d'obtenir des évènements dans une distribution :

		uniforme générale , sans ou avec des bornes, entière ou réelle
		normale centrée réduite Z(0,1) ou normale à moyenne et écart-type définis
*/

/*==========================================================*/
/* Le module offre donc sept fonctions :

	deux fonctions capables d'initialiser le générateur 
	1 - void mt_srand(unsigned long s);
	2 - unsigned long mt_srandSys(void);

	deux fonctions pour émettre un nombre réel dans une uniforme
	double mt_rand(void);
	double mt_randf(double b1, double b2);

	une fonction pour émettre un nombre entier dans une uniforme
	int mt_randi(int borne);

	deux fonctions pour émettre un réel dans une distribution normale
	double mt_randz(void);
	double mt_randnormal(double mu, double sigma);

*/
/*==========================================================*/


/*==========================================================*/

/* 
   A C-program for MT19937, with initialization improved 2002/1/26.
   Coded by Takuji Nishimura and Makoto Matsumoto.

   Before using, initialize the state by using init_genrand(seed)  
   or init_by_array(init_key, key_length).

   Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
   All rights reserved.                          

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

     1. Remtwister of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.

     2. Remtwister in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

     3. The names of its contributors may not be used to endorse or promote 
        products derived from this software without specific prior written 
        permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


   Any feedback is very welcome.
   http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
   email: m-mat @ math.sci.hiroshima-u.ac.jp (remove space)
*/

/*==========================================================*/

#ifndef _MT19937AR_H_
#define _MT19937AR_H_
/*==========================================================*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>


/*==========================================================*/

/* UNE INTERFACE MODULAIRE STANDARD POUR MES ÉTUDIANTS */

/*==========================================================*/

/*  Voici deux fonctions d'initialisation du
     générateur. Un générateur non-initialisé s'initialise 
     en fait à 0 et émet la même séquence ce qui fait douter
	 du caractère aléatoire.... C'est au client de l'initialiser
	 MAIS JUSTE UNE FOIS dans tout le programme de simulation.
*/

/*==========================================================*/
/* La fonction mt_srand 
 la forme d'initialisation la plus classique d'un générateur  
 à partir d'un entier quelconque, la séquence pseudo aléatoire 
 à venir est totalement déterminée par la valeur reçue 

PARAMETRE(s): s, un entier quelconque

SORTIE: aucune

SPECS: aucune
*/
void mt_srand(unsigned long s);

/*==========================================================*/


/*==========================================================*/
/* la fonction mt_srandSys 
 une forme alternative d'initialisation du générateur à partir 
 de l'horloge interne de la machine,  l'horloge donne un entier
 qui sert de paramètre à la fonction précédente. 
 Cette valeur est retournée 

PARAMETRE(s): Aucun

SORTIE: l'entier qui a véritablement initialisé le générateur

SPECS: aucune
*/
unsigned long mt_srandSys(void);
/*==========================================================*/

/* LES CINQ FONCTIONS D'ÉMISSION DANS LES mtwister SPÉCIFIÉES */

/*==========================================================*/
/* La fonction mt_rand   
L'émission d'un nombre réel dans la distribution uniforme 0,1 

PARAMETRE(s): Aucun

SORTIE : la valeur émise par le générateur

SPECS : aucune
*/
double mt_rand(void);
/*==========================================================*/

/*==========================================================*/
/* La fonction mt_randf

L'émission d'un nombre réel dans une  uniforme [b1, b2] 

PARAMETRE(s): deux valeurs réelles quelconques qui serviront 
               de bornes à l'intervalle

SORTIE : la valeur émise par le générateur

SPECS : l'ordre des paramètres n'a aucune importance
*/
double mt_randf(double b1, double b2);
/*==========================================================*/

/*==========================================================*/
/* La fonction mt_randi

L'émission d'un nombre entier positif dans une uniforme [1, borne]

PARAMETRE(s): une valeur entière quelconque

SORTIE : la valeur entière émise par le générateur

SPECS :  si le paramètre effectif < 0 , c'est la valeur absolue 
			du paramètre  qui sera considérée
         recevant 0 elle retourne automatiquement 0 et 
			c'est le seul 0 possible
*/
int mt_randi(int borne);
/*==========================================================*/

/*==========================================================*/
/* La fonction mt_randz

L'émission d'un nombre réel dans la distribution normale Z, 
la plus classique  de moyenne 0 et d'écart type 1

PARAMETRE(s) : Aucun

SORTIE : la valeur réelle émise par le générateur

SPECS : aucune
*/
double mt_randz(void);
/*==========================================================*/

/*==========================================================*/
/* La fonction mt_randnormal

L'émission d'un nombre réel dans une distribution normale quelconque, 
  de moyenne mu  et d'écart-type sigma donnés

PARAMETRE(s) : mu définit la moyenne voulue et sigma l'écart-type

SORTIE : la valeur réelle émise par le générateur

SPECS : le signe de sigma n'aura pas d'importance.
*/
double mt_randnormal(double mu, double sigma);

/*==========================================================*/
/*==========================================================*/

/* L'INTERFACE ORIGINALE DES DEUX CRÉATEURS SERA DANS LE .C 	*/

/*==========================================================*/
#endif	
/*==========================================================*/

