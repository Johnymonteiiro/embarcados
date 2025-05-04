
#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "esp_timer.h"
#define PINO 23

volatile int valor = 0;
volatile int64_t t_atual, t_anterior;

void INTERRUPCAO(void *)
{
    t_atual = esp_timer_get_time();

    if (t_atual - t_anterior > 500000)
        valor++;
    t_anterior = t_atual;
}

void app_main(void)
{

    /* Configura a parte de pinos de IO */
    gpio_set_direction(PINO, GPIO_MODE_INPUT);
    gpio_set_pull_mode(PINO, GPIO_PULLUP_ONLY);

    // Configura a parte de iterrupcoes
    gpio_install_isr_service(1);
    gpio_set_intr_type(PINO, GPIO_INTR_NEGEDGE);
    gpio_isr_handler_add(PINO, INTERRUPCAO, NULL);

    int x;
    while (1)
    {
        x = valor;
        valor = 0;
        printf("frequencia=%d\n", x);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
