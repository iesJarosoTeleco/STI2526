/*
 * DESCRIPCIÓN: detectar pulsador por nivel solo mostrando un mensaje al cambiar de nivel
 * Autor: Julio Díaz
 * Empresa: IES JAROSO
 * Fecha creación:2/10/25
 * Fecha actualización:
 */


//Librerias necesarias para hacer funcionar el programa
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_timer.h"
#include "esp_log.h"

//Definimos las constante del programa
#define PINPULSADOR1 36
#define MASKPINPUL1 1ULL << PINPULSADOR1 

static const char* TAG = "MyModule";

//Función principal
void app_main(void)
{
    

    gpio_config_t configPinPul1 = {
        .pin_bit_mask = MASKPINPUL1,
        .mode =  GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };

    gpio_config(&configPinPul1);

    int estado = 0;
    while (1)
    {
        if (gpio_get_level(PINPULSADOR1)==0)
        {
            if (estado == 1)
            {
                ESP_LOGI(TAG, "Pulsador esta siendo pulsado");
                estado = 0;
            }
        }
        else
        {
            if (estado == 0)
            {
                ESP_LOGI(TAG, "Pulsador no esta siendo pulsado");
                estado = 1;
            }
        }
        vTaskDelay(pdMS_TO_TICKS(300));
    }
    

    
}
