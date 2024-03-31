#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include "Structuri.h"
#include "Init.h"
#include "Update.h"
#include "DataFunctions.h"

Context context;

int main()
{ 
    init(&context);
    login_cont(&context);

    return 0;
}

