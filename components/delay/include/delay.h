#ifndef __DELAY__
#define __DELAY__

#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include <rom/ets_sys.h>

#define delay_us(A) ets_delay_us(A)
#define delay_ms(A) vTaskDelay(A / portTICK_PERIOD_MS)
#define getTime() esp_timer_get_time()
#endif