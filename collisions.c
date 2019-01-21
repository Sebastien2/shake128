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


#ifndef COLLISIONN
	#define COLLISIONN "collisionN.h"
	#include COLLISIONN
#endif


#define TEST 0



void main(int argc, char ** argv)
{
  if(argc!=2)
  {
    printf("Veuillez fournir en argument la taille des preimages\n");
    return;
  }



  //On prend la taille des preimages
	char *p;
	int num;
	int err= 0;
	int conv = strtol(argv[1], &p, 10);
	if (err!= 0 || *p != '\0' || conv > INT_MAX)
	{
			printf("Argument 1 (taille en byte des preimages) incompris essayer d'entrer un nombre cette fois-ci...\n");
			return;
	}
	else
	{
	    num = conv;
	}
	int taille=num;

	//Puis on lance la recherce
	rechercheFichiers(taille, 1000, 1000);


}
