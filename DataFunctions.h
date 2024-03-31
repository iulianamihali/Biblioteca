#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Update.h"
#include "Structuri.h"

void printare_meniu();
void meniu_principal(Context* context);
void login_cont(Context* context);
void meniu_imprumutare(Context* context);
void meniu_restituire(Context* context);
void meniu_donare(Context* context);
void meniu_vizualizare_carti(Context* context);
void meniu_exit();

char* getCurrentDate()
{
    time_t currentTime;
    char* currentDate = (char*)malloc(20);
    time(&currentTime);
    struct tm* localTime = localtime(&currentTime);
    strftime(currentDate, 20, "%d/%m/%Y", localTime);
    return currentDate;
}


void printare_meniu()
{
    printf("- - - - - - - - - - - - - -\n");
    printf("|     1.Imprumutare        |\n");
    printf("|     2.Restituire         |\n");
    printf("|     3.Donare             |\n");
    printf("|     4.Vizualizare carti  |\n");
    printf("|     5.Cautare            |\n");
    printf("|     6.Vizualizare cont   |\n");
    printf("|     7.Iesire             |\n");
    printf("- - - - - - - - - - - - - -");
}



void login_cont(Context* context)
{
    printf("1.Log in\n");
    printf("2.Sign up\n");
    printf("=>");
    int n;
    scanf("%d", &n);
    getchar();
    system("cls");
    if (n == 1)
    {
        char nume[101], parola[101];
        printf("Introduceti numele: ");
        fgets(nume, 101, stdin);
        nume[strcspn(nume, "\n")] = 0;
        printf("Introduceti parola: ");
        fgets(parola, 101, stdin);
        parola[strcspn(parola, "\n")] = 0;
        system("cls"); //clear screen

        int stop_while = 0;
        while (stop_while == 0)
        {
            int cod_exista = 0;

            for (int i = 0; i < context->nr_utilizatori; i++)
            {

                if (strcmp(nume, context->utilizatori[i].nume) == 0 && strcmp(parola, context->utilizatori[i].parola) == 0)//verificare pt login daca datele introduse exista
                {
                    cod_exista = 1;
                    context->cont_logat.cod = context->utilizatori[i].cod;
                    break;
                }
            }
            if (cod_exista == 1)
            {
                context->cont_logat.nume = (char*)malloc(101);
                strcpy(context->cont_logat.nume, nume);
                context->cont_logat.parola = (char*)malloc(101);
                strcpy(context->cont_logat.parola, parola);
                printare_meniu();
                meniu_principal(context);
                stop_while = 1;
            }
            else
            {

                printf("Nume sau parola invalida. Incearca din nou!\n");
                system("cls");
                printf("Introduceti numele: ");
                scanf("%s", nume);
                printf("Introduceti parola: ");
                scanf("%s", parola);
                getchar();
                system("cls");

            }
        }

    }
    else
    {
        char nume[101], parola[101];
        int verif = 1, OK = 1;
        printf("Introduceti numele: ");
        scanf("%s", nume);
        while (OK)
        {
            for (int i = 0; i < context->nr_utilizatori; i++)
            {
                if (strcmp(nume, context->utilizatori[i].nume) == 0)
                {
                    verif = 0;
                    break;
                }
            }
            if (verif == 0)
            {
                printf("Numele exista deja.Incearca altul\n");
                verif = 1;
                scanf("%s", nume);

            }
            else
            {
                OK = 0;
                break;
            }
        }
        printf("Introduceti parola: ");
        scanf("%s", parola);

        int cod_random = rand();
        context->cont_logat.cod = cod_random;
        context->cont_logat.nume = (char*)malloc(101);
        strcpy(context->cont_logat.nume, nume);
        context->cont_logat.parola = (char*)malloc(101);
        strcpy(context->cont_logat.parola, parola);

        //adaugam noul utilizator in vectorul de utilizatori
        context->utilizatori[context->nr_utilizatori].cod = cod_random;
        context->utilizatori[context->nr_utilizatori].nume = (char*)malloc(101);
        strcpy(context->utilizatori[context->nr_utilizatori].nume, nume);
        context->utilizatori[context->nr_utilizatori].parola = (char*)malloc(101);
        strcpy(context->utilizatori[context->nr_utilizatori].parola, parola);
        context->nr_utilizatori++;
        update_utilizatori(context->utilizatori, context->nr_utilizatori); //un nou utilizator s-a inregistrat deci facem update in fisierul de utilizatori

        system("cls");
        printare_meniu();
        meniu_principal(context);
    }
}


void meniu_imprumutare(Context* context)
{
    printf("0.Inapoi\n");
    printf("1.Continuati\n");
    printf("=>");
    int optiune;
    scanf("%d", &optiune);
    getchar();
    if (optiune == 0)
    {
        system("cls");
        printare_meniu();
        meniu_principal(context);
    }
    else if (optiune == 1)
    {

        system("cls");
        char autor[101], carte[101];
        printf("Autorul: ");
        fgets(autor, 101, stdin);
        autor[strcspn(autor, "\n")] = 0;
        printf("Cartea: ");
        fgets(carte, 101, stdin);
        carte[strcspn(carte, "\n")] = 0;

        int stop_while = 1;
        while (stop_while == 1)
        {
            for (int i = 0; i < context->nr_carti; i++)
            {
                if (strcmp(carte, context->carti[i].nume) == 0)
                {
                    if (context->carti[i].nr_exemplare > 0)
                    {
                        stop_while = 0;
                        //updatam vectorul de imprumuturi
                        context->imprumuturi[context->nr_imprumuturi].cod_utilizator = context->cont_logat.cod;
                        context->imprumuturi[context->nr_imprumuturi].cod_carte = context->carti[i].cod;
                        context->imprumuturi[context->nr_imprumuturi].data_imprumut = (char*)malloc(20);
                        char* currentDate = getCurrentDate();
                        strcpy(context->imprumuturi[context->nr_imprumuturi].data_imprumut, currentDate);
                        context->nr_imprumuturi++;
                        context->carti[i].nr_exemplare--;
                        update_carti(context->carti, context->nr_carti);
                        update_imprumuturi(context->imprumuturi, context->nr_imprumuturi); //facem update in fisierul de imprumuturi
                        system("cls");
                        printf("Ati imprumutat cartea cu succes.\nCitire placuta!");
                        break;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }



    }

}


void meniu_restituire(Context* context)
{
    printf("0.Inapoi\n");
    printf("1.Continuati\n");
    printf("=>");
    int optiune;
    scanf("%d", &optiune);
    if (optiune == 0)
    {
        system("cls");
        printare_meniu();
        meniu_principal(context);
    }
    else if (optiune == 1)
    {
        system("cls");
        char autor[101], carte[101];
        printf("Autorul: ");
        scanf("%s", autor);
        printf("Cartea: ");
        scanf("%s", carte);
        getchar();
        printf("Cartea dvs. %s a fost restituita cu succes!", carte);
    }

}

void meniu_donare(Context* context)
{
    printf("0.Inapoi\n");
    printf("1.Continuati\n");
    printf("=>");
    int optiune;
    scanf("%d", &optiune);
    if (optiune == 0)
    {
        system("cls");
        printare_meniu();
        meniu_principal(context);
    }
    else if (optiune == 1)
    {
        system("cls");
        char autor[101], carte[101];
        printf("Autorul: ");
        scanf("%s", autor);
        printf("Cartea: ");
        scanf("%s", carte);
        getchar();
        printf("Cartea dvs. %s a fost donata cu succes!", carte);
    }
}

void meniu_vizualizare_carti(Context* context)
{
}

void meniu_cautare_carti(Context* context)
{
}

void meniu_vizualizare_cont(Context* context)
{

}

void meniu_exit()
{
    exit(0);
}


void meniu_principal(Context* context)
{
    printf("\n");
    int number;
    scanf("%d", &number);
    getchar();
    system("cls");

    switch (number)
    {
    case 1:
        meniu_imprumutare(context);
        break;
    case 2:
        meniu_restituire(context);
        break;
    case 3:
        meniu_donare(context);
        break;
    case 4:
        meniu_vizualizare_carti(context);
        break;
    case 5:
        meniu_cautare_carti(context);
        break;
    case 6:
        meniu_exit();
        break;
    }

}