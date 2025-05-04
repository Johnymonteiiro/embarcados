idf_component_register(SRCS "web_test.c"
                    INCLUDE_DIRS "."
                    REQUIRES nvs_flash esp_wifi esp_event esp_netif mqtt
                    )
