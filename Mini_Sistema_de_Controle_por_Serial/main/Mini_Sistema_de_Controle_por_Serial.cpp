#include <stdio.h>
#include <string.h>
#include "serial.h"
#include "digital.h"
#include "delay.h"

__int64_t BOUND_RATE = 115200;

extern "C" void app_main(void)
{
    Serial.begin(BOUND_RATE);
    digital.pinMode(GPIO_NUM_22, OUTPUT);

    char comando[32];
    int index = 0;

    Serial.println("Sistema iniciado. Digite HELP para comandos.");

    while (true)
    {
        if (Serial.available())
        {
            char c = Serial.read();
            if (c == '\n' || c == '\r')
            {
                comando[index] = '\0'; // Termina a string
                index = 0;

                if (strcmp(comando, "LED ON") == 0)
                {
                    digital.digitalWrite(GPIO_NUM_22, 1);
                    Serial.println("LED ligado!");
                }
                else if (strcmp(comando, "LED OFF") == 0)
                {
                    digital.digitalWrite(GPIO_NUM_22, 0);
                    Serial.println("LED desligado!");
                }
                else if (strcmp(comando, "STATUS") == 0)
                {
                    int estado = digital.digitalRead(GPIO_NUM_22);
                    Serial.println(estado ? "LED está ligado." : "LED está desligado.");
                }
                else if (strcmp(comando, "HELP") == 0)
                {
                    Serial.println("Comandos: LED ON, LED OFF, STATUS, HELP");
                }
                else
                {
                    Serial.println("Comando inválido. Digite HELP.");
                }
            }
            else
            {
                if (index < sizeof(comando) - 1)
                {
                    comando[index++] = c;
                }
            }
        }

        delay_ms(100);
    }
}
