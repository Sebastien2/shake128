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




void fillStateFromString(int w, char state[5][5][w], char * contenu, int b, int l)
{
	for(int i=0; i<5; i++)
	{
		for(int j=0; j<5; j++)
		{
			for(int k=0; k<w; k++)
			{
				state[i][j][k]=contenu[w*(5*j+i)+k];
			}
		}
	}
}


void fillStringFromState(int w, char state[5][5][w], char * contenu, int b, int l)
{
	for(int i=0; i<5; i++)
	{
		for(int j=0; j<5; j++)
		{
			for(int k=0; k<w; k++)
			{
				contenu[w*(5*j+i)+k]=state[i][j][k];
			}
		}
	}
}


void fillStringFromStateSection313(int w, char state[5][5][w], char * contenu, int b, int l)
{
	for(int j=0; j<5; j++)
	{
		for(int i=0; i<5; i++)
		{
			for(int k=0; k<w; k++)
			{
				contenu[w*(5*j+i)+k]=state[i][j][k];
			}
		}
	}
}




void getLane(int w, char lane[w], int i, int j, char state[5][5][w])
{
	for(int k=0; k<w; k++)
    {
		lane[k]=state[i][j][k];
	}
}


void getPlane(int j, int w, char plane[5*w], char state[5][5][w])
{
	char lane[w];
	for(int i=0; i<5; i++)
	{
		getLane(w, lane, i, j, state);
		for(int k=0; k<w; k++)
		{
			plane[5*i+k]=lane[k];
		}
	}
}


//A verifier: OK
void creerStringFromBits(int len1, char * sortie1, int len2, char * sortie2)
{
	char temp;
	for(int i=0; i<len2; i++)
	{
		temp=(sortie1[8*i+0]<<0)+(sortie1[8*i+1]<<1)+(sortie1[8*i+2]<<2)+(sortie1[8*i+3]<<3)+(sortie1[8*i+4]<<4)+(sortie1[8*i+5]<<5)+(sortie1[8*i+6]<<6)+(sortie1[8*i+7]<<7);
		sortie2[i]=temp;
	}
}



void creerBitsFromString(int len, char * entree, char * sortie)
{
	char temp;
	for(int i=0; i<len; i++)
	{
		temp=entree[i]&0x1;
		sortie[8*i]=temp;

		temp=entree[i]&0x2;
		temp=temp>>1;
		sortie[8*i+1]=temp;

		temp=entree[i]&0x4;
		temp=temp>>2;
		sortie[8*i+2]=temp;

		temp=entree[i]&0x8;
		temp=temp>>3;
		sortie[8*i+3]=temp;

		temp=entree[i]&0x10;
		temp=temp>>4;
		sortie[8*i+4]=temp;

		temp=entree[i]&0x20;
		temp=temp>>5;
		sortie[8*i+5]=temp;

		temp=entree[i]&0x40;
		temp=temp>>6;
		sortie[8*i+6]=temp;

		temp=entree[i]&0x80;
		temp=temp>>7;
		sortie[8*i+7]=temp;

	}
}



void creerStringFromHexString(int lenEntree, char * entree, char * sortie)
{
	int len=(lenEntree+1)/3;
	char temp1, temp2, temp;
	for(int i=0; i<len; i++)
	{
		temp1=entree[3*i];
		temp2=entree[3*i+1];
		printf("temp1: %d, temp2: %d\n", temp1, temp2);
		if(temp1>=48 && temp1<=57)
		{
			temp1=temp1-48;
		}
		else if(temp1>=65 && temp1<=70)
		{
			temp1=10+temp1-65;
		}
		else
		{
			printf("temp1 dans creerStringFromHexString incorrect car = %d\n", temp1);
		}

		if(temp2>=48 && temp2<=57)
		{
			temp2=temp2-48;
		}
		else if(temp2>=65 && temp2<=70)
		{
			temp2=10+temp2-65;
		}
		else
		{
			printf("temp2 dans creerStringFromHexString incorrect car = %d\n", temp2);
		}

		temp=temp1*16+temp2;
		sortie[i]=temp;
	}
}
