mutex ==> exclusão mutua

xSemaphoreTake(xMutex, portMAX_DELAY) ==> A função xSemaphoreTake é parte do FreeRTOS, um sistema operacional em tempo real amplamente utilizado em sistemas embarcados. Ela é usada para sincronização de tarefas e controle de acesso a recursos compartilhados, como variáveis ou periféricos.

```sh

#include "FreeRTOS.h"
#include "semphr.h"

// Criar um mutex
SemaphoreHandle_t xMutex;

void setup() {
    xMutex = xSemaphoreCreateMutex();
}

void task1(void *pvParameters) {
    if (xSemaphoreTake(xMutex, portMAX_DELAY) == pdTRUE) {
        // Recurso protegido pelo mutex
        printf("Task 1 acquired the mutex.\n");

        // Libera o mutex após o uso
        xSemaphoreGive(xMutex);
    } else {
        printf("Task 1 failed to acquire the mutex.\n");
    }
}
```