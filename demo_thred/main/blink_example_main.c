
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_timer.h"

TaskHandle_t taskID;
TaskHandle_t taskID2;

void myTask(void *)
{
    int64_t tempo_atual;
    while (1)
    {
        tempo_atual = esp_timer_get_time(); // Tempo atual em microssegundos
        printf("Oi da tarefa 1, tempo atual: %lld\n", tempo_atual);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void myTask2(void *)
{
    while (1)
    {
        printf("Oi da tarefa 2\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    xTaskCreate(myTask, "Qualquer nome para debugar", 2048, NULL, 0, &taskID);
    xTaskCreate(myTask2, "Qualquer nome para debugar", 2048, NULL, 0, &taskID2);
}

// Onde tem Null podemos botar um parametro que será passado para a task
// O segundo parametro é o tamanho da stack, o terceiro é o parametro que será passado para a task, o quarto é a prioridade da task e o quinto é o ponteiro que vai receber o ID da task criada
// O primeiro parametro é o nome da task,
// o segundo é o tamanho da stack,
// o terceiro é o parametro que será passado para a task,
// o quarto é a prioridade da task e o quinto é o ponteiro que vai receber o ID da task criada

// xTaskCreatePinnedToCore(myTask, "Qualquer nome para debugar", 2048, NULL, 0, &taskID, 1);