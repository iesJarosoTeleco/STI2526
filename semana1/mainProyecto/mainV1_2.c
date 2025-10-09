/*
 * Semáforo con un modo temporizado con timers
 *
 * SPDX-License-Identifier: CC0-1.0
 */


#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_timer.h"
#include "esp_log.h"

//constantes

#define PINLEDROJO 32
#define PINLEDAMARILLO 33
#define PINLEDVERDE 25

#define MASKPINESLEDS (1ULL<<PINLEDROJO) | (1ULL<<PINLEDAMARILLO) | (1ULL<<PINLEDVERDE)

//declaración de variables globales

int accion = 1;

//declaración de funciones callback

void isrTimerSemaforo(void *);
//handles
esp_timer_handle_t h_timerSemaforo;


void app_main(void)
{
    gpio_config_t configPinesLeds = {
        .pin_bit_mask = MASKPINESLEDS,
        .mode = GPIO_MODE_INPUT_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };

    gpio_config(&configPinesLeds);

    //poner todos los leds a cero
        gpio_set_level(PINLEDROJO, 0);
        gpio_set_level(33, 0);
        gpio_set_level(25, 0);

    //configuración y creacción del timer semaforo

    esp_timer_create_args_t configTimerSemaforo = {
        .callback = isrTimerSemaforo
    };
    esp_timer_create(&configTimerSemaforo, &h_timerSemaforo);
    int accionSig = 1;
    accion = 1;

    while(1)
    { 

        //activar led verde
        if (accion==1 && accionSig == 1)
        {
            //acción 1
            gpio_set_level(PINLEDROJO, 0);
            gpio_set_level(PINLEDVERDE, 1);
            
            accionSig = 2;
            
            esp_timer_start_once(h_timerSemaforo, 4000000);
        }
        else if (accion==2 && accionSig == 2)
        {
            //activar led amarillo
            gpio_set_level(PINLEDAMARILLO, 1);
            gpio_set_level(PINLEDVERDE, 0);

            accionSig = 3;
            esp_timer_start_once(h_timerSemaforo, 1000000);
        }
        else if (accion==3 && accionSig == 3)
        {
            //activar led rojo
            gpio_set_level(PINLEDAMARILLO, 0);
            gpio_set_level(PINLEDROJO, 1);


            accionSig = 1;
            esp_timer_start_once(h_timerSemaforo, 5000000);
        }
        else
        {
            vTaskDelay(10);
        }
    }   
}

void isrTimerSemaforo(void * args)
{
    if (accion > 0 && accion < 3)
    {
        accion++;
    }
    else
    {
        accion = 1;
    }
}
