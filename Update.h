#pragma once

#include <stdio.h>
#include "Structuri.h"
#include "Init.h"

void update_utilizatori(Utilizator utilizatori[], int n)
{
	FILE* file = fopen("utilizatori.txt", "w");
	for (int i = 0; i < n; i++)
	{
		fprintf(file, "%d,%s,%s",utilizatori[i].cod, utilizatori[i].nume, utilizatori[i].parola);
		fprintf(file,"\n");
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