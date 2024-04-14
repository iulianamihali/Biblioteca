#pragma once
typedef struct Carte
{
	int cod;
	char* nume;
	char* autor;
	char* editura;
	int nr_exemplare;

}Carte;

typedef struct Utilizator 
{
	int cod;
	char* nume;
	char* parola;
	char* tip_utilizator;

}Utilizator;

typedef struct Imprumut
{
	int cod_utilizator;
	int cod_carte;
	char* data_imprumut;

}Imprumut;

typedef struct Donatie
{
	int cod_utilizator;
	char* nume_carte;
	char* data_donatie;


}Donatie;

typedef struct Istoric
{
	int cod_utilizator;
	int cod_carte;
	char* data_imprumut;
	char* data_return;

}Istoric;

typedef struct Context
{
	//Carti
	Carte carti[1001];
	int nr_carti;

	//Utilizatori
	Utilizator utilizatori[1001];
	int nr_utilizatori;

	//Imprumuturi
	Imprumut imprumuturi[1001];
	int nr_imprumuturi;

	//Donatii
	Donatie donatii[1001];
	int nr_donatii;

	//Istoric
	Istoric istoric[1001];
	int nr_istoric;

	Utilizator cont_logat;  


}Context;