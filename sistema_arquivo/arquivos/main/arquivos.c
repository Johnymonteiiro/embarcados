#include <stdio.h>

#include "esp_spiffs.h"
void app_main(void)

{

    esp_vfs_spiffs_conf_t config = {

        .base_path = "/storage",

        .partition_label = NULL,

        .max_files = 5,

        .format_if_mount_failed = true

    };

    esp_vfs_spiffs_register(&config);

    FILE *f = fopen("/storage/arquivo.txt", "r");

    if (f == NULL)

    {

        printf("Nao consigo ler o arquivo\n");

        return;
    }

    char linha[64];

    fgets(linha, sizeof(linha), f);
    printf("Lido = %s\n", linha);

    fclose(f);
}