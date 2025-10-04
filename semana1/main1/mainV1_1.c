/*
 * DESCRIPCIÓN: Realizar un programa qeu haga que la ESP32 realice un parpadeo de 1s de periodo
 *              usando un timer por interrupción. 
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
#define TIMERBLINK 500000 //us

//declaración de funciones
void isrTimerBlink(void *);

//Definimos handles
esp_timer_handle_t h_timerBlink;

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

    //configuración creación y arranque del timer para parpadeo del led
    esp_timer_create_args_t configTimerBlink = {
        .callback = isrTimerBlink, 
        .arg = NULL,
        .name = "timerBlink"
    };

    esp_timer_create(&configTimerBlink, &h_timerBlink);
    esp_timer_start_periodic(h_timerBlink, TIMERBLINK);
    //realicemos un bucle infinito, donde pongamos un 1 y un 0 en el pin indicado cada 500ms
    while (1)
    {
        vTaskDelay(10);
    }
    
}

void isrTimerBlink(void * args)
{
    gpio_set_level(PINLED1, !gpio_get_level(PINLED1));
}
