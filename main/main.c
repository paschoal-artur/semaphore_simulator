#include <stdio.h>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define RED_LED_PIN GPIO_NUM_16
#define YELLOW_LED_PIN GPIO_NUM_4
#define GREEN_LED_PIN GPIO_NUM_2

void setup_led()
{
    esp_rom_gpio_pad_select_gpio(RED_LED_PIN);
    gpio_set_direction(RED_LED_PIN, GPIO_MODE_OUTPUT);

    esp_rom_gpio_pad_select_gpio(YELLOW_LED_PIN);
    gpio_set_direction(YELLOW_LED_PIN, GPIO_MODE_OUTPUT);

    esp_rom_gpio_pad_select_gpio(GREEN_LED_PIN);
    gpio_set_direction(GREEN_LED_PIN, GPIO_MODE_OUTPUT);
}

void semaphore_task(void *pvParameters)
{
    while(1)
    {
        //!Luz verde-Passagem liberada  
        gpio_set_level(GREEN_LED_PIN, 1);
        vTaskDelay(pdMS_TO_TICKS(8000));
        gpio_set_level(GREEN_LED_PIN, 0);

        //!Luz amarela-Atenção
        gpio_set_level(YELLOW_LED_PIN, 1);
        vTaskDelay(pdMS_TO_TICKS(5000));
        gpio_set_level(YELLOW_LED_PIN, 0);

        //!Luz vermelha-Pare
        gpio_set_level(RED_LED_PIN, 1);
        vTaskDelay(pdMS_TO_TICKS(8000));
        gpio_set_level(RED_LED_PIN, 0);
    }
}


void app_main(void)
{
    setup_led();
    xTaskCreate(&semaphore_task, "semaphore_task", 2048, NULL, 5, NULL);
}
