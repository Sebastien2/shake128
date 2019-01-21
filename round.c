#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifndef AFFICHAGE
	#define AFFICHAGE "affichage.h"
	#include AFFICHAGE
#endif
#ifndef CONVERSION
	#define CONVERSION "conversion.h"
	#include CONVERSION
#endif
#ifndef KECCAKP
	#define KECCAKP "keccakp.h"
	#include KECCAKP
#endif
#ifndef ROUND
	#define ROUND "round.h"
	#include ROUND
#endif
#ifndef SPONGE
	#define SPONGE "sponge.h"
	#include SPONGE
#endif
#ifndef STEPMAPPINGS
	#define STEPMAPPINGS "stepMappings.h"
	#include STEPMAPPINGS
#endif
#ifndef KECCAK
	#define KECCAK "keccak.h"
	#include KECCAK
#endif





void roundStep(int w, char A[5][5][w], char Aprime[5][5][w], int ir, int l)
{
	theta( w, A, Aprime);
	copier(w, A, Aprime);
	rho(w, A, Aprime);
	copier(w, A, Aprime);
	pi(w, A, Aprime);
	copier(w, A, Aprime);
	chi(w, A, Aprime);
	copier(w, A, Aprime);
	iota(w, A, Aprime, ir, l);
}


void roundStepTest(int w, char A[5][5][w], char Aprime[5][5][w], int ir, int l)
{
	printf("Entree:\n");
	afficherStateHex(w, A);
	theta( w, A, Aprime);
	copier(w, A, Aprime);
	printf("After theta:\n");
	afficherStateHex(w, A);
	rho(w, A, Aprime);
	copier(w, A, Aprime);
	printf("After rho:\n");
	afficherStateHex(w, A);
	pi(w, A, Aprime);
	copier(w, A, Aprime);
	printf("After pi:\n");
	afficherStateHex(w, A);
	chi(w, A, Aprime);
	copier(w, A, Aprime);
	printf("After chi:\n");
	afficherStateHex(w, A);
	iota(w, A, Aprime, ir, l);
	copier(w, A, Aprime);
	printf("After iota:\n");
	afficherStateHex(w, A);
}



void copier(int w, char A[5][5][w], char Aprime[5][5][w])
{
	for(int x=0; x<5; x++)
	{
		for(int y=0; y<5; y++)
		{
			for(int z=0; z<w; z++)
			{
				A[x][y][z]=Aprime[x][y][z];
			}
		}
	}
}
