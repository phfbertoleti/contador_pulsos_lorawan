#include <stdio.h>
#include <esp_task_wdt.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp_log.h"
#include "esp_err.h"

/* Includes dos módulos do software */
#include "LoRaWAN/LoRaWAN.h"
#include "envios_lorawan/envios_lorawan.h"
#include "contadores_de_pulsos/contadores_de_pulsos.h"
#include "nvs_rw/nvs_rw.h"

/* Definições - debug */
#define APP_MAIN_TAG       "APP_MAIN"

/* Definição - tempo máximo sem feed do watchdog */
#define TEMPO_MAX_SEM_FEED_WATCHDOG        60 //s

void app_main(void)
{    
    ESP_LOGI(APP_MAIN_TAG, "Software inicializado");

    esp_task_wdt_init(TEMPO_MAX_SEM_FEED_WATCHDOG, true);

    /* Obtem informações do ESP32-C3 */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    ESP_LOGI(APP_MAIN_TAG, "Chip: %d; Numero de cores: %d; WiFI: %s%s; Tamanho de flash: %dMB",
                           CONFIG_IDF_TARGET,
                           chip_info.cores,
                           (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
                           (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "",
                           spi_flash_get_chip_size() / (1024 * 1024));
    /* Inicializa NVS */
    init_nvs();

    /* Inicializa LoRaWAN */
    init_lorawan();

    /* Inicializa modulo de contagem de pulsos */
    init_contadores_de_pulsos();

    /* Inicializa envios LoRaWAN */
    init_envios_lorawan();
}
