//pt scanf, printf
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE


#include <stdio.h>
#include <stdlib.h>
#include "Structuri.h"
#include "Update.h"

void update_utilizatori(Utilizator utilizatori[], int n)
{
	FILE* file = fopen("utilizatori.txt", "w");
	for (int i = 0; i < n; i++)
	{
		fprintf(file, "%d,%s,%s,%s", utilizatori[i].cod, utilizatori[i].nume, utilizatori[i].parola, utilizatori[i].tip_utilizator);
		fprintf(file, "\n");
	}
	fclose(file);

}

void update_imprumuturi(Imprumut imprumuturi[], int n)
{
	FILE* file = fopen("imprumuturi.txt", "w");
	for (int i = 0; i < n; i++)
	{
		fprintf(file, "%d,%d,%s", imprumuturi[i].cod_utilizator, imprumuturi[i].cod_carte, imprumuturi[i].data_imprumut);
		fprintf(file, "\n");
	}
	fclose(file);
}

void update_carti(Carte carti[], int n)
{
	FILE* file = fopen("carti.txt", "w");
	for (int i = 0; i < n; i++)
	{
		fprintf(file, "%d,%s,%s,%s,%d", carti[i].cod, carti[i].nume, carti[i].autor, carti[i].editura, carti[i].nr_exemplare);
		fprintf(file, "\n");
	}
	fclose(file);

}


void update_istoric(Istoric istoric[], int n)
{
	FILE* file = fopen("istoric.txt", "w");
	for (int i = 0; i < n; i++)
	{
		fprintf(file, "%d,%d,%s,%s", istoric[i].cod_utilizator, istoric[i].cod_carte, istoric[i].data_imprumut, istoric[i].data_return);
		fprintf(file, "\n");
	}
	fclose(file);

}

void update_donatii(Donatie donatii[], int n)
{
	FILE* file = fopen("donatii.txt", "w");
	for (int i = 0; i < n; i++)
	{
		fprintf(file, "%d,%s,%s", donatii[i].cod_utilizator, donatii[i].nume_carte, donatii[i].data_donatie);
		fprintf(file, "\n");
	}
	fclose(file);

}