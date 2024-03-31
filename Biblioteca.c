#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include "Structuri.h"
#include "Init.h"
#include "Update.h"
#include <time.h>

void login();
void printare_meniu();
void meniu_principal();
void meniu_imprumutare();
void meniu_restituire();
void meniu_donare();
void meniu_vizualizare_carti();
void meniu_cautare_carti();
void meniu_vizualizare_cont();
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

Context context;


int main()
{ 
    //citim datele
    init(&context);
    
   /* for (int i = 0; i < context.nr_carti; i++)
    {
        printf("%d %s %s %s %d\n", context.carti[i].cod, context.carti[i].nume, context.carti[i].autor, context.carti[i].editura, context.carti[i].nr_exemplare);
    }
    for (int i = 0; i < context.nr_utilizatori; i++)
    {
        printf("%d %s %s\n", context.utilizatori[i].cod, context.utilizatori[i].nume, context.utilizatori[i].parola);
    }
    for (int i = 0; i < context.nr_imprumuturi; i++)
    {
        printf("%d %d %s\n", context.imprumuturi[i].cod_utilizator, context.imprumuturi[i].cod_carte, context.imprumuturi[i].data_imprumut);
    }

    for (int i = 0; i < context.nr_donatii; i++)
    {
        printf("%d %s %s\n", context.donatii[i].cod_utilizator, context.donatii[i].nume_carte, context.donatii[i].data_donatie);
    }

    for (int i = 0; i < context.nr_istoric; i++)
    {
        printf("%d %d %s %s\n", context.istoric[i].cod_utilizator, context.istoric[i].cod_carte, context.istoric[i].data_imprumut, context.istoric[i].data_return);
    }*/


    login();

    
   
    return 0;
}

void login()
{
    printf("1.Log in\n");
    printf("2.Sign up\n");
    printf("=>");
    int n;
    scanf("%d", &n);
    system("cls");
    if (n == 1)
    {   
        char nume[101], parola[101];
        printf("Introduceti numele: ");
        scanf("%s", nume);
        printf("Introduceti parola: ");
        scanf("%s", parola);
        getchar();
        system("cls"); //clear screen
        printare_meniu();
        meniu_principal();
    }
    else
    {
        char nume[101], parola[101];
        int verif = 1, OK = 1;
        printf("Introduceti numele: ");
        scanf("%s", nume);
        while (OK)
        {
            for (int i = 0; i < context.nr_utilizatori; i++)
            {
                if (strcmp(nume, context.utilizatori[i].nume) == 0)
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
        context.cont_logat.cod = cod_random;
        context.cont_logat.nume = (char*)malloc(101);
        strcpy(context.cont_logat.nume, nume);
        context.cont_logat.parola = (char*)malloc(101);
        strcpy(context.cont_logat.parola, parola);
     
        //adaugam noul utilizator in vectorul de utilizatori
        context.utilizatori[context.nr_utilizatori].cod = cod_random;
        context.utilizatori[context.nr_utilizatori].nume = (char*)malloc(101);
        strcpy(context.utilizatori[context.nr_utilizatori].nume, nume);
        context.utilizatori[context.nr_utilizatori].parola = (char*)malloc(101);
        strcpy(context.utilizatori[context.nr_utilizatori].parola, parola);
        context.nr_utilizatori++;
        update_utilizatori(context.utilizatori, context.nr_utilizatori); //un nou utilizator s-a inregistrat deci facem update in fisierul de utilizatori
        
        system("cls");
        printare_meniu();
        meniu_principal();
    }
    
    
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

void meniu_principal()
{
    printf("\n");
    int number;
    scanf("%d", &number);
    getchar();
    system("cls");
 
    switch (number)
    {
    case 1:
        meniu_imprumutare();
        break;
    case 2:
        meniu_restituire();
        break;
    case 3:
        meniu_donare();
        break;
    case 4:
        meniu_vizualizare_carti();
        break;
    case 5:
        meniu_cautare_carti();
        break;
    case 6:
        meniu_exit();
        break;
    }

}

void meniu_imprumutare()
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
         meniu_principal();
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
             for (int i = 0; i < context.nr_carti; i++)
             {
                 if (strcmp(carte, context.carti[i].nume) == 0)
                 {
                     if (context.carti[i].nr_exemplare > 0)
                     {
                         stop_while = 0;
                         //updatam vectorul de imprumuturi
                         context.imprumuturi[context.nr_imprumuturi].cod_utilizator = context.cont_logat.cod;
                         context.imprumuturi[context.nr_imprumuturi].cod_carte = context.carti[i].cod;
                         context.imprumuturi[context.nr_imprumuturi].data_imprumut = (char*)malloc(20);
                         char* currentDate = getCurrentDate();
                         strcpy(context.imprumuturi[context.nr_imprumuturi].data_imprumut, currentDate);
                         context.nr_imprumuturi++;
                         context.carti[i].nr_exemplare--;
                         update_carti(context.carti, context.nr_carti);
                         update_imprumuturi(context.imprumuturi, context.nr_imprumuturi); //facem update in fisierul de imprumuturi
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

void meniu_restituire()
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
        meniu_principal();
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

void meniu_donare()
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
        meniu_principal();
    }
    else if(optiune == 1)
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

void meniu_vizualizare_carti()
{
}

void meniu_cautare_carti()
{
}

void meniu_vizualizare_cont()
{

}

void meniu_exit()
{
    exit(0);
}