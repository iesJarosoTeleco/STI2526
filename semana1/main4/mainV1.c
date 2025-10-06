*
 * DESCRIPCIÓN: Realizar cambios en el modo de funcionamiento, usando la pulsación
                Definimos las acciones en el main, y en la rutina de servicio de la 
                interrupción del pulsador, cambiamos la varible del modo, que será usada
                por el main para saber que modo debe ejecutar
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

#define PINLED1 32
#define MASKPINLED1 1ULL << PINLED1

#define MODOMAX 1   // modo 0 - led apagado, modo 1 - led parpadeando

static const char* TAG = "MyModule";

//Variables globales
int pulsaciones = 0;
int rebotes = 0;
int modo = 0; // modo 0 - led apagado, modo 1 - led parpadeando

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

    gpio_config_t configPinLed1 = {
        .pin_bit_mask = MASKPINLED1,
        .mode =  GPIO_MODE_INPUT_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };

    gpio_config(&configPinLed1);

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
        
        if (modo == 0)
        {
            gpio_set_level(PINLED1, 0); //apagar led1
            ESP_LOGI(TAG, "modo 0 - led apagado");
        }
        else if (modo == 1)
        {
            gpio_set_level(PINLED1, !gpio_get_level(PINLED1));
            vTaskDelay(pdMS_TO_TICKS(500));
            ESP_LOGI(TAG, "modo 1 - led parpadendo");
        }
        else
        {
            ESP_LOGI(TAG, "error modo fuera de rango. Modo %d", modo);
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    } 
}

void isrPulsador1(void * args)
{
    if (rebotes == 0)
    {
        pulsaciones++;
        rebotes = 1;
        esp_timer_start_once(h_timerPul1Rebotes, TIEMPOREBOTE);
        if (modo < MODOMAX)
        {
            modo++;
        }
        else
        {
            modo = 0;
        }
    }
    
}

void isrTimerPul1Rebotes(void *args)
{
    rebotes = 0;
}
