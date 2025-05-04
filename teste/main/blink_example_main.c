
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#define LOW 0
#define HIGH 1
#define LED_GPIO 22
#define LED_GREEN_GPIO 23

void app_main(void)
{
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1 << LED_GPIO | 1 << LED_GREEN_GPIO);
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio_config(&io_conf);

    int counter = 0;

    while (1)
    {
        printf("Turning on the LED\n");
        gpio_set_level(LED_GPIO, HIGH);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        printf("Turning off the LED\n");
        gpio_set_level(LED_GPIO, LOW);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        counter++;

        if (counter == 10)
        {
            printf("Turning on the GREEN LED (GPIO %d)\n", LED_GREEN_GPIO);
            gpio_set_level(LED_GREEN_GPIO, HIGH);
            vTaskDelay(1000 / portTICK_PERIOD_MS);

            printf("Turning off the GREEN LED (GPIO %d)\n", LED_GREEN_GPIO);
            gpio_set_level(LED_GREEN_GPIO, LOW);
            vTaskDelay(1000 / portTICK_PERIOD_MS);

            counter = 0;
        }
    }
}
