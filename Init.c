#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE


#include <string.h>
#include <stdlib.h>
#include "Structuri.h"
#include "Init.h"
#include <stdio.h>


void citire_carti(Carte carti[], int* n)   //preluam datele din fisierul Carti si le punem in vector
{
	FILE* fptr;
	fptr = fopen("carti.txt", "r");
	char string[101];
	int k = 0;
	while (fgets(string, 101, fptr))
	{
		int i = 0;
		char* ptr = strtok(string, ",\n");
		while (ptr != NULL)
		{
			switch (i)
			{
			case 0:
				carti[k].cod = atoi(ptr);
				break;
			case 1:
				carti[k].nume = (char*)malloc(101);
				strcpy(carti[k].nume, ptr);
				break;
			case 2:
				carti[k].autor = (char*)malloc(101);
				strcpy(carti[k].autor, ptr);
				break;
			case 3:
				carti[k].editura = (char*)malloc(101);
				strcpy(carti[k].editura, ptr);
				break;
			case 4:
				carti[k].nr_exemplare = atoi(ptr);
				break;
			}
			ptr = strtok(NULL, ",\n");
			i++;

		}
		k++;

	}
	*n = k;

	fclose(fptr);
}


void citire_utilizatori(Utilizator utilizatori[], int* n)
{
	FILE* fptr = fopen("utilizatori.txt", "r");
	char string[101];
	int k = 0;
	while (fgets(string, 101, fptr))
	{
		int i = 0;
		char* ptr = strtok(string, ",\n");
		while (ptr != NULL)
		{
			switch (i)
			{
			case 0:
				utilizatori[k].cod = atoi(ptr);
				break;
			case 1:
				utilizatori[k].nume = (char*)malloc(101);
				strcpy(utilizatori[k].nume, ptr);
				break;
			case 2:
				utilizatori[k].parola = (char*)malloc(101);
				strcpy(utilizatori[k].parola, ptr);
				break;
			case 3:
				utilizatori[k].tip_utilizator = (char*)malloc(101);
				strcpy(utilizatori[k].tip_utilizator, ptr);
				break;
			}
			ptr = strtok(NULL, ",\n");
			i++;
		}
		k++;
	}
	*n = k;
	fclose(fptr);
}

void citire_imprumuturi(Imprumut imprumuturi[], int* n)
{
	FILE* fptr = fopen("imprumuturi.txt", "r");
	char string[101];
	int k = 0;
	while (fgets(string, 101, fptr))
	{
		int i = 0;
		char* ptr = strtok(string, ",\n");
		while (ptr != NULL)
		{
			switch (i)
			{
			case 0:
				imprumuturi[k].cod_utilizator = atoi(ptr);
				break;
			case 1:
				imprumuturi[k].cod_carte = atoi(ptr);
				break;
			case 2:
				imprumuturi[k].data_imprumut = (char*)malloc(20);
				strcpy(imprumuturi[k].data_imprumut, ptr);
				break;
			}
			ptr = strtok(NULL, ",\n");
			i++;
		}
		k++;
	}

	*n = k;
	fclose(fptr);
}


void citire_donatii(Donatie donatii[], int* n)
{
	FILE* fptr = fopen("donatii.txt", "r");
	char string[101];
	int k = 0;
	while (fgets(string, 101, fptr))
	{
		int i = 0;
		char* ptr = strtok(string, ",\n");
		while (ptr != NULL)
		{
			switch (i)
			{
			case 0:
				donatii[k].cod_utilizator = atoi(ptr);
				break;

			case 1:
				donatii[k].nume_carte = (char*)malloc(101);
				strcpy(donatii[k].nume_carte, ptr);
				break;
			case 2:
				donatii[k].data_donatie = (char*)malloc(20);
				strcpy(donatii[k].data_donatie, ptr);
				break;
			}
			ptr = strtok(NULL, ",\n");
			i++;
		}
		k++;
	}
	*n = k;
	fclose(fptr);
}

void citire_istoric(Istoric istoric[], int* n)
{
	FILE* fptr = fopen("istoric.txt", "r");
	char string[101];
	int k = 0;
	while (fgets(string, 101, fptr))
	{
		int i = 0;
		char* ptr = strtok(string, ",\n");
		while (ptr != NULL)
		{
			switch (i)
			{
			case 0:
				istoric[k].cod_utilizator = atoi(ptr);
				break;

			case 1:
				istoric[k].cod_carte = atoi(ptr);
				break;
			case 2:
				istoric[k].data_imprumut = (char*)malloc(20);
				strcpy(istoric[k].data_imprumut, ptr);
				break;
			case 3:
				istoric[k].data_return = (char*)malloc(20);
				strcpy(istoric[k].data_return, ptr);
				break;
			}
			ptr = strtok(NULL, ",\n");
			i++;
		}
		k++;
	}
	*n = k;
	fclose(fptr);

}

void init(Context* context)  // actualizam contextul nostru ca mai apoi sa putem utiliza totii vectorii cu datele din fisiere
{
	citire_carti(context->carti, &context->nr_carti);
	citire_utilizatori(context->utilizatori, &context->nr_utilizatori);
	citire_imprumuturi(context->imprumuturi, &context->nr_imprumuturi);
	citire_donatii(context->donatii, &context->nr_donatii);
	citire_istoric(context->istoric, &context->nr_istoric);
}