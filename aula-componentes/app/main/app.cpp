#include <stdio.h>
#include "digital.h"
#include "delay.h"

extern "C" void app_main(void)
{
    digital.setDebug(1); // Ativa debug

    digital.pinMode(GPIO_NUM_2, GPIO_MODE_OUTPUT); // Configura o pino 2 como saída

    while (true)
    {
        digital.digitalWrite(GPIO_NUM_2, 1);
        delay_ms(1000);

        digital.digitalWrite(GPIO_NUM_2, 0);
        delay_ms(1000);
    }
}