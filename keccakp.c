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


void keccakp(int b, char * S, int nr, char * sortie)
{

  //Step 1
  int w=b/25;
	int l=(int)(log(w)/log(2));
  char state[5][5][w];
  char Aprime[5][5][w];
  fillStateFromString(w, state, S, b, l);

  //Step 2
  int ind=0;
  for(int ir=12+2*l-nr; ir<=12+2*l-1; ir++)
  {
    if(TEST)
    {
      printf("Round %d:\n\n", ind);
    }

    ind++;
    if(TEST)
    {
      roundStepTest( w, state, Aprime, ir, l);
    }
    else
    {
      roundStep( w, state, Aprime, ir, l);
    }

    copier(w, state, Aprime);
  }

  //Step 3
  fillStringFromStateSection313( w,  state, sortie, b, l);

  //Step 4
  //on a le résultat en pinteur

}


void keccakf(int b, char * S, char * sortie)
{
  int w=b/25;
  double t1=log(w);
  double t2=log(2);
  double t3=t1/t2;
  //printf("les doubles: %f %f %f\n", t1, t2, t3);
	int l=(int)(t3);
  int nr=12+2*l;
  printf("l: %d\n", l);
  //printf("nr: %d\n", nr);
  keccakp( b, S, nr, sortie);
}
