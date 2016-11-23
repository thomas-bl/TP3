
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




#include "mtwister.h"


/*==========================================================*/
/* 
   l'utilisation du type long par les auteurs avait une importance
   historique lorsque les entiers de base(int) pouvaient encore avoir une 
   représentation à 16 bits, le long nous assurait de 32 bits (ce 
   que les auteurs considèrent normal, puisque c'est le format 
   qu'ils décrivent partout) et c'est 32 bits qu'on obtient maintenant 
   sur tout compilateur moderne avec un int.

   l'utilisation du modificateur unsigned  par les auteurs 
   fait partie des choixs offerts au client. Les auteurs auraient bien
   pu passer sous silence et tout dans l'interface serait en int.
   
	Encore par souci d'élargir l'interface, les auteurs offrent toutes 
	les 4 formes d'uniformes réelles entre 0 et 1 :
		(0,1) intervalle ouvert --sans 0 ni 1 --
		[0,1) intervalle ouvert à droite -- avec 0 mais sans 1 --
		(0,1] intervalle ouvert à gauche -- sans 0 mais avec 1 --
		[0,1] intervalle fermé  -- avec 0 et avec 1 --

  */

/*
	Je n'ai ajouté qu'une présentation minimale en francais aux fonctions originales
	offertes sans rien  y changer + quelques observations pour nos étudiants
	Le commentaire en présentation des déclarations originales de fonctions 
	ne suit pas le modèle donné dans le cours....

	la présentation est vraiment 'limitée' mais c'est souvent ainsi qu'on offre
	du code interressant.

/*==========================================================*/
/*	Deux formes d'init possibles.
	Vous pouvez ne pas vous préoccuper du unsigned long 
	en paramètre formel et donner un int ou un tableau 
	de int (En assumant alors le warning possible)
*/
/*==========================================================*/

/* initializes mersenne twister 
   pseudo-random number generator with a seed */

/* initialisation à partir d'un entier quelconque */
/* la séquence pseudo aléatoire sera totalement déterminée*/

void mt_init_genrand(unsigned long s);
/*==========================================================*/


/*	initialize by an array with array-length
	init_key is the array for initializing keys
	key_length is its length
	slight change for C++, 2004/2/26
	idem in ANSI C
*/
/* variante de la précédente mais ici,
  donnez- lui un tableau  d'entiers et la taille du tableau */

void mt_init_by_array(const unsigned long init_key[], int key_length);
/*==========================================================*/

/* generates a random number on [0,0xffffffff]-interval*/
/* Pour obtenir un entier sur 32 bits pseudo-aléatoires */
unsigned long mt_genrand_int32(void);

/*==========================================================*/
/* generates a random number on [0,0x7fffffff]-interval*/
/* Pour obtenir un entier sur 31 bits pseudo-aléatoires */
/* Vous êtes simplement assuré qu'il ne sera pas négatif */
/* si on récupère dans un int à 32 bits*/
long mt_genrand_int31(void);

/*==========================================================*/

/*==========================================================*/

/* These real versions are due to Isaku Wada, 2002/01/09 added */

/* et les quatre uniformes dans l'intervalle 0,1 */
/* simplement différenciées par le suffixe 1,2,3,53*/
/* PAS très fort comme représentativité ...... */
/* mais l'âme japonaise souffre surement des mêmes maux que la notre!*/

/* generates a random number on [0,1]-real-interval*/
double mt_genrand_real1(void);

/* generates a random number on [0,1)-real-interval*/
double mt_genrand_real2(void);

/* generates a random number on (0,1)-real-interval*/
double mt_genrand_real3(void);

/* generates a random number on [0,1) with 53-bit resolution*/
double mt_genrand_res53(void);
// Period parameters
//
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL		// constant vector a
#define UPPER_MASK 0x80000000UL		// most significant w-r bits
#define LOWER_MASK 0x7fffffffUL		// least significant r bits


static unsigned long mt[N];		// the array for the state vector
static int mti=N+1;				// mti==N+1 means mt[N] is not initialized



// initializes mt[N] with a seed
//
void mt_init_genrand(unsigned long s)
{
	mt[0]= s & 0xffffffffUL;
	for (mti=1; mti<N; mti++)
	{
		mt[mti] = (1812433253UL * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti);
		// See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier.
		// In the previous versions, MSBs of the seed affect
		// only MSBs of the array mt[].
		// 2002/01/09 modified by Makoto Matsumoto

		mt[mti] &= 0xffffffffUL;	// for >32 bit machines
	}
}



// initialize by an array with array-length
// init_key is the array for initializing keys
// key_length is its length
// slight change for C++, 2004/2/26
//
void mt_init_by_array(const unsigned long init_key[], int key_length)
{
	int i, j, k;
	mt_init_genrand(19650218UL);
	i=1;
	j=0;
	k = (N>key_length ? N : key_length);
	for (; k; k--)
	{
		mt[i] =	(mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1664525UL))
				+ init_key[j] + j;	// non linear
		mt[i] &= 0xffffffffUL;	// for WORDSIZE > 32 machines
		i++;
		j++;
		if (i>=N)
		{
			mt[0] = mt[N-1];
			i=1;
		}
		if (j>=key_length)
		j=0;
	}
	for (k=N-1; k; k--)
	{
		mt[i] =	(mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1566083941UL))
				- i;			// non linear
		mt[i] &= 0xffffffffUL;	// for WORDSIZE > 32 machines
		i++;
		if (i>=N)
		{
			mt[0] = mt[N-1];
			i=1;
		}
	}

	mt[0] = 0x80000000UL;	// MSB is 1; assuring non-zero initial array
}



// generates a random number on [0,0xffffffff]-interval
//
unsigned long mt_genrand_int32(void)
{
	unsigned long y;
	static unsigned long mag01[2]={0x0UL, MATRIX_A};
	// mag01[x] = x * MATRIX_A  for x=0,1

	if (mti >= N)	 // generate N words at one time
	{
		int kk;

		if (mti == N+1)				// if init_genrand() has not been called,
			mt_init_genrand(5489UL);	// a default initial seed is used

		for (kk=0;kk<N-M;kk++)
		{
			y = (mt[kk] & UPPER_MASK) | (mt[kk+1] & LOWER_MASK);
			mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
		}
		for (;kk<N-1;kk++)
		{
			y = (mt[kk] & UPPER_MASK) | (mt[kk+1] & LOWER_MASK);
			mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
		}
		y = (mt[N-1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
		mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

		mti = 0;
	}

	y = mt[mti++];

	// Tempering
	y ^= (y >> 11);
	y ^= (y << 7) & 0x9d2c5680UL;
	y ^= (y << 15) & 0xefc60000UL;
	y ^= (y >> 18);

	return y;
}



// generates a random number on [0,0x7fffffff]-interval
//
long mt_genrand_int31(void)
{
	return (long)(mt_genrand_int32()>>1);
}



// These real versions are due to Isaku Wada, 2002/01/09 added
//

// generates a random number on [0,1]-real-interval
//
double mt_genrand_real1(void)
{
	return mt_genrand_int32()*(1.0/4294967295.0); 
	// divided by 2^32-1
}



// generates a random number on [0,1[-real-interval
//
double mt_genrand_real2(void)
{
	return mt_genrand_int32()*(1.0/4294967296.0); 
	// divided by 2^32
}



// generates a random number on ]0,1[-real-interval
double mt_genrand_real3(void)
{
	return (((double)mt_genrand_int32()) + 0.5)*(1.0/4294967296.0); 
	// divided by 2^32
}



// generates a random number on [0,1[ with 53-bit resolution
//
double mt_genrand_res53(void) 
{ 
	unsigned long a=mt_genrand_int32()>>5, b=mt_genrand_int32()>>6; 
	return(a*67108864.0+b)*(1.0/9007199254740992.0); 
}

/*==========================================================*/

/* implémentation des 7 fonctions ajoutées pour nos étudiants */
/*==========================================================*/

void mt_srand(unsigned long s){
	mt_init_genrand(s);
}
/*==========================================================*/

unsigned long mt_srandSys(void){	
	unsigned long v ;
	v = time(NULL);
	mt_init_genrand(v);
	return v;
}
/*==========================================================*/

double mt_rand(void){
	return mt_genrand_real1();
}
/*==========================================================*/

double mt_randf(double b1, double b2){
	return b1 + (mt_genrand_real1()*(b2-b1));
}
/*==========================================================*/

int mt_randi(int borne){
	borne = abs(borne);
	return (int)(1 + mt_genrand_real3()* borne);
}
/*==========================================================*/

/* obtenu naivement de la somme de 12 uniforme 0,1 */
double mt_randz(void){
	double r=0;
	int i=0;
	for( ; i<12; ++i) r += mt_genrand_real1();
	return (r-6.0);
}
/*==========================================================*/
double mt_randnormal(double mu, double sigma){
	return mu+mt_randz()*sigma ;
}
/*==========================================================*/


