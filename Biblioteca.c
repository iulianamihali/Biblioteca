#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include "Structuri.h"
#include "Init.h"

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
    char nume[101], prenume[101];
    printf("Introduceti numele dvs: ");
    scanf("%s", nume);
    printf("Introduceti prenumele dvs: ");
    scanf("%s", prenume);
    getchar();
    system("cls"); //clear screen
    printare_meniu();
    meniu_principal();
    
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
         int nr_exemplare;
         printf("Nr exemplare: ");
         scanf("%d", &nr_exemplare);

         if (nr_exemplare > 0)
         {
             printf("Ati imprumutat cartea cu succes.\nCitire placuta!");
         }
         else
         {

             printf("Stoc epuizat!");
         }

     }

}

void meniu_restituire()
{
    printf("0.Inapoi\n");
    printf("1.Continuati\n");
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