#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include "Structuri.h"
#include "Init.h"
#include "Update.h"
#include "DataFunctions.h"


int main(int argc, char* argv[])
{ 
    Context context;  // in variabila Context retinem vectorii structurilor
    init(&context); //initializam vectorii
    if(argc <= 1) // daca nu avem argumente pe linia de comanda
        login_cont(&context);
    else
    {
        if (verify_login_argv(context,argv[1], argv[2]) == 1)
        {
            printare_meniu();
            meniu_principal(&context);
        }
        else
        {
            printf("\n Nume sau parola incorecta.\n Alegeti una dintre optiunile de mai jos\n");
            login_cont(&context);
        }
    }

    return 0;
}

