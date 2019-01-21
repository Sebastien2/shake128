#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <limits.h>


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


#define TEST 0











void main(int argc, char ** argv)
{
	if(argc!=3)
	{
		printf("Incorrect number of arguments, it is %d\n", argc);
		return;
	}

	char * nameFile=argv[2];
	if(TEST)
	{
		printf("Nom du fichier: %s\n", nameFile);
	}

	FILE * file=fopen(nameFile, "rb");

	fseek(file, 0, SEEK_END);
	int stringLen=ftell(file);

	//int b=8*stringLen+4;  //Pour avoir un bit sur chaque element, plus 4 bits a la fin pour shale 128
	int b=stringLen;

	if(TEST)
	{
		printf("%d\n", b);
	}


	char contenu[b];
	char t;
	fseek(file, 0, SEEK_SET);

	for(int i=0; i<b; i++)
	{
		contenu[i]=fgetc(file);
	}






	if(TEST)
	{
		for(int i=0; i<b; i++)
		{
			printf("%c ", contenu[i]);
		}
	}

	int w=b/25;
	int l=(int)(log(w)/log(2));

	if(TEST)
	{
		printf("l:%d w:%d\n", l, w);
	}

	//Puis le state
	char state[5][5][w];
	fillStateFromString(w, state, contenu, b, l);
	if(TEST)
	{
		afficherState(w, state);
	}

	fclose(file);



	//On prend c
	char *p;
	int num;
	int err= 0;
	int conv = strtol(argv[1], &p, 10);

	// Check for errors: e.g., the string does not represent an integer
	// or the integer is larger than int
	if (err!= 0 || *p != '\0' || conv > INT_MAX)
	{
	    // Put here the handling of the error, like exiting the program with
	    // an error message
			printf("Argument 1 (valeur de c) incompris essayer d'entrer un nombre cette fois-ci... tant qu'a faire inferieur a 1600 (mieux: inferieur a 1500)");
			return;
	}
	else
	{
	    // No error
	    num = conv;
	    //printf("c vaut %d\n", num);
	}

	int d=8*num;


	//Pour avoir shake128
	int c=256;
	char sortie[d];
	/*
	b=5;
	contenu[0]=1;
	contenu[1]=1;
	contenu[0]=0;
	contenu[0]=0;
	contenu[1]=1;
	shake128Bits(b, contenu, c, sortie, d);
	*/
	shake128(b, contenu, c, sortie, d);
	printf("Message a signer:\n");
	for(int i=0; i<b; i++)
	{
		printf("%c", contenu[i]);
	}
	printf("\n");
	printf("Signature shake128 en hexadecimal:\n");
	afficherBinaryInHex(d, sortie);
	printf("\n");














	//---------------------------------------
	//Anciens test
	/*
	int r;
	for(int i=0; i<100; i++)
	{
		r=rc(i);
		printf("rc(%d): %d\n", i, r);
	}
	*/

	/*
	char Aprime[5][5][w];
	int nr=24;
	int ir=12+2*l-nr;
	fillStateFromString(w, state, contenu, b, l);
	roundStep( w, state, Aprime,  ir,  l);
	fillStringFromState( w, Aprime, sortie,  b,  l);
	*/

	//keccakp( b, contenu, 24, sortie);


	//Shapke128
	/*
	int d=512; //Taille de la sortie

	keccak( c,  b,  d, contenu, sortie);
	printf("Shake128 avec c=%d et d=%d vaut:\n", c, d);
	for(int i=0; i<d; i++)
	{
		//printf("Numero %d: %02x\n", i, (unsigned int)(sortie[i] & 0xFF));
		printf("%02x",  (unsigned int)(sortie[i] & 0xFF));
	}
	printf("\n");

	*/

	/*
	char test[1600];
	char sortie2[1600];
	for(int i=0; i<1600; i++)
	{
		test[i]=0;
	}
	char caracString[200];
	creerStringFromHexString(599, contenu, caracString);
	creerBitsFromString(200, caracString, test);
	keccakf(1600, test, sortie2);

	//Puis on reconstruit le string
	char sortie3[200];
	creerStringFromBits(1600, sortie2, 200, sortie3);
	afficherStringEnHex(200, sortie3);
	*/



}
