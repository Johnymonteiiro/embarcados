#include <stdio.h>
#include "trena.h"

void TRENA::init(void)
{

    printf("trena :: Chamou a rotina de init\n");
}

void TRENA::calibra(int v)
{
    printf("trena :: Chamou a rotina de calibrar\n");
}

int TRENA::mede(void)
{
    printf("trena :: Chamou a rotina de mede\n");
    return 0;
}
