/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
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
    
    while(1)
    { 

        //activar led verde
        gpio_set_level(PINLEDROJO, 0);
        gpio_set_level(PINLEDVERDE, 1);
        vTaskDelay(pdMS_TO_TICKS(5000));
        //activar led amarillo
        gpio_set_level(PINLEDAMARILLO, 1);
        gpio_set_level(PINLEDVERDE, 0);
        vTaskDelay(pdMS_TO_TICKS(1000));

        //activar led rojo
        gpio_set_level(PINLEDAMARILLO, 0);
        gpio_set_level(PINLEDROJO, 1);
        vTaskDelay(pdMS_TO_TICKS(4000));
    }


    
}
