#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/gpio.h"

#define LED_PIN 2

void led_timer(int interval)
{
  gpio_set_level(LED_PIN, (uint32_t)1);
  vTaskDelay(interval / portTICK_PERIOD_MS);
  gpio_set_level(LED_PIN, (uint32_t)0);
  vTaskDelay(interval / portTICK_PERIOD_MS);
}

void led_blink(int number)
{
  for (int i = 0; i < number; i++)
  {
    gpio_set_level(LED_PIN, (uint32_t)1);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    gpio_set_level(LED_PIN, (uint32_t)0);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
  vTaskDelay(2000 / portTICK_PERIOD_MS);
}

void configure_led(void)
{
  gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
  led_timer(1000);
}

void turn_on_off(int level)
{
  gpio_set_level(LED_PIN, (uint32_t)level);
}