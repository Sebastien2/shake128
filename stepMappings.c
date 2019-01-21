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





char moduloChar(int n, int mod)
{
	char res;
	res=n%mod;
	while(res<0)
	{
		res+=mod;
	}
	while(res>=mod)
	{
		res-=mod;
	}
	return res;
}

int moduloInt(int n, int mod)
{
	int res;
	res=n%mod;
	while(res<0)
	{
		res+=mod;
	}
	while(res>=mod)
	{
		res-=mod;
	}
	return res;
}






//Nouvelle verion: pour qu'il n'y ait qu'un seul bit a chaque fois, chgt dans le XOR

void theta(int w, char A[5][5][w], char Aprime[5][5][w])
{
	int a, b, c;
	char C[5][w];
	char D[5][w];
	for(int i=0; i<5; i++)
	{
		for(int j=0; j<w; j++)
		{
			C[i][j]=0;
			D[i][j]=0;
		}
	}
	for(int i=0; i<5; i++)
	{
		for(int k=0; k<w; k++)
		{
			C[i][k]=moduloChar((A[i][0][k]+A[i][1][k]+A[i][2][k]+A[i][3][k]+A[i][4][k]), 2);
		}
	}

	for(int i=0; i<5; i++)
	{
		for(int k=0; k<w; k++)
		{
			a=moduloInt((i-1), 5);
			b=moduloInt((i+1), 5);
			c=moduloInt((k-1), w);
			//printf("a: %d, b: %d, c: %d\n", a, b, c);
			D[i][k]=(C[a][k]+C[b][c])%2;
			//printf("%d \n", D[i][k]);
		}
	}

	for(int i=0; i<5; i++)
	{
		for(int j=0; j<5; j++)
		{
			for(int k=0; k<w; k++)
			{
				Aprime[i][j][k]=(A[i][j][k]+D[i][k])%2;
				//printf("%d ", Aprime[i][j][k]);
			}
		}
	}
}



void rho(int w, char A[5][5][w], char Aprime[5][5][w])
{
	int a;
	for(int z=0; z<w; z++)
	{
		Aprime[0][0][z]=A[0][0][z];
	}
	int temp;
	int x=1;
	int y=0;
	for(int t=0; t<=23; t++)
	{
		//printf("x: %d, y: %d \n", x, y);
		for(int z=0; z<w; z++)
		{
			a=moduloInt((z-((t+1)*(t+2))/2),w);
			//printf("a: %d\n", a);
			Aprime[x][y][z]=A[x][y][a];
		}
		temp=x;
		x=y;
		y=moduloInt((2*temp+3*y),5);
		//printf("y: %d\n", y);
	}
}



void pi(int w, char A[5][5][w], char Aprime[5][5][w])
{
	int a;
	for(int x=0; x<5; x++)
	{
		for(int y=0; y<5; y++)
		{
			for(int z=0; z<w; z++)
			{
				a=moduloInt((x+3*y), 5);
				Aprime[x][y][z]=A[a][x][z];
			}
		}
	}
}



void chi(int w, char A[5][5][w], char Aprime[5][5][w])
{
	int a, b;
	for(int x=0; x<5; x++)
	{
		for(int y=0; y<5; y++)
		{
			for(int z=0; z<w; z++)
			{
				a=moduloInt((x+1), 5);
				b=moduloInt((x+2), 5);
				Aprime[x][y][z]=(A[x][y][z]+(moduloChar((A[a][y][z]+1), 2) * A[b][y][z]))%2;
			}
		}
	}
}


//TODO: vérifier la rectitude de cette fonction
char rc(int t)
{
	if(t%255==0)
	{
		return 1;
	}

	int m=300;
	char R[m];
	for(int i=0; i<m; i++)
	{
		R[i]=0;
	}
	R[0]=1;

	for(int i=1; i<=t%255; i++)
	{

		for(int i=m-1; i>0; i--)
		{
			R[i]=R[i-1];
		}
		R[0]=0;

		R[0]=(R[0]+R[8])%2;
		R[4]=(R[4]+R[8])%2;
		R[5]=(R[5]+R[8])%2;
		R[6]=(R[6]+R[8])%2;


		for(int i=8; i<m; i++)
		{
			R[i]=0;
		}
	}

	return R[0];
}






void iota(int w, char A[5][5][w], char Aprime[5][5][w], int ir, int l)
{
	//printf("ir: %d\n", ir);
	for(int x=0; x<5; x++)
	{
		for(int y=0; y<5; y++)
		{
			for(int z=0; z<w; z++)
			{
				Aprime[x][y][z]=A[x][y][z];
			}
		}
	}

	//TODO: check, spec unclear
	char RC[w];
	for(int i=0; i<w; i++)
	{
		RC[i]=0;
	}

	int ind;
	int val;
	for(int j=0; j<=l; j++)
	{
		ind=(1<<j) - 1;
		val=rc(j+7*ir);
		//printf("indice: %d , valeur: %d\n", ind, val);
		RC[ind]=val;
	}

	/*
	printf("RC: ");
	for(int i=0; i<w; i++)
	{
		printf("%d ", RC[i]);
	}
	printf("\n");
	*/

	for(int z=0; z<w; z++)
	{
		Aprime[0][0][z]=(Aprime[0][0][z]+RC[z])%2;
		/*
		if(Aprime[0][0][z]!=0)
		{
			printf("Valeur non nulle en (0,0,%d): %d\n", z, Aprime[0][0][z]);
		}
		*/
	}

}
