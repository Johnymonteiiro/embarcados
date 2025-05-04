#include <stdio.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "tempo.h"

#define ECHO GPIO_NUM_22
#define TRIGGER GPIO_NUM_23

#define LOW 0
#define HIGH 1

volatile int contador = 0;
volatile int64_t t1, t2;
volatile int32_t distancia = 0;

void INTERRUPCAO(void *)
{
    if (contador == 0)
    {
        t1 = esp_timer_get_time();
        contador++;
    }
    else
    {
        contador = 0;
        t2 = esp_timer_get_time();
        distancia = (t2 - t1) / 58;
    }
}

void app_main(void)
{

    /* Configura a parte de pinos de IO */
    gpio_reset_pin(ECHO);
    gpio_reset_pin(TRIGGER);

    gpio_set_direction(ECHO, GPIO_MODE_INPUT);
    gpio_set_direction(TRIGGER, GPIO_MODE_OUTPUT);

    // Configura a parte de iterrupcoes
    gpio_install_isr_service(1);

    gpio_set_intr_type(ECHO, GPIO_INTR_ANYEDGE);
    gpio_isr_handler_add(ECHO, INTERRUPCAO, NULL);

    gpio_set_level(TRIGGER, LOW);
    while (1)
    {
        distancia = 0;
        contador = 0;
        gpio_set_intr_type(ECHO, GPIO_INTR_ANYEDGE);

        gpio_set_level(TRIGGER, HIGH);
        delay_us(10);
        gpio_set_level(TRIGGER, LOW);
        delay_ms(1000);
        printf("   distancia=%ld\n", distancia);
        gpio_set_intr_type(ECHO, GPIO_INTR_DISABLE);
    }
}