/*
 * DESCRIPCIÓN: detectar pulsador por flanco, en este caso al soltar el pulsador
 *              usando interrupción
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
#define TIEMPOREBOTE 150000 //us

static const char* TAG = "MyModule";

int pulsaciones = 0;
int rebotes = 0;

//Declaración funciones
void isrPulsador1(void *);
void isrTimerPul1Rebotes(void *);

//crear handles
esp_timer_handle_t h_timerPul1Rebotes;

//Función principal
void app_main(void)
{
    

    gpio_config_t configPinPul1 = {
        .pin_bit_mask = MASKPINPUL1,
        .mode =  GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_POSEDGE
    };

    gpio_config(&configPinPul1);

    gpio_install_isr_service(0);
    gpio_isr_handler_add(PINPULSADOR1, isrPulsador1, NULL);

    esp_timer_create_args_t configTimerPul1Rebotes = {
        .arg = NULL, 
        .callback = isrTimerPul1Rebotes,
        .name = "isrTimerPul1Rebotes"
    };
    esp_timer_create(&configTimerPul1Rebotes, &h_timerPul1Rebotes);
    
    while (1)
    {
        
        ESP_LOGI(TAG, "pulsaciones: %d", pulsaciones);
        vTaskDelay(pdMS_TO_TICKS(1000));
    } 
}

void isrPulsador1(void * args)
{
    if (rebotes == 0)
    {
        pulsaciones++;
        rebotes = 1;
        esp_timer_start_once(h_timerPul1Rebotes, TIEMPOREBOTE);
    }
    
}

void isrTimerPul1Rebotes(void *args)
{
    rebotes = 0;
}
