#include <stdio.h>
#include <string.h>
#include "serial.h"

#include "driver/uart.h"
#include "driver/gpio.h"

void SERIAL::begin(int taxa)
{
    uart_config_t uart_config = {
        .baud_rate = taxa,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };

    uart_param_config(UART_NUM_0, &uart_config);

    // Instala o driver da UART com buffers internos
    uart_driver_install(UART_NUM_0, 1024, 0, 0, NULL, 0);
}

void SERIAL::print(const char *text)
{
    uart_write_bytes(UART_NUM_0, text, strlen(text));
}

void SERIAL::println(const char *text)
{
    uart_write_bytes(UART_NUM_0, text, strlen(text));
    uart_write_bytes(UART_NUM_0, "\r\n", 2); // adiciona quebra de linha
}

int SERIAL::available()
{
    size_t length;
    uart_get_buffered_data_len(UART_NUM_0, &length);
    return length;
}

int SERIAL::read()
{
    uint8_t data;
    int len = uart_read_bytes(UART_NUM_0, &data, 1, 20 / portTICK_PERIOD_MS); // timeout de 20ms
    if (len > 0)
    {
        return data;
    }
    else
    {
        return -1; // Nada lido
    }
}

// Cria a instância global
SERIAL Serial = SERIAL();
