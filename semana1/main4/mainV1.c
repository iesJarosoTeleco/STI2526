/*
 * DESCRIPCIÓN: Sistema dos modos - apagado - blink
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
#define VALORMODOMAX 1 //modos 0 y 1
#define TIEMPOREBOTE 150000  //us

#define PINLED1 32
#define MASKPINLED1 1ULL << PINLED1

static const char* TAG = "Ejercicio2";

int modo = 0;
int tiempoReboteFin = 1;

//definición de handlers
esp_timer_handle_t h_timer_rebote;

//Declaración rutinas de interrupción
void isr_int_pul1 (void *);
void isr_timer_reb (void*);

//Función principal
void app_main(void)
{
    //configuaración del pulsador pin36
    gpio_config_t configPul1 = {
        .pin_bit_mask = MASKPINPUL1, 
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_POSEDGE
    };
    
    gpio_config(&configPul1);

    //configuaración del led pin32
    gpio_config_t configLed1 = {
        .pin_bit_mask = MASKPINLED1, 
        .mode = GPIO_MODE_INPUT_OUTPUT, 
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&configLed1);

    //Configuración Interrupción
    gpio_install_isr_service(0);
    gpio_isr_handler_add(PINPULSADOR1, isr_int_pul1, NULL);

    //Configuración timer
    esp_timer_create_args_t configTimerRebote = {
        .name = "timerRebote",
        .arg = NULL, 
        .callback = isr_timer_reb
    };
    esp_timer_create(&configTimerRebote, &h_timer_rebote);
    int repetirSoloUnaVez = 0;

    while(1)
    {
        if (modo == 0 && repetirSoloUnaVez == 0)
        {
            gpio_set_level(PINLED1, 0);
            ESP_LOGI(TAG, "acceso modo 0 - led apagado");
            repetirSoloUnaVez = 1;            
        }
        else if (modo == 1)
        {
            gpio_set_level(PINLED1, !gpio_get_level(PINLED1));   //hay que configurar el pin como entrada-salida
            vTaskDelay(pdMS_TO_TICKS(500));
            if (repetirSoloUnaVez == 1)
            {
                ESP_LOGI(TAG, "acceso modo 1 - led blink");
                repetirSoloUnaVez = 0;
            }
            
        }
        else if (modo >= VALORMODOMAX)
        {
            ESP_LOGI(TAG, "modo tomando valor incorrecto modo = %d", modo);
        }
        vTaskDelay(10);
    }
    
}

void isr_int_pul1 (void * args)
{
    //vTaskDelay(pdMS_TO_TICKS(150));
    if (tiempoReboteFin == 1)
    {
        if (modo < VALORMODOMAX)
        {
            modo++;
        }
        else
        {
            modo = 0;
        }
        esp_timer_start_once(h_timer_rebote, TIEMPOREBOTE);
        tiempoReboteFin = 0;
    }
    
}

void isr_timer_reb (void* args)
{
    tiempoReboteFin = 1;
}
