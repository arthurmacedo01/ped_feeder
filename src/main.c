#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

TaskHandle_t TaskReading = NULL;
QueueHandle_t Queue1 = NULL;

void read_sensor(void *pvParameters)
{
  int value = 0;
  while (1)
  {
    value++;
    printf("lendo sensor... valor: %d\n", value);
    if (value >= 5 && value <= 10)
    {
      xQueueSendToBack(Queue1, &value, 0);
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
  vTaskDelete(NULL);
}
void sending_value(void *pvParameters)
{
  int value = 0;
  while (1)
  {
    if (xQueueReceive(Queue1, &value, portMAX_DELAY))
    {
      printf("enviando valor %d...\n", value);
    }
  }
  vTaskDelete(NULL);
}

void app_main(void)
{
  Queue1 = xQueueCreate(10, sizeof(int));
  xTaskCreate(read_sensor, "Leitura de Sensor", 2048, NULL, 0, NULL);
  xTaskCreate(sending_value, "Envio de Valor", 2048, NULL, 0, &TaskReading);
}