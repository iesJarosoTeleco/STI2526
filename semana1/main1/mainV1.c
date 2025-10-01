/*
 * DESCRIPCIÓN: Realizar un programa qeu haga que la ESP32 realice un parpadeo de 1s de periodo
 * Autor: Julio Díaz
 * Empresa: IES JAROSO
 */


//Librerias necesarias para hacer funcionar el programa
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_timer.h"

//Definimos las constante del programa
#define PINLED1 32
#define MASKPINLED1 1ULL << PINLED1


//Función principal
void app_main(void)
{
    //según la documentación creamos variable de tipo gpio_config_t para definir la configuración del Pin
    gpio_config_t configLed1 = {
        .pin_bit_mask = MASKPINLED1,
        .mode = GPIO_MODE_INPUT_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE
    };
    //pasamos la configuración a la ESP32 a través de la función gpio_config    
    gpio_config(&configLed1);

    //realicemos un bucle infinito, donde pongamos un 1 y un 0 en el pin indicado cada 500ms
    while (1)
    {
        gpio_set_level(PINLED1, 0);
        vTaskDelay(pdMS_TO_TICKS(500));
        gpio_set_level(PINLED1, 1);
        vTaskDelay(pdMS_TO_TICKS(500));

    }
    
}
