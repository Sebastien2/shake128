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




void afficherState(int w, char state[5][5][w])
{
	for(int i=0; i<5; i++)
	{
		for(int j=0; j<5; j++)
		{
			for(int k=0; k<w; k++)
			{
				printf("%c ", state[i][j][k]);
			}
		}
	}
}



void afficherStateHex(int w, char state[5][5][w])
{
	char temp;
	for(int j=0; j<5; j++)
	{
		for(int i=0; i<5; i++)
		{
			for(int k=w/8-1; k>=0; k--)
			{
				temp=(state[i][j][8*k]<<0)+((state[i][j][8*k+1])<<1)+((state[i][j][8*k+2])<<2)+((state[i][j][8*k+3])<<3)+((state[i][j][8*k+4])<<4)+((state[i][j][8*k+5])<<5)+((state[i][j][8*k+6])<<6)+((state[i][j][8*k+7])<<7);
				printf("%02x", (unsigned int)(temp&0xFF));
				//printf("%02x", (unsigned int)(state[i][j][k]&0xFF));
			}
			printf(" ");
		}
		printf("\n");
	}
	printf("\n\n");
}



//TODO: séparer les différents elem
void afficherStateHexInString(int w, char state[5][5][w])
{
	int len=5*5*w;
	char binary[len];
	for(int i=0; i<5; i++)
	{
		for(int j=0; j<5; j++)
		{
			for(int k=0; k<w; k++)
			{
				binary[w*(5*j+i)+k]=state[i][j][k];
			}
		}
	}
	char temp;
	//Puis on convertit en hex
	for(int i=0; i<len/8; i++)
	{
		temp=(binary[8*i]<<0)+(binary[8*i+1]<<1)+(binary[8*i+2]<<2)+(binary[8*i+3]<<3)+(binary[8*i+4]<<4)+(binary[8*i+5]<<5)+(binary[8*i+6]<<6)+(binary[8*i+7]<<7);
		printf("%02x ", (unsigned int)(temp&0xFF));
	}
}


void afficherBinary(int w, char state[5][5][w])
{

	for(int i=0; i<5; i++)
	{
		for(int j=0; j<5; j++)
		{
			for(int k=0; k<w; k++)
			{
				printf("%d", state[i][j][k]);
				//printf("%02x", (unsigned int)(state[i][j][k]&0xFF));
			}
			printf(" ");
		}
		printf("\n");
	}
	printf("\n\n");
}



void afficherStringEnHex(int len, char * sortie3)
{
	for(int i=0; i<len; i++)
	{
		printf("%02X ", (unsigned int)(sortie3[i]&0xFF));
	}
	printf("\n");
}



void afficherBinaryInHex(int len, char * binary)
{
	char temp;
	//Puis on convertit en hex
	for(int i=0; i<len/8; i++)
	{
		temp=(binary[8*i]<<0)+(binary[8*i+1]<<1)+(binary[8*i+2]<<2)+(binary[8*i+3]<<3)+(binary[8*i+4]<<4)+(binary[8*i+5]<<5)+(binary[8*i+6]<<6)+(binary[8*i+7]<<7);
		printf("%02x ", (unsigned int)(temp&0xFF));
	}
}



void afficherBinaryOfString(int len, char * binary)
{
	for(int i=0; i<len; i++)
	{
		printf("%d ", binary[i]);
	}
}
