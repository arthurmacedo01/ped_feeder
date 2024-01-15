#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void read_sensor(void *pvParameters)
{
  while (1)
  {
    printf("lendo sensor...\n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
  vTaskDelete(NULL);
}
void sending_value(void *pvParameters)
{
  int *period = (int *)pvParameters;
  while (1)
  {
    printf("enviando valor %d...\n", *period);
    vTaskDelay(*period / portTICK_PERIOD_MS);
  }
  vTaskDelete(NULL);
}

int period = 3000;

void app_main(void)
{
  xTaskCreate(read_sensor, "Leitura de Sensor", 1024, NULL, 0, NULL);
  xTaskCreate(sending_value, "Envio de Valor", 2048, (void *)&period, 0, NULL);
}