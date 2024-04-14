#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "Structuri.h"
#include "Update.h"
#include "Init.h"
#include "DataFunctions.h"

int hashString(const char* str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    // Ajustăm valoarea hash la dimensiunea unui int
    return (int)(hash % 2147483647);
    
}
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
    printf("- - - - - - - - - - - - - -\n");
}



void login_cont(Context* context)
{
    printf(" - - - - - - - - - -\n");
    printf("|    Biblioteca     |\n");
    printf("|    1.Log in       |\n");
    printf("|    2.Sign up      |\n");
    printf(" - - - - - - - - - - \n");
    printf("=> ");
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
                printf("Introduceti numele: ");
                fgets(nume, 101, stdin);
                nume[strcspn(nume, "\n")] = 0;
                printf("Introduceti parola: ");
                fgets(parola, 101, stdin);
                parola[strcspn(parola, "\n")] = 0;
                system("cls");

            }
        }

    }
    else if(n == 2)
    {
        char nume[101], parola[101];
        int valid_nume = 1, OK = 1;
        printf(" Introduceti numele: ");
        scanf("%s", nume);
        while (OK)
        {
            for (int i = 0; i < context->nr_utilizatori; i++)
            {
                if (strcmp(nume, context->utilizatori[i].nume) == 0)
                {
                    valid_nume = 0;
                    break;
                }
            }
            if (valid_nume == 0)
            {
                printf(" Numele exista deja.Incearca altul\n");
                printf("=> ");
                scanf("%s", nume);
                valid_nume = 1;

            }
            else
            {
                system("cls");
                OK = 0;
                break;
            }
        }
        printf(" Introduceti parola: ");
        scanf("%s", parola);

        char str[101];
        strcpy(str, nume);
        strcpy(str + strlen(str), parola);
        int cod_random = hashString(str);
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
    else
    {
        system("cls");
        login_cont(context);
    }
}


void meniu_imprumutare(Context* context)
{
    printf(" 0.Inapoi\n");
    printf(" 1.Continuati\n");
    printf(" => ");
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
        printf(" Autorul: ");
        fgets(autor, 101, stdin);
        autor[strcspn(autor, "\n")] = 0;
        printf(" Cartea: ");
        fgets(carte, 101, stdin);
        carte[strcspn(carte, "\n")] = 0;
        system("cls");

        int stop_while = 1;
        while (stop_while == 1)
        {
            for (int i = 0; i < context->nr_carti; i++)
            {
                if (strcmp(carte, context->carti[i].nume) == 0 && strcmp(autor, context->carti[i].autor) == 0)
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
                        char* data_imprumut = getCurrentDate();
                        system("cls");
                        printf("     Ati imprumutat cartea cu succes.Citire placuta!\n\n\n");
                        printf(" - - - - - - - - - - - - - - - - -\n");
                        printf(" |     0.Inapoi meniu             |\n");
                        printf(" |     1.Exit                     |\n");
                        printf(" - - - - - - - - - - - - - - - - - \n");
                        int n;
                        printf(" => ");
                        scanf("%d", &n);
                        getchar();
                        if (n == 0)
                        {
                            system("cls");
                            printare_meniu();
                            meniu_principal(context);
                        }
                        else if (n == 1)
                        {
                            exit(0);
                        }
                        else 
                        {
                            int stop_while2 = 0;
                            while (stop_while2 == 0)
                            {
                                system("cls");
                                printf(" - - - - - - - - - - - - - - - - -\n");
                                printf(" |     0.Inapoi meniu             |\n");
                                printf(" |     1.Exit                     |\n");
                                printf(" - - - - - - - - - - - - - - - - - \n");
                                int n;
                                printf(" => ");
                                scanf("%d", &n);
                                getchar();
                                if (n == 0)
                                {
                                    system("cls");
                                    printare_meniu();
                                    meniu_principal(context);
                                    
                                }
                                else if (n == 1)
                                {
                                    stop_while2 = 1;
                                    exit(0);

                                }
                            }

                        }
                        break;
                    }
                    else
                    {
                        printf(" Stare: Stoc epuizat!  \n");
                        printf(" 1.Alege alta carte!   \n");
                        stop_while = 0;
                        break;
                    }
                }


            }
            if (stop_while == 1)
            {
                printf("      Ne pare rau, nu avem aceasta carte.      \n");
                printf(" 1.Alegeti alta carte\n");
                printf(" 2.Reveniti la meniul principal\n");
                int n;
                printf("=> ");
                scanf("%d", &n);
                getchar();
                system("cls");
                if (n == 1)
                {
                    printf(" Autorul: ");
                    fgets(autor, 101, stdin);
                    autor[strcspn(autor, "\n")] = 0;
                    printf(" Cartea: ");
                    fgets(carte, 101, stdin);
                    carte[strcspn(carte, "\n")] = 0;
                    system("cls");
                    
                }
                else if(n == 2)
                {
                    printare_meniu();
                    meniu_principal(context);
                    stop_while = 0;
                    break;
                }
                else
                {
                    int stop_while = 0;
                    while (stop_while == 0)
                    {
                        system("cls");
                        printf(" 1.Alegeti alta carte\n");
                        printf(" 2.Reveniti la meniul principal\n");
                        int n;
                        printf("=> ");
                        scanf("%d", &n);
                        getchar();
                        if (n == 1)
                        {
                            printf(" Autorul: ");
                            fgets(autor, 101, stdin);
                            autor[strcspn(autor, "\n")] = 0;
                            printf(" Cartea: ");
                            fgets(carte, 101, stdin);
                            carte[strcspn(carte, "\n")] = 0;
                            system("cls");
                            stop_while = 1;
                            break;
                        }
                        else if (n == 2)
                        {
                            printare_meniu();
                            meniu_principal(context);
                            stop_while = 1;
                            break;
                        }
                    }
                }
            }
        }



    }
    else
    {
        system("cls");
        meniu_imprumutare(context);
    }

}


void meniu_restituire(Context* context)
{
    printf(" 0.Inapoi\n");
    printf(" 1.Continuati\n");
    printf(" => ");
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
        printf(" Autorul: ");
        fgets(autor, 101, stdin);
        autor[strcspn(autor, "\n")] = 0;
        printf(" Cartea: ");
        fgets(carte, 101, stdin);
        carte[strcspn(carte, "\n")] = 0;
        stergere_imprumuturi(context, autor, carte);

        printf(" Cartea dvs. %s a fost restituita cu succes!\n", carte);
        printf(" 0.Inapoi meniu\n");
        printf(" 1.Exit\n");
        int n;
        printf(" => ");
        scanf("%d", &n);
        getchar();
        if (n == 0)
        {
            system("cls");
            printare_meniu();
            meniu_principal(context);
        }
        else if (n == 1)
        {
            exit(0);
        }
        else
        {
            int stop_while = 0;
            while (stop_while == 0)

            {
                system("cls");
                printf(" 0.Inapoi meniu\n");
                printf(" 1.Exit\n");
                int n;
                printf(" => ");
                scanf("%d", &n);
                getchar();
                if (n == 0)
                {
                    system("cls");
                    printare_meniu();
                    meniu_principal(context);
                    stop_while = 1;
                }
                else if (n == 1)
                {
                    stop_while = 1;
                    exit(0);
                }
            }
        }
    }
    else
    {
        system("cls");
        meniu_restituire(context);
    }

}

void meniu_donare(Context* context)
{
    printf(" 0.Inapoi\n");
    printf(" 1.Continuati\n");
    printf(" => ");
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
        char autor[101], carte[101], editura[101];
        printf(" Autorul: ");
        fgets(autor, 101, stdin);
        autor[strcspn(autor, "\n")] = 0;
        printf(" Cartea: ");
        fgets(carte, 101, stdin);
        carte[strcspn(carte, "\n")] = 0;
        printf(" Editura: ");
        fgets(editura, 101, stdin);
        editura[strcspn(editura, "\n")] = 0;

        adaugare_donatie(context, autor, carte, editura);
        printf(" Cartea dvs. %s a fost donata cu succes!", carte);
        printf("\n");
        printf(" - - - - - - - - - - - - - -\n");
        printf(" |     0.Inapoi             |\n");
        printf(" |     1.Donati din nou     |\n");
        printf(" |     2.Exit               |\n");
        printf(" - - - - - - - - - - - - - -\n");
        int optiune;
        printf(" => ");
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
            int stop_while = 0;
            while (stop_while == 0)
            {
                system("cls");
                char autor[101], carte[101], editura[101];
                printf(" Autorul: ");
                fgets(autor, 101, stdin);
                autor[strcspn(autor, "\n")] = 0;
                printf(" Cartea: ");
                fgets(carte, 101, stdin);
                carte[strcspn(carte, "\n")] = 0;
                printf(" Editura: ");
                fgets(editura, 101, stdin);
                editura[strcspn(editura, "\n")] = 0;

                adaugare_donatie(context, autor, carte, editura);
                printf(" Cartea dvs. %s a fost donata cu succes!", carte);
                printf("\n");
                printf(" - - - - - - - - - - - - - -\n");
                printf(" |     0.Inapoi             |\n");
                printf(" |     1.Donati din nou     |\n");
                printf(" |     2.Exit               |\n");
                printf(" - - - - - - - - - - - - - -\n");
                int optiune;
                printf("=> ");
                scanf("%d", &optiune);
                getchar();

                if (optiune == 0)
                {
                    system("cls");
                    printare_meniu();
                    meniu_principal(context);
                    stop_while = 1;
                    break;
                }
                else if (optiune == 2)
                {
                    exit(0);
                    stop_while = 1;
                    break;
                }



            }

        }

      
    }
   
    else
    {
        system("cls");
        meniu_donare(context);
    }
    
}


void meniu_vizualizare_carti(Context* context)
{
    printf(" 0.Inapoi\n");
    printf(" 1.Continuati\n");
    printf(" => ");
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
        printf("   CARTI DISPONIBILE   \n\n");
        for (int i = 0; i < context->nr_carti; i++)
        {

            printf(" Nume: %s\n", context->carti[i].nume);
            printf(" Autor: %s\n", context->carti[i].autor);
            printf(" Editura: %s\n", context->carti[i].editura);
            printf(" Nr. exemplare disponibile: %d\n\n", context->carti[i].nr_exemplare);
        }
    }
    else
    {
        system("cls");
        meniu_vizualizare_carti(context);
    }
    printf(" 0.Inapoi meniu\n");
    printf(" 1.Exit\n");
    int n;
    printf(" => ");
    scanf("%d", &n);
    getchar();
    if (n == 0)
    {
        system("cls");
        printare_meniu();
        meniu_principal(context);
    }
    else if (n == 1)
    {
        exit(0);
    }
    else
    {
        int stop_while = 0;

        while (stop_while == 0)
        {
            system("cls");
            printf(" 0.Inapoi meniu\n");
            printf(" 1.Exit\n");
            int n;
            printf(" => ");
            scanf("%d", &n);
            getchar();
            if (n == 0)
            {
                
                printare_meniu();
                meniu_principal(context);
                stop_while = 1;
            }
            else if (n == 1)
            {
                stop_while = 1;
                exit(0);
            }
        }
    }

}

void meniu_cautare_carti(Context* context)
{
    int optiune;
    printf(" 0.Inapoi\n");
    printf(" 1.Continuati\n");
    printf(" => ");
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
        printf(" Cautati: ");
        char text[1001];
        fgets(text, 1001, stdin);
        text[strcspn(text, "\n")] = 0;
        cautare_carte(context, text);

    }
    else
    {
        system("cls");
        meniu_cautare_carti(context);
    }


}


void meniu_vizualizare_cont(Context* context)
{
    printf(" 0.Inapoi\n");
    printf(" 1.Continuati\n");
    printf(" => ");
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
        printf("   VIZUALIZARE CONT   \n\n");

        printf(" ID logare: %d\n", context->cont_logat.cod);
        printf(" Username: %s\n\n", context->cont_logat.nume);
        printf("   ISTORIC   \n");
        for (int i = 0; i < context->nr_istoric; i++)
        {
            if (context->istoric[i].cod_utilizator == context->cont_logat.cod)
            {
                for (int j = 0; j < context->nr_carti; j++)
                {
                    if (context->istoric[i].cod_carte == context->carti[j].cod)
                    {
                        printf(" Autorul: %s\n", context->carti[j].autor);
                        printf(" Cartea: %s\n", context->carti[j].nume);
                        break;
                    }
                }
                printf(" Data imprumut: %s\n", context->istoric[i].data_imprumut);
                printf(" Data return: %s\n\n", context->istoric[i].data_return);

            }
        }
        printf("   DONATII   \n");
        for (int i = 0; i < context->nr_donatii; i++)
        {
            if (context->cont_logat.cod == context->donatii[i].cod_utilizator)
            {
                printf(" Nume carte: %s\n", context->donatii[i].nume_carte);
                printf(" Data donatie: %s\n\n", context->donatii[i].data_donatie);
            }
        }

    }
    else
    {
        system("cls");
        meniu_vizualizare_cont(context);
    }
    printf(" 0.Inapoi meniu\n");
    printf(" 1.Exit\n");
    int n;
    printf("=> ");
    scanf("%d", &n);
    getchar();
    if (n == 0)
    {
        system("cls");
        printare_meniu();
        meniu_principal(context);
    }
    else if (n == 1)
    {
        exit(0);
    }
    else
    {
        int stop_while = 0;
        while (stop_while == 0)
        {
            system("cls");
            printf(" 0.Inapoi meniu\n");
            printf(" 1.Exit\n");
            int n;
            printf("=> ");
            scanf("%d", &n);
            getchar();
            if (n == 0)
            {
                system("cls");
                printare_meniu();
                meniu_principal(context);
                stop_while = 1;
            }
            else if (n == 1)
            {
                exit(0);
                stop_while = 1;
            }
           
        }

    }
}

void meniu_exit()
{
    exit(0);
}


void meniu_principal(Context* context)
{
    int number;
    printf("=>");
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
        meniu_vizualizare_cont(context);
        break;
    case 7:
        meniu_exit(0);
        break;

    default: 
        printare_meniu();
        meniu_principal(context);
        break;
    }
    

}


void stergere_imprumuturi(Context* context, char autor[], char carte_cautata[])
{
    int id_carte_cautata = 0;
    for (int i = 0; i < context->nr_carti; i++)
    {
        if (strcmp(context->carti[i].autor, autor) == 0 && strcmp(context->carti[i].nume, carte_cautata)==0)
        {
            context->carti[i].nr_exemplare++;
            id_carte_cautata = context->carti[i].cod;

            break;

        }
    }

    for (int i = 0; i < context->nr_imprumuturi; i++)
    {
        if (context->imprumuturi[i].cod_utilizator == context->cont_logat.cod && context->imprumuturi[i].cod_carte == id_carte_cautata)
        {
            context->istoric[context->nr_istoric].cod_utilizator = context->cont_logat.cod;
            context->istoric[context->nr_istoric].cod_carte = id_carte_cautata;
            context->istoric[context->nr_istoric].data_imprumut = (char*)malloc(20);
            strcpy(context->istoric[context->nr_istoric].data_imprumut, context->imprumuturi[i].data_imprumut);
            char* returnDate = getCurrentDate();
            context->istoric[context->nr_istoric].data_return = (char*)malloc(20);
            strcpy(context->istoric[context->nr_istoric].data_return, returnDate);
            context->nr_istoric++;
            break;
        }
    }


    for (int i = 0; i < context->nr_imprumuturi; i++)
    {
        if (context->imprumuturi->cod_carte == id_carte_cautata && context->imprumuturi->cod_utilizator == context->cont_logat.cod)
        {
            context->imprumuturi[i] = context->imprumuturi[i + 1];

        }

    }
    context->nr_imprumuturi--;

    update_imprumuturi(context->imprumuturi, context->nr_imprumuturi);
    update_carti(context->carti, context->nr_carti);
    update_istoric(context->istoric, context->nr_istoric);
}

void adaugare_donatie(Context* context, char autor[], char carte[], char editura[])
{
    int gasit = 0;
    for (int i = 0; i < context->nr_carti; i++)
    {
        if (strcmp(context->carti[i].nume, carte) == 0 && strcmp(context->carti[i].autor, autor) == 0)
        {
            context->carti[i].nr_exemplare++;
            gasit = 1;
            break;
        }
    }
    if (gasit == 0)
    {
        char string[1001];
        strcpy(string, autor);
        strcpy(string+strlen(string), carte);
        strcpy(string + strlen(string), editura);
        context->carti[context->nr_carti].cod = hashString(string);
        context->carti[context->nr_carti].nume = (char*)malloc(20);
        strcpy(context->carti[context->nr_carti].nume, carte);
        context->carti[context->nr_carti].autor = (char*)malloc(20);
        strcpy(context->carti[context->nr_carti].autor, autor);
        context->carti[context->nr_carti].editura = (char*)malloc(20);
        strcpy(context->carti[context->nr_carti].editura, editura);
        context->carti[context->nr_carti].nr_exemplare = 1;
        context->nr_carti++;

    }
    context->donatii[context->nr_donatii].cod_utilizator = context->cont_logat.cod;
    context->donatii[context->nr_donatii].nume_carte = (char*)malloc(20);
    strcpy(context->donatii[context->nr_donatii].nume_carte, carte);
    context->donatii[context->nr_donatii].data_donatie = (char*)malloc(20);
    char* data_donatie = getCurrentDate();
    strcpy(context->donatii[context->nr_donatii].data_donatie, data_donatie);
    context->nr_donatii++;
    update_carti(context->carti, context->nr_carti);
    update_donatii(context->donatii, context->nr_donatii);
}

void cautare_carte(Context* context, char text[])
{
    system("cls");
    printf("\n");
    for (int i = 0; i < context->nr_carti; i++)
    {

        if ((strstr(context->carti[i].autor, text) != NULL || fct_tolower(context->carti[i].autor, text) != 0) || (strstr(context->carti[i].nume, text) != NULL || fct_tolower(context->carti[i].nume, text) != 0) || (strstr(context->carti[i].editura, text) != NULL || fct_tolower(context->carti[i].editura, text) != 0) || (fct_tolower_strtok(context->carti[i].autor, text) != 0 || fct_tolower_strtok(context->carti[i].autor, text) != 0))
        {
            printf(" Nume: %s\n", context->carti[i].nume);
            printf(" Autor: %s\n", context->carti[i].autor);
            printf(" Editura: %s\n", context->carti[i].editura);
            printf(" Nr. exemplare disponibile: %d\n\n", context->carti[i].nr_exemplare);
        }
      

    }
    printf("- - - - - - - - - - - - - -\n");
    printf("|     1.Cauta din nou      |\n");
    printf("|     2.Inapoi la meniu    |\n");
    printf("|     3.Exit               |\n");
    printf("- - - - - - - - - - - - - -\n");
    printf("=> ");
    int optiune;
    scanf("%d", &optiune);
    getchar();
    system("cls");

    if (optiune == 1)
    {
        printf(" Cautati: ");
        char text2[1001];
        fgets(text2, 1001, stdin);
        text2[strcspn(text2, "\n")] = 0;
        cautare_carte(context, text2);
    }
    else if (optiune == 2)
    {
        printare_meniu();
        meniu_principal(context);
    }
    else if (optiune == 3)
    {
        meniu_exit(0);
    }
 
    
 }

int fct_tolower(char sir[], char text[])
{
    char copie_sir[101], copie_text[101];
    strcpy(copie_sir, sir);
    strcpy(copie_text, text);
    for (int i = 0; i < strlen(copie_sir); i++)
    {
        copie_sir[i] = tolower(copie_sir[i]);
    }

    for (int i = 0; i < strlen(copie_text); i++)
    {
        copie_text[i] = tolower(copie_text[i]);
    }

    if (strstr(copie_sir, copie_text) != NULL)
        return 1;
    return 0;
}

int fct_tolower_strtok(char sir[], char text[])
{
    char copie_sir[101], copie_text[101];
    strcpy(copie_sir, sir);
    strcpy(copie_text, text);
    for (int i = 0; i < strlen(copie_sir); i++)
    {
        copie_sir[i] = tolower(copie_sir[i]);
    }

    for (int i = 0; i < strlen(copie_text); i++)
    {
        copie_text[i] = tolower(copie_text[i]);
    }
    char* p = strtok(copie_text, " ,.!");
    while (p != NULL)
    {
        if (strstr(copie_sir, p) != NULL)
            return 1;
        p = strtok(NULL, " ,.!");

    }
    return 0;
}


int verify_login_argv(Context *context, char nume[], char parola[])
{
    for (int i = 0; i < context->nr_utilizatori; i++)
    {
        if (strcmp(context->utilizatori[i].nume, nume) == 0 && strcmp(context->utilizatori[i].parola, parola) == 0)
        {
            context->cont_logat.nume = (char*)malloc(101);
            strcpy(context->cont_logat.nume, nume);
            context->cont_logat.parola = (char*)malloc(101);
            strcpy(context->cont_logat.parola, parola);
            context->cont_logat.cod = context->utilizatori[i].cod;
            return 1;
        }

    }
    return 0;
}
