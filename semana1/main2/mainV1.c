/*
 * DESCRIPCIÓN: detectar pulsador por nivel
 * Autor: Julio Díaz
 * Empresa: IES JAROSO
 * Fecha creación:
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
    
    //creamos los datos de configuración para el pin donde esta conectado el pulsador (con R de pull-up)
    gpio_config_t configPinPul1 = {
        .pin_bit_mask = MASKPINPUL1,
        .mode =  GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    //pasamos los datos de configuración del pin a la ESP32
    gpio_config(&configPinPul1);

    while (1)
    {
      //Rutina donde evaluamos si en el pin donde esta conectado el pulsado hay un 1 (3V) o un 0(0V)  
      if (gpio_get_level(PINPULSADOR1)==0)
        {
          //si el valor en el pin es 0 es que está pulsado - usamos R de pullup  
          ESP_LOGI(TAG, "Pulsador esta siendo pulsado");
        }
        else
        {
          //si el valor en el pin es 1 es que no está pulsado - usamos R de pullup  
          ESP_LOGI(TAG, "Pulsador no esta siendo pulsado");
        }
        //incluimos un delay para que los mensaje en el monitor no sean demasiado y para evitar el bouncing del pulsador
        vTaskDelay(pdMS_TO_TICKS(300));
    }
}
