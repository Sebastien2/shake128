#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
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

#ifndef COLLISIONN
	#define COLLISIONN "collisionN.h"
	#include COLLISIONN
#endif

#ifndef TEST
  #define TEST 1
#endif
#ifndef TESTENTREE
	#define TESTENTREE 0
#endif



void copierBits(int len, char * original, char * copie)
{
  for(int i=0; i<len; i++)
  {
    copie[i]=original[i];
  }
}

int equalBits(int len, char * A1, char * A2)
{
  int res=1;
  for(int i=0; i<len; i++)
  {
    if(A1[i]!=A2[i])
    {
      res=0;
    }
  }
  return res;
}




void enregistrerFichiers(char * preimage1, char * preimage2, int d, int numero, int N)
{
	if(TEST)
	{
		printf("N: %d\n", N);
	}
	char temp;
	char texte[N];
	FILE * file;
	int nbCaracN=(double)(log(N)/log(10))+1;
	int nbCaracNumero=(double)(log(numero)/log(10))+1;
	if(TEST)
	{
		printf("Taille des nombres %d %d : %d %d\n", N, numero, nbCaracN, nbCaracNumero);
	}

	int longueurNomFichier=nbCaracN+nbCaracNumero+19;
	char fileName[longueurNomFichier];

	sprintf(fileName, "collisions-%d/ex-%d.A", N, numero);
	if(TEST)
	{
		printf("Nom du fichier: %s\n", fileName);
	}

	file=fopen(fileName, "wb");
	if(file!=NULL)
	{
		creerStringFromBits(8*N, preimage1, N, texte);
		if(TEST)
		{
			printf("Ce qui va etre ecrit dans le fichier .A:\n");
			afficherStringEnHex(N, texte);
		}
		for(int i=0; i<N; i++)
		{
			fwrite(&(texte[i]), sizeof(char), 1, file);

		}
		fclose(file);
	}
	else
	{
		printf("Echec de la creation du fichier %s\n", fileName);
	}


	//Deuxieme fichier
	sprintf(fileName, "collisions-%d/ex-%d.B", N, numero);
	if(TEST)
	{
		printf("Nom du fichier: %s\n", fileName);
	}

	file=fopen(fileName, "wb");
	if(file!=NULL)
	{
		creerStringFromBits(8*N, preimage2, N, texte);
		if(TEST)
		{
			printf("Ce qui va etre ecrit dans le fichier .B:\n");
			afficherStringEnHex(N, texte);
		}
		for(int i=0; i<N; i++)
		{
			fwrite(&(texte[i]), sizeof(char), 1, file);

		}
		fclose(file);
	}
	else
	{
		printf("Echec de la creation du fichier %s\n", fileName);
	}


}







void rechercheFichiers(int N, int rec, int nbCollisions)
{
	char preimage1[8*N];
	char preimage2[8*N];
	char hash1[8*N];
	char hash2[8*N];

	//Hash table
	char hashTable[nbCollisions][2][8*N];
	for(int i=0; i<nbCollisions; i++)
	{
		for(int j=0; j<2; j++)
		{
			for(int k=0; k<8*N; k++)
			{
				hashTable[i][j][k]=0;
			}
		}
	}
	int nbCollisionsTrouvees=0;
	int compteur=0;

	int c=256;
	int d=8*N;
	while(compteur<rec && nbCollisionsTrouvees<nbCollisions)
	{
		if(TEST)
		{
			printf("-------------------\n---------------------\nTour n°%d\n\n", compteur);
		}
		recherche(N, preimage1, preimage2);
		shake128Bits(d, preimage1, c, hash1, d);
		shake128Bits(d, preimage2, c, hash2, d);
		if(equalBits(d, hash1, hash2)==1 && equalBits(d, preimage1, preimage2)==0)
		{
			//On a trouve une collision: veriins qu'on ne l'avait pas deja
			if(TEST)
			{
				printf("Egalite des hash validee\n");
			}

			int deja=0;
			for(int i=0; i<nbCollisionsTrouvees; i++)
			{
				if((equalBits(d, preimage1, hashTable[i][0])==1 && equalBits(d, preimage2, hashTable[i][1])==1) || (equalBits(d, preimage1, hashTable[i][1])==1 && equalBits(d, preimage2, hashTable[i][0])==1))
				{
					deja=1;
				}
			}
			if(deja==0)
			{
				if(TEST)
				{
					printf("Collision jamais vue\n");
				}

				//on n'a jamais vu cette collisionN
				for(int i=0; i<d; i++)
				{
					hashTable[nbCollisionsTrouvees][0][i]=preimage1[i];
					hashTable[nbCollisionsTrouvees][1][i]=preimage2[i];

				}
				nbCollisionsTrouvees+=1;

				//puis on cree les fichiers
				enregistrerFichiers(preimage1, preimage2, d, nbCollisionsTrouvees, N);
			}
			else
			{
				if(TEST)
				{
					printf("Collision deja vue\n");
				}

			}
		}
		else
		{
			if(TEST)
			{
				printf("ERREUR lors de la verification de collision\n");
			}

		}
		compteur+=1;
	}


}



void recherche(int N, char * preimage1, char * preimage2)
{
	if(TEST)
	{
		printf("Taille: %d\n", N);
	}
  //Etape 1: prendre une seed random
  char seed[N];
  char entree[8*N];
  char sortie[8*N];
  char entree1[8*N];
  char sortie1[8*N];
  char entree2[8*N];
  char sortie2[8*N];
	char stock1[8*N];
	char stock2[8*N];
	for(int i=0; i<8*N; i++)
	{
		entree[i]=0;
		sortie[i]=0;
		entree1[i]=0;
		sortie1[i]=0;
		entree2[i]=0;
		sortie2[i]=0;
		stock1[i]=0;
		stock2[i]=0;
	}
	int s=0;
  randomSeedPerso(N, seed);

  //We start iterating our research: we are only looking into files of same length as their hash (for iteration)
	/*
	seed[0]=0x55;
	seed[1]=0xdf;
	*/
  creerBitsFromString(N, seed, entree);


  if(TEST)
  {
    printf("Seed en binary:\n");
    afficherBinaryInHex(8*N, entree);
    printf("\n");
  }

  copierBits(8*N, entree, entree1);
  copierBits(8*N, entree, entree2);

	if(TEST)
  {
    printf("Entree1 en binary:\n");
    afficherBinaryInHex(8*N, entree1);
    printf("\n");
    printf("Entree2 en binary:\n");
    afficherBinaryInHex(8*N, entree2);
    printf("\n");
  }

  int d=8*N;
  int c=256;
  //int b=1600;
	if(TESTENTREE)
	{
		printf("entree1:\n");
		afficherBinaryInHex(d, entree1);
		printf("\n");
	}

	copierBits(d, entree1, stock1);

  shake128Bits(d, entree1, c, sortie1, d);
	if(TESTENTREE)
	{
		printf("sortie1:\n");
		afficherBinaryInHex(d, sortie1);
		printf("\n");
	  copierBits(d, sortie1, entree1);

		printf("\n\n---------------------\n\n");
	}


	if(TESTENTREE)
	{
		printf("entree2 etape 1:\n");
		afficherBinaryInHex(d, entree2);
		printf("\n");
	}

  shake128Bits(d, entree2, c, sortie2, d);
	if(TESTENTREE)
	{
		printf("sortie2 etape 1:\n");
		afficherBinaryInHex(d, sortie2);
		printf("\n");
	}

	copierBits(d, sortie2, entree2);

	copierBits(d, entree2, stock2);
	if(TESTENTREE)
	{
		printf("\n\n---------------------\n\n");

		printf("entree2 etape 2:\n");
		afficherBinaryInHex(d, entree2);
		printf("\n");
	}

  shake128Bits(d, entree2, c, sortie2, d);
	if(TESTENTREE)
	{
		printf("sortie2 etape 2:\n");
		afficherBinaryInHex(d, sortie2);
		printf("\n");

		printf("\n\n---------------------\n\n");
	}


  copierBits(d, sortie2, entree2);
  s+=1;

	//while(s<0)
  while(equalBits(d, entree1, entree2)==0 && s<INT_MAX)

	{
    if(s%50==0)
    {
      printf("Recherche en cours... s: %d\n", s);
			printf("Valeurs à comparer:\n");
			afficherBinaryInHex(d, entree1);
			printf("\n");
			afficherBinaryInHex(d, entree2);
	    printf("\n");
			printf("--------------\n");
    }

		copierBits(d, entree1, stock1);
    shake128Bits(d, entree1, c, sortie1, d);
    copierBits(d, sortie1, entree1);

    shake128Bits(d, entree2, c, sortie2, d);
    copierBits(d, sortie2, entree2);
		copierBits(d, entree2, stock2);
    shake128Bits(d, entree2, c, sortie2, d);
    copierBits(d, sortie2, entree2);

    s+=1;
  }

	if(TEST)
  {
    printf("On a obtenu deux images identiques.\n");
    printf("Index: %d\n", s);
		printf("Contenu 1: ");
		afficherBinaryInHex(d, entree1);
    printf("\n");
    printf("Contenu 2: ");
    afficherBinaryInHex(d, entree2);
    printf("\n");
	}





	//Puis deuxième étape
	if(TEST)
	{
		printf("--------------\nEtape 2\n-------------\n");
	}

	int t=0;
	copierBits(d, entree, entree1);
	copierBits(d, sortie2, entree2);
	shake128Bits(d, entree2, c, sortie2, d);
	copierBits(d, sortie2, entree2);
	shake128Bits(d, entree2, c, sortie2, d);
	copierBits(d, sortie2, entree2);


	if(TEST)
  {
    printf("Entree1 en binary:\n");
    afficherBinaryInHex(d, entree1);
    printf("\n");
    printf("Entree2 en binary:\n");
    afficherBinaryInHex(d, entree2);
    printf("\n");
  }
	while(equalBits(d, entree1, entree2)==0 && t<=s)
	{
		if(TEST)
		{
			if(t%50==0)
			{
				printf("Parcours en cours... t: %d\n", t);
				printf("Valeurs à comparer:\n");
				afficherBinaryInHex(d, entree1);
				printf("\n");
				afficherBinaryInHex(d, entree2);
		    printf("\n");
				printf("--------------\n");

			}
		}

		copierBits(d, entree1, stock1);
    shake128Bits(d, entree1, c, sortie1, d);
    copierBits(d, sortie1, entree1);

		copierBits(d, entree2, stock2);
    shake128Bits(d, entree2, c, sortie2, d);
    copierBits(d, sortie2, entree2);
		t+=1;
	}


  if(TEST)
  {
		if(equalBits(d, entree1, entree2)==1)
		{
			printf("On a trouve deux images identiques:\n");
	    printf("Index: %d\n", t);
	    printf("Contenu 1: ");
	    afficherBinaryInHex(d, entree1);
	    printf("\n");
	    printf("Contenu 2: ");
	    afficherBinaryInHex(d, entree2);
	    printf("\n");
			printf("Pre-images:\n");
			afficherBinaryInHex(d, stock1);
			printf("\n");
			afficherBinaryInHex(d, stock2);
			printf("\n");
		}
		else
		{
			printf("Valeur commune non retrouvee. t: %d\n", t);
		}

  }

	if(equalBits(d, entree1, entree2)==1)
	{
		for(int i=0; i<d; i++)
		{
			preimage1[i]=stock1[i];
			preimage2[i]=stock2[i];
		}
	}




}


void randomSeedPerso(int N, char * seed)
{
  srand(time(NULL));
  int r;
  for(int i=0; i<N; i++)
  {
    r=rand();
    if(TEST)
    {
      printf("Nombre aleatoire genere: %d\n", r);
    }
    seed[i]=moduloInt(r, 256);
  }

}
