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






#ifndef NR
  #define NR 24
#endif
#ifndef TEST
  #define TEST 0
#endif





void sponge(int d, int N, char * entree, char * sortie, void(*f)(int b, char * S, int nr, char * sortie), int r, int b)
{
	if(TEST)
	{
		printf("Taille de la sortie: %d\n", d);
	}
  //On suppose entree de longueuer N, et sortie e longueur d
  //Step 1
  int lenPad=padLength(r, N);
  if(TEST)
  {
    printf("Longueur du padding: %d\n", lenPad);
  }
  char padding[lenPad];
  pad(lenPad, padding);
  if(TEST)
  {
    printf("Padding: ");
    for(int i=0; i<lenPad; i++)
    {
      printf("%d ", padding[i]);
    }
    printf("\n");
  }
  char Pm[N+lenPad];
	if(TEST)
	{
		printf("N vaut: %d\n", N);
	}
  for(int i=0; i<N; i++)
  {
    Pm[i]=entree[i];
  }
  for(int i=N; i<N+lenPad; i++)
  {
    Pm[i]=padding[i-N];
  }

  //Step 2
  int n=(N+lenPad)/r;

  //Spte 3
  int c=b-r;

  //Step 4
  char P[n][r];
  for(int i=0; i<n; i++)
  {
    for(int j=0; j<r; j++)
    {
      P[i][j]=Pm[r*i+j];
    }
  }
	if(TEST)
	{
		printf("\nLes Pi:\n");
		for(int i=0; i<n; i++)
		{
			printf("P%d: ", i);
			afficherBinaryInHex(r, P[i]);
			printf("\n");
		}
		printf("\n");
	}


  //Step 5
  char S[b];
  for(int i=0; i<b; i++)
  {
    S[i]=0;
  }

  //Step 6
  char temp[b];

  if(TEST)
  {
    printf("Nombre de permutations: n=%d, r=%d\n", n, r);
  }
  for(int i=0; i<n; i++)
  {
    for(int j=0; j<r; j++)
    {
      temp[j]=P[i][j];
    }
    for(int j=r; j<b; j++)
    {
      temp[j]=0;
    }
		if(TEST)
		{
			printf("temp avant son integration:\n");
			afficherBinaryInHex(b, temp);
      printf("\n");
		}
    for(int j=0; j<b; j++)
    {
      temp[j]=moduloChar(temp[j]+S[j], 2);  //TODO: verifier l'operation binaire + choisir NR
    }
    if(TEST)
    {
      printf("Input of permutation:\n");
      afficherBinaryInHex(b, temp);
      printf("\n");
    }
    (*f)( b, temp,  NR, S);
    if(TEST)
    {
      printf("State after permutation:\n");
      afficherBinaryInHex(b, S);
      printf("\n");
    }
  }

	if(TEST)
	{
		printf("\n");
	}

  //Step 7
  char Z[d];
  int pos=0;
  int index=0;

	while(pos<d && index<r)
	{
		Z[pos]=S[index];
		index+=1;
		pos+=1;
	}
	if(TEST)
	{
		printf("pos en premier coup: %d, r: %d\n", pos, r);
	}

  if(TEST)
  {
    printf("Etape: compression\n");
  }
	int compteur=0;
  while(pos<d /*|| compteur<4*/)
  {
		compteur+=1;
		if(TEST)
		{
			printf("Compression numero %d\n:", compteur);
		}
    index=0;


    //Step 10
    for(int i=0; i<b; i++)
    {
      temp[i]=S[i];
    }
    if(TEST)
    {
      printf("Avant compression:\n");
      afficherBinaryInHex(b, temp);
      printf("\n");
    }

    (*f)( b, temp,  NR, S);

		while(pos<d && index<r)
    {
			if(TEST)
			{
				//printf("exec index: %d, r: %d, pos: %d, d: %d\n", index, r, pos, d);
			}
			Z[pos]=S[index];
      index+=1;
      pos+=1;
    }

    if(TEST)
    {
      printf("Apres compression:\n");
      afficherBinaryInHex(b, S);
      printf("\n");
    }
  }


  //Step 9
  for(int i=0; i<d; i++)
  {
    sortie[i]=Z[i];
  }
  if(TEST)
  {
    printf("Sortie de sponge:\n");
    afficherBinaryInHex(d, sortie);
    printf("\n");
  }
}








//Fournit la taille du padding
int padLength(int x, int m)
{
  int res=0;
  /*
  int r=m%x;
  while(r<0)
  {
    r+=x;
  }
  res=x-r;
  while(res<0)
  {
    res+=x;
  }
  while(res>=x)
  {
    res-=x;
  }
  */
  //res=(-m-2)%x;
  res=moduloInt((-m-2), x);
  if(res<0)
  {
    res+=x;
  }
  return res+2;

}

//TODO: prendre le padding que l'on veut
void pad(int len, char * sortie)
{
  /*
  for(int i=0; i<len; i++)
  {
    sortie[i]=0;
  }
  */
  sortie[0]=1;
  for(int i=1; i<len-1; i++)
  {
    sortie[i]=0;
  }
  sortie[len-1]=1;

}
