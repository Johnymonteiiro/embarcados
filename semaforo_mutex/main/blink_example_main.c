
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_strip.h"
#include "sdkconfig.h"
#include "rtc_wdt.h"

SemaphoreHandle_t xMutex;

volatile uint32_t x;

void faz_computacao_pesada(void)
{
    volatile uint64_t a;

    for (a = 0; a < 100000; a++)
    {
        x = x + a;
        // rtc_wdt_feed();
    }
}

void Tarefa(void *ponteiro)
{
    int valor = *(int *)ponteiro;
    while (1)
    {

        if (xSemaphoreTake(xMutex, portMAX_DELAY)) // verificação do down
        {
            printf("Tarefa %d Entrou na regiao critica\n", valor);
            // faz_computacao_pesada(); // se essa rotina demorar e não alimentar o watchdog o programa reseata
            vTaskDelay(pdMS_TO_TICKS(10000));
            printf("Tarefa %d Saiu da regiao critica\n", valor);
            xSemaphoreGive(xMutex); // up
        }

        vTaskDelay(pdMS_TO_TICKS(10000)); // sleep
    }
}

void leiaString(char *st, int tamanhoMax)
{
    int x = 0;
    int c;

    while (1)
    {
        c = getchar();

        switch (c)
        {
        case EOF:
            vTaskDelay(pdMS_TO_TICKS(10));
            break;
        case 13:          // Enter no Windows (\r)
        case 10:          // Enter no Linux/Mac (\n)
            st[x] = '\0'; // finaliza a string
            printf("\n"); // pula linha no terminal
            return;
        case 8: // Backspace (opcional)
        case 127:
            if (x > 0)
            {
                x--;
                printf("\b \b"); // apaga o caractere do terminal
            }
            break;
        default:
            if (x < tamanhoMax - 1)
            {
                st[x++] = c;
                printf("%c", c); // eco no terminal
            }
            break;
        }
    }
}

void app_main()
{
    xMutex = xSemaphoreCreateMutex();
    xSemaphoreTake(xMutex, portMAX_DELAY);

    printf("Cria tarefas \n");
    for (int x = 0; x < 10; x++)
    {
        printf("Cria Tarefa %d\n", x);
        xTaskCreate(Tarefa, "escreve", 2048, (void *)&x, 5, NULL);
    }

    while (1)
    {
        char buffer[64];
        printf("Digite algo: ");
        leiaString(buffer, sizeof(buffer));
        printf("Você digitou: %s\n", buffer);

        xSemaphoreGive(xMutex);
        vTaskDelay(pdMS_TO_TICKS(500));
        printf("X \n");
    }
}