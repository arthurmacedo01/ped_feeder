#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TaskHandle_t TaskReading = NULL;

void read_sensor(void *pvParameters)
{
  int value = 0;
  while (1)
  {
    value++;
    printf("lendo sensor... valor: %d\n", value);
    if (value >= 5 && value <= 10)
    {
      // notificar a task sending_value
      xTaskNotifyGive(TaskReading);
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
  vTaskDelete(NULL);
}
void sending_value(void *pvParameters)
{
  while (1)
  {
    // aguardando a notificação ...
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    printf("enviando valor...\n");
  }
  vTaskDelete(NULL);
}

void app_main(void)
{
  xTaskCreate(read_sensor, "Leitura de Sensor", 2048, NULL, 0, NULL);
  xTaskCreate(sending_value, "Envio de Valor", 2048, NULL, 0, &TaskReading);
}