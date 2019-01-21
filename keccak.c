#include <stdio.h>
#include <stdlib.h>
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

#ifndef TEST
  #define TEST 0
#endif





void keccak(int c, int N, int d, char * entree, char * sortie)
{
  int b=1600;
  sponge(d, N, entree, sortie, keccakp, b-c, b);
}




void shake128(int len, char * contenu, int c, char * sortie, int d)
{
  int b=len*8+4; //On rajoute les 4 bits à la fin
  if(TEST)
  {
    printf("len: %d\n", len);
  }

  int w=b/25;
	int l=(int)(log(w)/log(2));


  char entree[b];

  creerBitsFromString(len, contenu, entree);
  entree[b-4]=(char)1;
  entree[b-3]=(char)1;
  entree[b-2]=(char)1;
  entree[b-1]=(char)1;
  if(TEST)
  {
    afficherBinaryOfString(b, entree);
  }

  keccak( c,  b,  d, entree, sortie);

}




void shake128Bits(int len, char * contenu, int c, char * sortie, int d)
{
  int b=len+4; //On rajoute les 4 bits à la fin
  if(TEST)
  {
    printf("len: %d\n", len);
  }

  int w=b/25;
	int l=(int)(log(w)/log(2));


  char entree[b];
	for(int i=0; i<b-4; i++)
	{
		entree[i]=contenu[i];
	}

  entree[b-4]=(char)1;
  entree[b-3]=(char)1;
  entree[b-2]=(char)1;
  entree[b-1]=(char)1;
  if(TEST)
  {
    afficherBinaryOfString(b, entree);
  }

  keccak( c,  b,  d, entree, sortie);

}
