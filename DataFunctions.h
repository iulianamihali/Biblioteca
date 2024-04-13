#pragma once
#include "Structuri.h"

void printare_meniu();
void meniu_principal(Context* context);
void login_cont(Context* context);
void meniu_imprumutare(Context* context);
void meniu_restituire(Context* context);
void meniu_donare(Context* context);
void meniu_vizualizare_carti(Context* context);
void meniu_cautare_carti(Context* context);
void meniu_vizualizare_cont(Context* context);
void meniu_exit();

void stergere_imprumuturi(Context* context, char carte_cautata[]);
void adaugare_donatie(Context* context, char autor[], char carte[], char editura[]);
void cautare_carte(Context* context, char text[]);
int  fct_tolower(char sir[], char text[]);
int  verify_login_argv(Context context, char nume[], char parola[]);
int hashString(const char* str);
char* getCurrentDate();