/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"
#include "driver/gpio.h"

#define LOW 0
#define HIGH 1
void app_main(void)
{
    gpio_config_t config_variables;
    config_variables.intr_type = GPIO_INTR_DISABLE;
    config_variables.mode = GPIO_MODE_OUTPUT;
    config_variables.pin_bit_mask = (1 << 23 || 1 << 22);
    config_variables.pull_down_en = GPIO_PULLDOWN_DISABLE;
    config_variables.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio_config(&config_variables);

    while (1)
    {
        gpio_set_level(23, HIGH);
        gpio_set_level(22, LOW);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        gpio_set_level(23, LOW);
        gpio_set_level(22, HIGH);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    printf("Hello world!\n");
}
